
/**
 * @file	linear_gauge.h
 *
 * @brief	linear_gauge.h file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#include "linear_gauge/linear_gauge.h"

#include "indicator/indicator_functions.h"

#include "math/functions.h"

#include "qdebug.h"
#include "qfontmetrics.h"
#include "qpainter.h"
#include "qpen.h"
#include "qpoint.h"
#include "qstring.h"
#include "qtimer.h"

#include "QKeyEvent"

#include <cassert>
#include <cmath>
#include <iostream>

LinearGauge::LinearGauge(QWidget *parent)
    : QWidget(parent)
    , m_largeTickInterval(0.f)
    , m_textVisible(true)
    , m_borderVisible(true)
    , m_groundVisible(true)
    , m_value(0.f)
    , m_interval(20.f)
    , m_padding(30)
    , m_digitCount(3)
    , m_alignment(Qt::AlignCenter)
    , m_orientation(Qt::Vertical)
    , m_largeTickCount(3ul)
    , m_middleTickCount(4)
    , m_smallTickCount(0)
    , m_font("Cantarell", 40)
    , m_brush(QColor("#7ec850"))
{
    // TODO: Adapt font size depending on widget size and digit count
    const QFontMetrics fm(m_font);
    m_fontSize.setWidth(fm.horizontalAdvance("000") + 1);
    m_fontSize.setHeight(fm.height());

    initializeTicksLabelValue(m_value, m_largeTickCount, m_interval);

    const QSize tickLabelSize(m_fontSize.width(), m_fontSize.height());
    m_largeTickLabelRect.setSize(tickLabelSize);
    m_largeTickLabelRectLeft.setSize(tickLabelSize);
    m_largeTickLabelRectRight.setSize(tickLabelSize);
    m_largeTickLabelRectTop.setSize(tickLabelSize);
    m_largeTickLabelRectBottom.setSize(tickLabelSize);
}

LinearGauge::~LinearGauge() = default;

Qt::Alignment LinearGauge::alignment() const
{
    return m_alignment;
}

void LinearGauge::setAlignment(const Qt::Alignment alignment)
{
    if (alignment == m_alignment)
        return;

    m_alignment = alignment;
}

Qt::Orientation LinearGauge::orientation() const
{
    return m_orientation;
}

void LinearGauge::setOrientation(const Qt::Orientation orientation)
{
    m_orientation = orientation;

    // TODO: Orientation code
}

bool LinearGauge::borderVisible() const
{
    return m_borderVisible;
}

void LinearGauge::setBorderVisible(const bool visible)
{
    if (visible == m_borderVisible)
        return;

    m_borderVisible = visible;
}

void LinearGauge::setBackgroundPalette(const QPalette & /*palette*/)
{
    // if (palette != palette())
    // {
    //     setPalette(palette);
    //     setAutoFillBackground(true);
    //     setBackgroundRole(palette);
    // }
}

void LinearGauge::setLargeTickCount(unsigned long numTicks)
{
    if (numTicks == m_largeTickCount)
        return;

    m_largeTickCount = numTicks;
    update();
}

void LinearGauge::setFont(const QFont &font)
{
    if (m_font == font)
        return;

    m_font = font;

    const QFontMetrics fm(m_font);
    m_fontSize.setWidth(fm.horizontalAdvance("000") + 1);
    m_fontSize.setHeight(fm.height());
}

unsigned long LinearGauge::digitCount() const
{
    return m_digitCount;
}

void LinearGauge::setDigitCount(unsigned long numDigits)
{
    if (numDigits == m_digitCount)
        return;

    m_digitCount = numDigits;
    update();
}

void LinearGauge::setMiddleTickCount(unsigned long numTicks)
{
    if (numTicks == m_middleTickCount)
        return;

    m_middleTickCount = numTicks;
    update();
}

float LinearGauge::value() const
{
    return m_value;
}

void LinearGauge::setValue(float value)
{
    m_value = value;
    update();
}

void LinearGauge::reset()
{
    setValue(0.f);
}

