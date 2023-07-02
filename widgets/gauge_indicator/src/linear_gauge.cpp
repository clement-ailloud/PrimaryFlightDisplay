
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

constexpr auto g_penWidth{ 2 };
constexpr auto g_horizontalPadding{ 30 }; //<! Padding wrapping the text of the tick's value.
constexpr auto g_verticalPadding{ 5 };    //<! Padding wrapping the text of the tick's value.
// auto m_stepSpan{0.f};

const QBrush m_brush(QColor("#7ec850"));
std::vector<int> g_vector; //!< Temporary container used to store data that will be displayed
std::vector<QString> g_labels;

int getLabel(const size_t pos)
{
    return g_vector[pos];
}

LinearGauge::LinearGauge(QWidget* parent)
    : AbstractGauge(parent)
    , m_stepSpan(0.f)
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

    painter.drawLine(0, height() / 2, width(), height() / 2);

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

    const auto tickPosition = tickPositionFromValue(value(), largeTickInterval(), m_stepSpan);

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
        const auto y = (value() * m_stepSpan) / largeTickInterval();
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
    // Remove hidden tick (e.g next tick that will be visible)
    const auto visibleLargeTick = largeTickCount() * 2ul + 1ul + 1ul - 1ul;

    auto largeTickPadding = 0ul;
    switch (orientation())
    {
    case Qt::Vertical:
    {
        largeTickPadding = m_fontSize.width() + m_fontSize.width() / 2;
    }
    break;
    case Qt::Horizontal:
    {
        largeTickPadding = g_verticalPadding + m_fontSize.height() + g_verticalPadding;
    }
    break;
    }

    m_stepSpan = getStepSpan<float>(size(), visibleLargeTick, orientation());

    const auto tickSpanRatio = 0.02;
    const auto largeTickspan = m_stepSpan * tickSpanRatio;

    // Setup large ticks size and position
    getTickCoordinates(m_largeTickRect, largeTickspan, largeTickPadding, orientation(),
                       ticksPosition());

    // Setup middle ticks
    const auto middleTickSpan = largeTickspan / 2;
    const auto middleTickPadding =
        getMiddleTickPadding(m_largeTickRect.size(), largeTickPadding, orientation());

    // Setup middle ticks size and position
    getTickCoordinates(m_middleTickRect, middleTickSpan, middleTickPadding, orientation(),
                       ticksPosition());

    // Setup small ticks
    const auto smallTickSpan = largeTickspan / 4;
    const auto smallTickPadding =
        getSmallTickPadding(m_largeTickRect.size(), largeTickPadding, orientation());

    // Setup ticks size and position
    getTickCoordinates(m_smallTickRect, smallTickSpan, smallTickPadding, orientation(),
                       ticksPosition());

    // Move ticks value according to window size
    moveTicksLabel(orientation(), ticksPosition());
}

void LinearGauge::update(std::vector<QString>& labels)
{
    updateTicksLabelValue(g_vector, value(), largeTickInterval(), labels.size());
    std::transform(g_vector.cbegin(), g_vector.cend(), labels.begin(),
                   [](const auto label) { return QString::number(label); });
}

void LinearGauge::initPainter(QPainter* painter) const
{
#ifdef NDEBUG
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
#endif

    // Set theme color
#ifdef NDEBUG
    QPen pen(m_brush, g_penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
#else
    QPen pen(m_brush, g_penWidth);
#endif
    painter->setPen(pen);
    painter->setFont(font());
    painter->setBrush(m_brush);
}

void LinearGauge::getTickCoordinates(QRect& rect, int span, int padding,
                                     Qt::Orientation orientation, TicksPosition ticksPosition)
{
    auto x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    // Set tick span depending on orientation
    switch (orientation)
    {
    case Qt::Horizontal:
    {
        x1 = width() / 2 - span;
        x2 = width() / 2 + span;
        break;
    }
    case Qt::Vertical:
    {
        y1 = height() / 2 - span;
        y2 = height() / 2 + span;
        break;
    }
    }

    // Set position depending on orientation and alignment
    switch (static_cast<int>(orientation) | static_cast<int>(ticksPosition))
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

void LinearGauge::moveTicksLabel(Qt::Orientation orientation, TicksPosition position)
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

        const auto tmp = (static_cast<long>(i - count / 2ul)) * m_stepSpan + offset;

        auto x = 0, y = 0; // NOLINT(readability-isolate-declaration)
        (orientation() == Qt::Vertical) ? y = tmp : x = tmp;

        drawTick(painter, m_largeTickRect.translated(x, y)); //, brush);
    }
}

void LinearGauge::drawMiddleTicks(QPainter& painter, unsigned long count, float offset)
{
    const float interval = (m_stepSpan / (middleTickCount() + 1ul));

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
        (orientation() == Qt::Vertical) ? y = tmp - m_middleTickRect.height() / 2 : x = tmp;

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

            const auto tmp = (i - static_cast<long>(count / 2ul)) * m_stepSpan + offset;

            auto x = 0, y = 0;
            if (orientation() == Qt::Vertical)
            {
                painter.setBrush(Qt::NoBrush);
                painter.drawRect(m_largeTickLabelRectLeft);
                y = tmp;
                drawLargeTickLabel(painter, m_largeTickLabelRectLeft.translated(x, y), getLabel(i),
                                   getLabelAlignment(TicksPosition::TicksRight));

                drawLargeTickLabel(painter, m_largeTickLabelRectRight.translated(x, y), getLabel(i),
                                   getLabelAlignment(TicksPosition::TicksLeft));
            }
            else
            {
                x = tmp;
                painter.drawRect(m_largeTickLabelRectTop.translated(x, y));
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

            const auto tmp = (i - static_cast<long>(count / 2ul)) * m_stepSpan + offset;

            auto x = 0, y = 0;
            (orientation() == Qt::Vertical) ? y = tmp : x = tmp;
            drawLargeTickLabel(painter, m_largeTickLabelRect.translated(x, y), getLabel(i),
                               getLabelAlignment(ticksPosition()));
        }
    }
}
