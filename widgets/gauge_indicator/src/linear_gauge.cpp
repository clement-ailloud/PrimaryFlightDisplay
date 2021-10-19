
/**
 * @file	linear_gauge.h
 *
 * @brief	linear_gauge.h file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#include "gauge_indicator/linear_gauge.h"

#include "gauge_indicator/private/linear_gauge_private.h"

#include "indicator/indicator_functions.h"

#include "qbrush.h"
#include "qcolor.h"
#include "qdebug.h"
#include "qfontmetrics.h"
#include "qpainter.h"
#include "qpen.h"
#include "qpoint.h"
#include "qsize.h"

#include <cassert>

#include <algorithm>

using TicksPosition = AbstractGauge::TicksPosition;

/**
 *  Write a GTest fixture with abritrary widget settings width, height...
 *
 *  The test shall ensure the position of the ticks and labels are well set as well as the offset
 *  position increment when increment/decrement the value of the gauge.
 */

constexpr auto g_penWidth{ 1 };
constexpr auto g_horizontalPadding{ 30 }; //<! Padding wrapping the text of the tick's value.
constexpr auto g_verticalPadding{ 5 };    //<! Padding wrapping the text of the tick's value.
// auto g_largeTickPositionInterval{0.f};

const QBrush m_brush(QColor("#7ec850"));
std::vector<int> g_vector; //!< Temporary container used to store data that will be displayed
std::vector<QString> g_labels;

int getLabel(const size_t pos)
{
    return g_vector[pos];
}

LinearGauge::LinearGauge(QWidget* parent)
    : AbstractGauge(parent)
    , g_largeTickPositionInterval(0.f)
    , m_borderPosition(BorderPosition::BorderRight | BorderPosition::BorderTop |
                       BorderPosition::BorderRight | BorderPosition::BorderBottom)
    , m_borderVisible(true)
    , m_borderWidth(4)
    , m_groundVisible(true)
{
    m_largeTickLabelRect.setSize(m_fontSize);
    m_largeTickLabelRectLeft.setSize(m_fontSize);
    m_largeTickLabelRectRight.setSize(m_fontSize);
    m_largeTickLabelRectTop.setSize(m_fontSize);
    m_largeTickLabelRectBottom.setSize(m_fontSize);
}

LinearGauge::~LinearGauge() = default;

/**
 * @brief   Returns true whether the widget's border is visible.
 *
 * Make widget's border visible.
 */
bool LinearGauge::borderVisible() const
{
    return m_borderVisible;
}

void LinearGauge::setBorderVisible(const bool visible)
{
    if (m_borderVisible == visible)
        return;

    m_borderVisible = visible;
    QWidget::update();
}

int LinearGauge::borderPosition() const
{
    return m_borderPosition;
}

void LinearGauge::setBorderPosition(int flags)
{
    if (m_borderPosition == flags)
        return;

    m_borderPosition = flags;
    QWidget::update();
}

int LinearGauge::borderWidth() const
{
    return m_borderWidth;
}

void LinearGauge::setBorderWidth(int width)
{
    if (m_borderWidth == width)
        return;

    m_borderWidth = width;
    QWidget::update();
}

/**
 * @brief   Returns true whether the ground is visible.
 */
bool LinearGauge::groundVisible() const
{
    return m_groundVisible;
}

void LinearGauge::setGroundVisible(bool visible)
{
    if (m_groundVisible == visible)
        return;

    m_groundVisible = visible;
    QWidget::update();
}

/**
 * @brief   Scrolling 2D background
 *
 *          Refresh each time value changed
 *
 * TODO: see QWidget::scroll(int dx, int dy)
 */