void LinearGauge::setTextVisible(bool visible)
{
    m_textVisible = visible;
}

bool LinearGauge::textVisible() const
{
    return m_textVisible;
}

void LinearGauge::keyPressEvent(QKeyEvent *event)
{
    if (m_value < 0)
        return;

    switch (event->key())
    {
    case Qt::Key_Up:
        ++m_value;
        break;
    case Qt::Key_Down:
        if (m_value > 0)
            --m_value;
        break;
    default:
        return;
    }

    update();

    QWidget::keyPressEvent(event);
}

/**
 * @brief   Scrolling 2D background
 *
 *          Refresh each time value changed
 */
void LinearGauge::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    // Remove pen width used for drawing
    // TODO: Test with big pen width
    // largeTickLabelRect.adjust(0, 0, -penWidth / 2, -penWidth / 2);

    // * 2 for top and bottom, add one for centered tick and one for hidden tick
    const auto largeTickCount = m_largeTickCount * 2ul + 1ul + 1ul;

    std::cout << "value: " << m_value << '\n';

    static auto min = m_value - m_interval;
    static auto max = m_value + m_interval;

    if (m_value >= max)
    {
        std::cout << "emit overflow()\n";
        // initializeTicksLabelValue(m_value, largeTickCount, m_interval);
    }

    if (m_value <= min)
    {
        std::cout << "emit overflow()\n";
        // initializeTicksLabelValue(m_value, largeTickCount, m_interval);
    }

    min = Common::Math::floor(m_value, m_interval);
    max = Common::Math::ceil(m_value, m_interval);

    // if (offset == 0)
    // {
    // emit requestDataUpdate();
    //     std::cout << "data update requested\n";
    //
    initializeTicksLabelValue(m_value, largeTickCount, m_interval);
    // }
    //
    //   initializeTicksLabelValue(m_value, largeTickCount, m_interval);
    //
    //
    // Model
    //
    // connect(linearGauge, LinearGauge::requestDataUpdate, this, [linearGauge]()
    // {
    //       // Consumers are free to use theirs own algorithms to fulfill the model. This last will
    //       // be read by the linear gauge on requestDataUpdate signal emission.
    //       linearGauge->setData(model);
    // });

    const auto reminder = std::fmod(m_value, m_interval);
    const auto offset =
        std::fmod(reminder * (m_largeTickInterval / m_interval), m_largeTickInterval);

    {
        const unsigned count = largeTickCount;
        drawLargeTicks(painter, count, offset);
    }

    {
        const unsigned count =
            (largeTickCount + 1ul) * (m_middleTickCount + 1ul) + m_middleTickCount + 1ul;
        drawMiddleTicks(painter, count, offset);
    }

    {
        const unsigned count = largeTickCount;
        drawLargeTicksLabel(painter, count, offset);
    }

    // if (m_borderVisible)
    // {
    //     drawBorder(painter);
    // }

    if (m_groundVisible)
    {
        const auto y = (m_value * m_largeTickInterval) / m_interval - m_largeTickRect.height() / 2;
        const auto rect = QRect(QPoint(0, y + height() / 2 - m_largeTickLabelRect.height() / 2),
                                QPoint(width(), y + height() + m_largeTickLabelRect.height() / 2));

        // QLinearGradient linearGradient(rect.topLeft(), rect.bottomLeft());
        // linearGradient.setColorAt(0, Qt::transparent);
        // linearGradient.setColorAt(1, Qt::darkGreen);
        // const QBrush brush(linearGradient);

        const QBrush brush(m_brush);
        drawGround(painter, rect, brush);
    }
}

