/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "gauge_indicator/abstract_gauge.h"
#include "indicator/indicator_functions.h"

#include "QKeyEvent"
#include "qdebug.h"

using TicksPosition = AbstractGauge::TicksPosition;

// float positionFromValue(float value);
// float valueFromPosition(float position);

Qt::Alignment getLabelAlignment(TicksPosition position)
{
    switch (position)
    {
    case TicksPosition::TicksRight:
        return Qt::AlignVCenter | Qt::AlignRight;
    case TicksPosition::TicksLeft:
        return Qt::AlignVCenter | Qt::AlignLeft;
    case TicksPosition::TicksAbove:
        return Qt::AlignCenter;
    case TicksPosition::TicksBelow:
        return Qt::AlignCenter;
    default:
        assert(false);
    }
}

AbstractGauge::AbstractGauge(QWidget* parent)
    : QWidget(parent)
    , m_alignment(Qt::AlignRight)
    , m_orientation(Qt::Vertical)
    , m_ticksPosition(TicksRight)
    , m_labelVisible(true)
    , m_font("Cantarell", 16, QFont::Bold)
    , m_largeTickInterval(5.f)
    , m_largeTickCount(3ul)
    , m_middleTickCount(1ul)
    , m_smallTickCount(4ul)
    , m_value(0.f)
    , m_fontSize(textSize("-00", font()))
{
    setFocusPolicy(Qt::ClickFocus);

    // TODO: Adapt font size depending on widget size and digit count
    // Retrieve those from LabelItem
}

AbstractGauge::~AbstractGauge() = default;

/**
 * @brief This property holds the alignment of the ticks within the gauge.
 *
 * By default, the ticks are right-aligned.
 */
Qt::Alignment AbstractGauge::alignment() const
{
    return m_alignment;
}

void AbstractGauge::setAlignment(const Qt::Alignment alignment)
{
    m_alignment = alignment;
    QWidget::update();
}

/**
 * @brief This property holds the orientation of the gauge.
 *
 * The orientation must be Qt::Vertical (the default) or Qt::Horizontal.
 */
Qt::Orientation AbstractGauge::orientation() const
{
    return m_orientation;
}

void AbstractGauge::setOrientation(const Qt::Orientation orientation)
{
    m_orientation = orientation;
    QWidget::update();
}

TicksPosition AbstractGauge::ticksPosition() const
{
    return m_ticksPosition;
}

void AbstractGauge::setTicksPosition(TicksPosition position)
{
    m_ticksPosition = position;
    QWidget::update();
}

/**
 * @brief This property holds whether the labels is visible.
 */
bool AbstractGauge::labelVisible() const
{
    return m_labelVisible;
}

void AbstractGauge::setLabelVisible(bool visible)
{
    m_labelVisible = visible;
}

/**
 * @brief This property holds the font currently set for the labels.
 */
const QFont& AbstractGauge::font() const
{
    return m_font;
}

void AbstractGauge::setFont(const QFont& font)
{
    m_font = font;
    m_fontSize.setWidth(textWidth("-000"));
    m_fontSize.setHeight(textHeight(m_font));
}

float AbstractGauge::minimum() const
{
    return m_minimum;
}

void AbstractGauge::setMinimum(float minimum)
{
    if (m_minimum == minimum)
        return;

    m_minimum = minimum;
    QWidget::update();
}

float AbstractGauge::maximum() const
{
    return m_maximum;
}

void AbstractGauge::setMaximum(float maximum)
{
    if (m_maximum == maximum)
        return;

    m_maximum = maximum;
    QWidget::update();
}

/**
 * @brief This property holds the value interval between large ticks
 */
unsigned long AbstractGauge::largeTickInterval() const
{
    return m_largeTickInterval;
}

void AbstractGauge::setLargeTickInterval(unsigned long interval)
{
    m_largeTickInterval = interval;
    QWidget::update();
}

/**
 * @brief This property holds the number of large ticks.
 */
unsigned long AbstractGauge::largeTickCount() const
{
    return m_largeTickCount;
}

void AbstractGauge::setLargeTickCount(unsigned long numTicks)
{
    if (m_largeTickCount == numTicks)
        return;

    m_largeTickCount = numTicks;
    QWidget::update();
}

/**
 * @brief This property holds the number of middle ticks between two large ticks.
 */
unsigned long AbstractGauge::middleTickCount() const
{
    return m_middleTickCount;
}

void AbstractGauge::setMiddleTickCount(unsigned long numTicks)
{
    if (m_middleTickCount == numTicks)
        return;

    m_middleTickCount = numTicks;
    QWidget::update();
}

/**
 * @brief   This property holds the number of small ticks between two middle ticks.
 */
unsigned long AbstractGauge::smallTickCount() const
{
    return m_smallTickCount;
}

void AbstractGauge::setSmallTickCount(unsigned long numTicks)
{
    if (m_smallTickCount == numTicks)
        return;

    m_smallTickCount = numTicks;
    QWidget::update();
}

/**
 * @brief Sets the gauge's minimum to min and its maximum to max.
 *
 * If max is smaller than min, min becomes the only legal value.
 */
void AbstractGauge::setRange(float minimum, float maximum)
{
    if (m_minimum != minimum)
    {
        m_minimum = minimum;
        QWidget::update();
    }

    if (m_maximum != maximum)
    {
        m_maximum = maximum;
        QWidget::update();
    }
}

/**
 * @brief This property holds the number of middle ticks between two large ticks.
 *
 * The gauge forces the value to be within the legal range: minimum <= value <= maximum.
 */
float AbstractGauge::value() const
{
    return m_value;
}

void AbstractGauge::setValue(float value)
{
    m_value = value;
    QWidget::update();
}

/**
 * @brief Sets the value of the gauge to zero.
 */
void AbstractGauge::reset()
{
    AbstractGauge::setValue(0.f);
}

void AbstractGauge::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        m_value += .5f;
        break;
    case Qt::Key_Down:
        m_value -= .5f;
        break;
    default:
        return;
    }

    QWidget::update();

    QWidget::keyPressEvent(event);
}

void AbstractGauge::update(std::vector<QString>& labels)
{
    const size_t count = m_largeTickCount * 2ul + 1ul + 2ul;
    if (labels.size() <= 0ul)
    {
        labels.resize(count);
    }

    labels[0] = QString::number(m_maximum);
    for (auto i = 1ul; i < count; ++i)
    {
        bool ok = false;
        labels[i] = QString::number(labels[i - 1].toInt(&ok) - m_largeTickInterval);
        assert(ok == true);
    }
}