void LinearGauge::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

    // Remove pen width used for drawing
    // TODO: Test with big pen width
    // largeTickLabelRect.adjust(0, 0, -g_penWidth / 2, -g_penWidth / 2);

    // static auto min = value() - largeTickInterval();
    // static auto max = value() + largeTickInterval();
    //
    // if (value() >= max)
    // {
    //     std::cout << "emit overflow()\n";
    // }
    //
    // if (value() <= min)
    // {
    //     std::cout << "emit overflow()\n";
    // }
    //
    // min = Common::Math::floor(value(), largeTickInterval());
    // max = Common::Math::ceil(value(), largeTickInterval());

    // * 2 for top and bottom, add one for centered tick and two for hidden ticks
    const auto _largeTickCount = largeTickCount() * 2ul + 1ul + 2ul;

    if (g_labels.size() != _largeTickCount)
    {
        g_labels.resize(_largeTickCount);
    }

    update(g_labels);

    const auto tickPosition =
        tickPositionFromValue(value(), largeTickInterval(), g_largeTickPositionInterval);

    {
        const size_t count = _largeTickCount;
        drawLargeTicks(painter, count, tickPosition);
    }

    {
        const size_t count = _largeTickCount * (middleTickCount() + 1ul) + middleTickCount() + 1ul;
        drawMiddleTicks(painter, count, tickPosition);
    }

    {
        const size_t count = _largeTickCount;
        drawLargeTicksLabel(painter, count, tickPosition);
    }

    if (m_groundVisible)
    {
        const auto y = (value() * g_largeTickPositionInterval) / largeTickInterval();
        const auto rect = QRect(QPoint(0, y + height() / 2), QPoint(width(), y + height()));

        // QLinearGradient linearGradient(rect.topLeft(), rect.bottomLeft());
        // linearGradient.setColorAt(0, Qt::transparent);
        // linearGradient.setColorAt(1, Qt::darkGreen);
        // const QBrush brush(linearGradient);

        const QBrush brush(m_brush);
        drawGround(painter, rect, brush);
    }

    if (m_borderVisible)
    {
        drawBorder(painter, size(), m_borderPosition);
    }
}

void LinearGauge::resizeEvent(QResizeEvent* /*event*/)
{
    auto stepSize = 0.f;
    const auto stepRatio = 0.015f;

    auto largeTickPadding = 0ul;
    auto largeTickThickness = 0ul;

    // Remove hidden tick (next tick that will be visible)
    const auto visibleLargeTick = static_cast<float>(largeTickCount()) * 2.f + 1.f + 1.f - 1.f;

    // Remove hidden tick from computation
    switch (orientation())
    {
    case Qt::Vertical:
    {
        stepSize = static_cast<float>(height()) / visibleLargeTick;
        const auto tickHeight = stepSize * stepRatio;
        largeTickThickness = static_cast<unsigned long>(tickHeight);

        largeTickPadding = m_fontSize.width() + m_fontSize.width() / 2;
    }
    break;
    case Qt::Horizontal:
    {
        stepSize = static_cast<float>(width()) / visibleLargeTick;
        const auto tickWidth = stepSize * stepRatio;
        largeTickThickness = static_cast<unsigned long>(tickWidth);

        largeTickPadding = g_verticalPadding + m_fontSize.height() + g_verticalPadding;
    }
    break;
    }

    // Setup ticks interval
    const auto tickSpacer = stepSize * (1.f - stepRatio);
    g_largeTickPositionInterval = static_cast<float>(largeTickThickness) + tickSpacer;

    // Setup large ticks position
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
    setTicksLabelPosition(orientation(), ticksPosition());
}

void LinearGauge::update(std::vector<QString>& labels)
{
    setTicksLabelValue(g_vector, value(), largeTickInterval(), labels.size());
    std::transform(g_vector.cbegin(), g_vector.cend(), labels.begin(),
                   [](const auto label) { return QString::number(label); });
}

void LinearGauge::initPainter(QPainter* painter) const
{
    // Set rendering quality
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);

    // Set theme color
    QPen pen(m_brush, g_penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->setFont(font());
    painter->setBrush(m_brush);
}