void LinearGauge::resizeEvent(QResizeEvent * /*event*/)
{
    auto stepSize = 0.f;
    const auto stepRatio = 0.05f;

    auto largeTickPadding = 0ul;
    auto largeTickThickness = 0ul;

    // Remove hidden tick (next tick that will be visible)
    const auto visibleLargeTick = m_largeTickCount * 2ul + 1ul + 1ul - 1ul;

    // Remove hidden tick from computation
    switch (m_orientation)
    {
    case Qt::Vertical:
    {
        stepSize = static_cast<float>(height()) / static_cast<float>(visibleLargeTick);
        const auto tickHeight = stepSize * stepRatio;
        largeTickThickness = static_cast<long>(tickHeight);

        largeTickPadding = m_padding + m_fontSize.width() + m_padding;
    }
    break;
    case Qt::Horizontal:
    {
        stepSize = static_cast<float>(width()) / static_cast<float>(visibleLargeTick);
        const auto tickWidth = stepSize * stepRatio;
        largeTickThickness = static_cast<long>(tickWidth);

        largeTickPadding = m_padding + m_fontSize.height() + m_padding;
    }
    break;
    }

    // Setup ticks interval
    const auto tickSpacer = stepSize * (1.f - stepRatio);
    m_largeTickInterval = largeTickThickness + tickSpacer;

    // Setup ticks position
    getTickPosition(m_largeTickRect, largeTickThickness, largeTickPadding);

    // Setup middle ticks
    const auto middleTickThickness = largeTickThickness / 2;
    const auto middleTickPadding = largeTickPadding + m_largeTickRect.width() / 4;

    // Setup ticks position
    getTickPosition(m_middleTickRect, middleTickThickness, middleTickPadding);

    // Setup small ticks
    const auto smallTickThickness = largeTickThickness / 4;
    const auto smallTickPadding = largeTickPadding + m_largeTickRect.width() / 2;

    // Setup ticks position
    getTickPosition(m_smallTickRect, smallTickThickness, smallTickPadding);

    // Setup ticks value
    initializeTicksLabelPosition(m_orientation, m_alignment);
}

void LinearGauge::initPainter(QPainter *painter) const
{
    // Set rendering quality
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);

    // Set theme color
    QPen pen(m_brush, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->setFont(m_font);
    painter->setBrush(m_brush);
}

void LinearGauge::getTickPosition(QRect &rect, int thickness, int padding)
{
    auto x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    // Set tick thickness depending on orientation
    switch (m_orientation)
    {
    case Qt::Horizontal:
    {
        x1 = width() / 2 - thickness;
        x2 = width() / 2 + thickness;
        break;
    }
    case Qt::Vertical:
    {
        y1 = height() / 2 - thickness;
        y2 = height() / 2 + thickness;
        break;
    }
    }

    // Set position depending on orientation and alignment
    switch (static_cast<int>(m_orientation) | static_cast<int>(m_alignment))
    {
    case Qt::Vertical | Qt::AlignLeft:
    {
        x1 = 0;
        x2 = width() - padding;
        break;
    }
    case Qt::Vertical | Qt::AlignRight:
    {
        x1 = padding;
        x2 = width();
        break;
    }
    case Qt::Vertical | Qt::AlignCenter:
    {
        x1 = padding;
        x2 = width() - padding;
        break;
    }
    case Qt::Horizontal | Qt::AlignTop:
    {
        y1 = 0;
        y2 = height() - padding;
        break;
    }
    case Qt::Horizontal | Qt::AlignBottom:
    {
        y1 = padding;
        y2 = height();
        break;
    }
    case Qt::Horizontal | Qt::AlignCenter:
    {
        y1 = padding;
        y2 = height() - padding;
        break;
    }
    }

    rect.setCoords(x1, y1, x2, y2);
}