void LinearGauge::getTickPosition(QRect& rect, int thickness, int padding)
{
    auto x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    // Set tick thickness depending on orientation
    switch (orientation())
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
    switch (static_cast<int>(orientation()) | static_cast<int>(ticksPosition()))
    {
    case Qt::Vertical | TicksPosition::TicksLeft:
    {
        x1 = 0;
        x2 = width() - padding;
        break;
    }
    case Qt::Vertical | TicksPosition::TicksRight:
    {
        x1 = padding;
        x2 = width();
        break;
    }
    case Qt::Vertical | TicksPosition::TicksCenter:
    {
        x1 = padding;
        x2 = width() - padding;
        break;
    }
    case Qt::Horizontal | TicksPosition::TicksAbove:
    {
        y1 = 0;
        y2 = height() - padding;
        break;
    }
    case Qt::Horizontal | TicksPosition::TicksBelow:
    {
        y1 = padding;
        y2 = height();
        break;
    }
    case Qt::Horizontal | TicksPosition::TicksCenter:
    {
        y1 = padding;
        y2 = height() - padding;
        break;
    }
    default:
        assert(false);
    }

    rect.setCoords(x1, y1, x2, y2);
}

void LinearGauge::setTicksLabelPosition(Qt::Orientation orientation, TicksPosition position)
{
    switch (static_cast<int>(orientation) | static_cast<int>(position))
    {
    case Qt::Vertical | TicksPosition::TicksLeft:
    {
        const auto x = width() - g_penWidth - m_fontSize.width();
        const auto y = -m_largeTickLabelRect.height() / 2 + height() / 2;
        m_largeTickLabelRect.moveTopLeft({ x, y });

        break;
    }
    case Qt::Vertical | TicksPosition::TicksRight:
    {
        const auto x = 0;
        const auto y = -m_largeTickLabelRect.height() / 2 + height() / 2;
        m_largeTickLabelRect.moveTopLeft({ x, y });

        break;
    }
    case Qt::Vertical | TicksPosition::TicksCenter:
    {
        const auto x1 = 0;
        const auto y1 = -m_largeTickLabelRectLeft.height() / 2 + height() / 2;
        m_largeTickLabelRectLeft.moveTopLeft({ x1, y1 });

        const auto x2 = width() - m_largeTickLabelRectRight.width();
        const auto y2 = -m_largeTickLabelRectRight.height() / 2 + height() / 2;
        m_largeTickLabelRectRight.moveTopLeft({ x2, y2 });

        break;
    }
    case Qt::Horizontal | TicksPosition::TicksAbove:
    {
        const auto x = width() / 2 - m_fontSize.width() / 2;
        const auto y = height() - g_verticalPadding - m_largeTickLabelRect.height();
        m_largeTickLabelRect.moveTopLeft({ x, y });

        break;
    }
    case Qt::Horizontal | TicksPosition::TicksBelow:
    {
        const auto x = width() / 2 - m_fontSize.width() / 2;
        const auto y = g_verticalPadding;
        m_largeTickLabelRect.moveTopLeft({ x, y });

        break;
    }
    case Qt::Horizontal | TicksPosition::TicksCenter:
    {
        const auto x1 = width() / 2 - m_fontSize.width() / 2;
        const auto y1 = g_verticalPadding;
        m_largeTickLabelRectTop.moveTopLeft({ x1, y1 });

        const auto x2 = width() / 2 - m_fontSize.width() / 2;
        const auto y2 = height() - g_verticalPadding - m_largeTickLabelRect.height();
        m_largeTickLabelRectBottom.moveTopLeft({ x2, y2 });

        break;
    }
    }
}

// TODO: replace offset type float by int
void LinearGauge::drawLargeTicks(QPainter& painter, unsigned long count, float offset)
{
    // Start drawing the first tick at the top (first tick and last tick are hidden outside the
    // paint device). Add offset for the next tick and so on until the last one.
    for (auto i = 0ul; i < count; ++i)
    {
        // Do not draw ticks and numbers for negative Y-axis
        if (m_groundVisible && getLabel(i) <= 0)
            continue;

        const auto tmp =
            (static_cast<long>(i - count / 2ul)) * g_largeTickPositionInterval + offset;

        auto x = 0, y = 0; // NOLINT(readability-isolate-declaration)
        (orientation() == Qt::Vertical) ? y = tmp : x = tmp;

        drawTick(painter, m_largeTickRect.translated(x, y)); //, brush);
    }
}

void LinearGauge::drawMiddleTicks(QPainter& painter, unsigned long count, float offset)
{
    const float interval = (g_largeTickPositionInterval / (middleTickCount() + 1ul));

    for (auto i = 0l; i < count; ++i)
    {
        // Do not draw middle ticks for negative value
        // if (m_groundVisible && getLabel(i) <= 0)
        //     continue;

        // Useless to draw middle tick on large tick
        if (i % (middleTickCount() + 1) == 0)
            continue;

        const auto tmp = (i - static_cast<long>(count / 2ul)) * interval + offset;

        auto x = 0, y = 0;
        (orientation() == Qt::Vertical) ? y = tmp : x = tmp;

        drawTick(painter, m_middleTickRect.translated(x, y));
    }
}

void LinearGauge::drawLargeTicksLabel(QPainter& painter, unsigned long count, float offset)
{
    if (ticksPosition() == TicksPosition::TicksCenter)
    {
        for (auto i = 0l; i < count; ++i)
        {
            if (m_groundVisible && getLabel(i) < 0)
                continue;

            auto x = 0, y = 0;
            const auto tmp =
                (i - static_cast<long>(count / 2ul)) * g_largeTickPositionInterval + offset;

            if (orientation() == Qt::Vertical)
            {
                y = tmp;
                drawLargeTickLabel(painter, m_largeTickLabelRectLeft.translated(x, y), getLabel(i),
                                   getLabelAlignment(TicksPosition::TicksRight));

                // TextItem m_largeTickTextItemLeft(QString::number(getLabel(i), font());
                // m_largeTickTextItemLeft.translate(x, y);
                // drawTextItem(painter, m_largeTickTextItemLeft);

                drawLargeTickLabel(painter, m_largeTickLabelRectRight.translated(x, y), getLabel(i),
                                   getLabelAlignment(TicksPosition::TicksLeft));
                // painter.drawRect(m_largeTickLabelRectRight.translated(x, y));
            }
            else
            {
                x = tmp;
                // drawLargeTickLabel(painter, m_largeTickLabelRectTop.translated(x, y),
                // getLabel(i), Qt::AlignHCenter | Qt::AlignBottom);
                painter.drawRect(m_largeTickLabelRectTop.translated(x, y));

                // drawLargeTickLabel(painter, m_largeTickLabelRectBottom.translated(x, y),
                // getLabel(i), Qt::AlignHCenter | Qt::AlignTop);
                painter.drawRect(m_largeTickLabelRectBottom.translated(x, y));
            }
        }
    }
    else
    {
        for (auto i = 0l; i < count; ++i)
        {
            if (m_groundVisible && getLabel(i) <= 0)
                continue;

            const auto tmp =
                (i - static_cast<long>(count / 2ul)) * g_largeTickPositionInterval + offset;

            auto x = 0, y = 0;
            if (orientation() == Qt::Vertical)
            {
                y = tmp;
            }
            else
            {
                x = tmp;
            }

            drawLargeTickLabel(painter, m_largeTickLabelRect.translated(x, y), getLabel(i),
                               getLabelAlignment(ticksPosition()));
            // painter.setBrush(Qt::NoBrush);
            // painter.drawRect(m_largeTickLabelRect.translated(x, y));
        }
    }
}