void LinearGauge::initializeTicksLabelPosition(Qt::Orientation orientation, Qt::Alignment alignment)
{
    switch (static_cast<int>(orientation) | static_cast<int>(alignment))
    {
    case Qt::Vertical | Qt::AlignLeft:
    {
        const auto x = width() - m_padding - m_fontSize.width();
        const auto y = -m_largeTickLabelRect.height() / 2 + height() / 2;
        m_largeTickLabelRect.setTopLeft({ x, y });

        break;
    }
    case Qt::Vertical | Qt::AlignRight:
    {
        const auto x = m_padding;
        const auto y = -m_largeTickLabelRect.height() / 2 + height() / 2;
        m_largeTickLabelRect.setTopLeft({ x, y });

        break;
    }
    case Qt::Vertical | Qt::AlignCenter:
    {
        const auto x1 = m_padding;
        const auto y1 = -m_largeTickLabelRectLeft.height() / 2 + height() / 2;
        m_largeTickLabelRectLeft.setTopLeft({ x1, y1 });

        const auto x2 = width() - m_padding - m_largeTickLabelRectRight.width();
        const auto y2 = -m_largeTickLabelRectRight.height() / 2 + height() / 2;
        m_largeTickLabelRectRight.setTopLeft({ x2, y2 });

        break;
    }
    case Qt::Horizontal | Qt::AlignTop:
    {
        const auto x = width() / 2 - m_fontSize.width() / 2;
        const auto y = height() - m_padding - m_largeTickLabelRect.height();
        m_largeTickLabelRect.setTopLeft({ x, y });

        break;
    }
    case Qt::Horizontal | Qt::AlignBottom:
    {
        const auto x = width() / 2 - m_fontSize.width() / 2;
        const auto y = m_padding;
        m_largeTickLabelRect.setTopLeft({ x, y });

        break;
    }
    case Qt::Horizontal | Qt::AlignCenter:
    {
        const auto x1 = width() / 2 - m_fontSize.width() / 2;
        const auto y1 = m_padding;
        m_largeTickLabelRectTop.setTopLeft({ x1, y1 });

        const auto x2 = width() / 2 - m_fontSize.width() / 2;
        const auto y2 = height() - m_padding - m_largeTickLabelRect.height();
        m_largeTickLabelRectBottom.setTopLeft({ x2, y2 });

        break;
    }
    }

    std::vector<QRect *> ticksBoundingRect{ &m_largeTickLabelRect, &m_largeTickLabelRectLeft,
                                            &m_largeTickLabelRectRight, &m_largeTickLabelRectTop,
                                            &m_largeTickLabelRectBottom };

    const auto penWidth = 2;
    for (auto tickBounding : ticksBoundingRect)
    {
        tickBounding->setWidth(m_fontSize.width());
        tickBounding->setHeight(m_fontSize.height());
        tickBounding->adjust(0, 0, -penWidth / 2, -penWidth / 2);
    }
}

void LinearGauge::initializeTicksLabelValue(float value, unsigned long count, float interval)
{
    // Base drawn values on current value and remove the rest depending on interval
    const int offset = Common::Math::floor(value, interval);

    // Compute values range
    const auto start = (count / 2ul) * interval + offset;
    const auto stop = -(count / 2ul * interval - offset);

    // TODO: to improve
    m_vector.clear();
    m_vector.reserve(9);

    const auto _interval = static_cast<unsigned>(interval);

    // Fill array with step value
    for (auto value = start; value >= stop; value -= _interval)
    {
        m_vector.push_back(value);
    }
}

int LinearGauge::getNumber(const unsigned long pos) const
{
    return m_vector.at(pos);
}

// TODO: replace offset type float by int
void LinearGauge::drawLargeTicks(QPainter &painter, unsigned long count, float offset)
{
    // Start drawing the first tick at the top (first tick and last tick are hidden outside the
    // paint device) Add offset until next tick and so on
    for (auto i = 0ul; i <= count; ++i)
    {
        // Do not draw ticks and numbers for negative Y-axis
        if (m_groundVisible && getNumber(i) < 0)
            continue;

        const auto tmp = (static_cast<long>(i - count / 2ul)) * m_largeTickInterval + offset;

        auto x = 0, y = 0; // NOLINT(readability-isolate-declaration)
        (m_orientation == Qt::Vertical) ? y = tmp : x = tmp;

        QRect rect = m_largeTickRect.translated(x, y);

        // QLinearGradient linearGradient(rect.topLeft(), rect.bottomLeft());
        // linearGradient.setColorAt(0, Qt::transparent);
        // linearGradient.setColorAt(.5, m_brush.color());
        // linearGradient.setColorAt(1, Qt::transparent);
        // const QBrush brush(linearGradient);

        drawTick(painter, rect); //, brush);
    }
}

void LinearGauge::drawMiddleTicks(QPainter &painter, unsigned long count, float offset)
{
    const float interval = (m_largeTickInterval / (m_middleTickCount + 1ul));

    for (auto i = 0l; i <= count; ++i)
    {
        // if (m_groundVisible && getNumber(i) < 0) continue;
        //
        // Do not draw middle ticks for negative value
        // {
        //     continue;
        // }

        // Useless to draw middle tick on large tick
        if (i % (m_middleTickCount + 1) == 0)
            continue;

        const auto tmp = (i - static_cast<long>(count / 2ul)) * interval + offset;

        auto x = 0, y = 0;
        (m_orientation == Qt::Vertical) ? y = tmp : x = tmp;

        drawTick(painter, m_middleTickRect.translated(x, y));
    }
}

void LinearGauge::drawLargeTicksLabel(QPainter &painter, unsigned long count, float offset)
{
    if (m_alignment == Qt::AlignCenter)
    {
        for (auto i = 0l; i <= count; ++i)
        {
            if (m_groundVisible && getNumber(i) < 0)
                continue;

            auto x = 0, y = 0;
            const auto tmp = (i - static_cast<long>(count / 2ul)) * m_largeTickInterval + offset;

            if (m_orientation == Qt::Vertical)
            {
                y = tmp;
                drawLargeTickLabel(painter, m_largeTickLabelRectLeft.translated(x, y), getNumber(i),
                                   Qt::AlignVCenter | Qt::AlignRight);

                // TextItem m_largeTickTextItemLeft(QString::number(getNumber(i), m_font);
                // m_largeTickTextItemLeft.translate(x, y);
                // drawTextItem(painter, m_largeTickTextItemLeft);

                drawLargeTickLabel(painter, m_largeTickLabelRectRight.translated(x, y),
                                   getNumber(i), Qt::AlignVCenter | Qt::AlignLeft);
                // painter.drawRect(m_largeTickLabelRectRight.translated(x, y));
            }
            else
            {
                x = tmp;
                // drawLargeTickLabel(painter, m_largeTickLabelRectTop.translated(x, y),
                // getNumber(i), Qt::AlignHCenter | Qt::AlignBottom);
                painter.drawRect(m_largeTickLabelRectTop.translated(x, y));

                // drawLargeTickLabel(painter, m_largeTickLabelRectBottom.translated(x, y),
                // getNumber(i), Qt::AlignHCenter | Qt::AlignTop);
                painter.drawRect(m_largeTickLabelRectBottom.translated(x, y));
            }
        }
    }
    else
    {
        for (auto i = 0l; i <= count; ++i)
        {
            if (m_groundVisible && getNumber(i) <= 0)
                continue;

            const auto tmp = (i - static_cast<long>(count / 2ul)) * m_largeTickInterval + offset;

            auto x = 0, y = 0;
            (m_orientation == Qt::Vertical) ? y = tmp : x = tmp;

            // drawLargeTickLabel(painter, m_largeTickLabelRect.translated(x, y), getNumber(i),
            // Qt::AlignVCenter | m_alignment);
            painter.drawRect(m_largeTickLabelRect.translated(x, y));
        }
    }
}

bool LinearGauge::groundVisible() const
{
    return m_groundVisible;
}

void LinearGauge::setGroundVisible(bool visible)
{
    m_groundVisible = visible;
}

void LinearGauge::drawGround(QPainter &painter, const QRect &rect, const QBrush &brush)
{
    painter.fillRect(rect, brush);
}

void LinearGauge::drawBorder(QPainter &painter) const
{
    const auto widthF = static_cast<float>(width());
    const auto heightF = static_cast<float>(height());

    const std::vector<QPointF> boundingPoints{ { 0.f, 0.f },
                                               { widthF, 0.f },
                                               { widthF, heightF },
                                               { 0.f, heightF } };

    painter.drawPolyline(boundingPoints.data(), boundingPoints.size());
}
