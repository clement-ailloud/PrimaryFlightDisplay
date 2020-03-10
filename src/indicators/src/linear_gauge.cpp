
//!
//! \file	airspeed_indicator_view.cpp
//!
//! \brief	airspeed_indicator_view file description
//!
//! \date
//!
//! \author	Clement Ailloud
//!


#include "linear_gauge.h"

#include "qbrush.h"
#include "qpainter.h"
#include "qpen.h"
#include "qpoint.h"
#include "qrect.h"
#include "qsize.h"
#include "qstring.h"
#include "QKeyEvent"
#include "qfontmetrics.h"

#include "QStyleOptionGraphicsItem"

#include <cmath>


LinearGauge::LinearGauge(QGraphicsItem* parent, QGraphicsLayoutItem* parentLayout)
    : QGraphicsItem(parent)
    , QGraphicsLayoutItem(parentLayout)
    , m_value(0.f)
    , m_scaleLength(100)
    , m_largeTick(3)
    , m_largeTickInterval(40)
    , m_aligment(Alignment::AlignRight)
    , m_textVisible(true)
    , m_stepValue(5)
    , m_drawBorder(true)
    , m_boundingRect(std::move(QRectF(-50.f, -150.f, 100.f, 300.f)))
{
    init();

    // Set level as child of current indicator
//    m_movableLinearGaugeValue->setParentItem(this);
}


LinearGauge::~LinearGauge() = default;


void LinearGauge::init()
{
    // Required by QGraphicsLayoutItem
    setGraphicsItem(this);

    m_largeTickHeight = 2;

    m_penWidth = 1;

    m_drawRectHeight = m_largeTickHeight;

    m_font.setPixelSize(20);

    QFontMetrics fm(m_font);

    // Replace bounding rectangle
    m_textHeight = fm.height();

    m_textRect = fm.boundingRect("000");
    m_textRect.adjust(0, 0, -m_penWidth, -m_penWidth);
    m_textRect.moveCenter(QPoint(0, 0));

//    m_middleTickThickness = m_largeTickHeight / 2;

    m_borderTop = -m_largeTick * m_largeTickInterval - m_textHeight / 2;
    m_borderBot =  m_largeTick * m_largeTickInterval + m_textHeight / 2;

    m_drawStartY = -m_largeTickInterval * (m_largeTick + 1);
    m_drawStopY = m_largeTickInterval * m_largeTick;

    setAlignment(m_aligment);

    // Enable mouse selection for keyboard events
    setFlags(QGraphicsItem::ItemIsFocusable);

    // ?
//    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}


void LinearGauge::setAlignment(const Alignment alignment)
{
    const int textRectSpacing = 12;

    m_aligment = alignment;

    const int offset = 10;

    switch (m_aligment)
    {
        case LinearGauge::Alignment::AlignLeft:

            m_textRect.moveLeft(m_textRect.width());

            m_x1 = m_textRect.left() - m_textRect.width();//- textRectSpacing;

            m_textAlignment = Qt::AlignLeft;

            m_middleTickRect = QRect(m_x1, 0, offset, m_drawRectHeight);

            m_largeTickRect = QRect(m_x1, 0, 20, m_drawRectHeight);

            break;

        case LinearGauge::Alignment::AlignRight:

            m_x1 = m_textRect.x() + m_textRect.width() + textRectSpacing; m_x2 = m_x1;

            m_middleTickRect = QRect(m_x1 + offset, 0, offset, m_drawRectHeight);

            m_textAlignment = Qt::AlignRight;

            m_largeTickRect = QRect(m_x1, 0, 20, m_drawRectHeight);

            break;

        case LinearGauge::Alignment::AlignCenter:

            m_middleTickRect = QRect(-50, 0, 100, m_drawRectHeight);

            m_largeTickRect = QRect(-100, 0, 200, m_drawRectHeight);

            m_textAlignment = Qt::AlignCenter;

            break;

        default: break;
    }
}


void LinearGauge::setValue(const float value)
{
    m_value = value;
}


float LinearGauge::value() const
{
    return m_value;
}


void LinearGauge::reset()
{
    m_value = 0.f;
}


void LinearGauge::setTextVisible(const bool visible)
{
    m_textVisible = visible;
}


bool LinearGauge::textVisible() const
{
    return m_textVisible;
}


void LinearGauge::setBorder(const bool enable)
{
    m_drawBorder = enable;
}


QRectF LinearGauge::boundingRect() const
{
    return QRectF(QPointF(0,0), geometry().size());;
}


void LinearGauge::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/,
        QWidget* /*widget*/)
{
    // Clip area
    painter->setClipRect(m_boundingRect);
    painter->setFont(m_font);

//    painter->scale(-1.0, 1.0);

    if (m_drawBorder)
    {
	painter->setPen(QPen(QBrush(QColor("#7ec850")), 5));

        drawBoundingRect(painter);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////

    painter->setPen(QPen(QBrush(QColor("#7ec850")), m_penWidth));

    // Update drawn number
    std::vector<int> tab;
    //tab.resize();

    // Remove the rest to keep the right step
    m_drawOffsetValue = m_value - std::fmod(m_value, m_stepValue);

    const int startValue = m_largeTick * m_stepValue + m_stepValue + m_drawOffsetValue;
    const int stopValue = -m_largeTick * m_stepValue + m_drawOffsetValue;

    // Fill array with step value
    for (auto i = startValue; i >= stopValue; i -= m_stepValue)
    {
        tab.push_back(i);
    }

    auto j = 0;

    // Convert value into pixel offset
    const auto offset = std::fmod(valueToDraw(m_value, m_largeTickInterval / m_stepValue), 40.f);

    painter->setBrush(QBrush(QColor("#aa32cd32")));

    //!
    //! DRAW INDICATOR BACKGROUND
    //!

    for (auto i = m_drawStartY; i <= m_drawStopY; i += m_largeTickInterval)
    {
        const auto number = tab[j];

        // Do not print negative values
        if (number >= 0)
        {
            const auto y = i + offset + 1;

            // Recenter tick
            const auto yRect = y - m_drawRectHeight / 2;

            m_largeTickRect.moveTop(yRect);
            painter->drawRect(m_largeTickRect);
            // Draw large tick

            // Draw middle tick
            m_middleTickRect.moveTop(yRect - m_largeTickInterval / 2);
            painter->drawRect(m_middleTickRect);

            // Do not draw 0 value
            if (m_textVisible == true && number > 0)
            {
                // Recenter text
                const auto yText = y - m_textHeight / 2;

                m_textRect.moveTop(yText);
                painter->drawText(m_textRect, m_textAlignment, QString::number(number));
            }
        }

        j++; // Get next value to draw
    }

    const int yGround = (m_value * m_largeTickInterval) / m_stepValue;

    QLinearGradient linearGradient(m_boundingRect.topLeft(), m_boundingRect.bottomLeft());
    linearGradient.setColorAt(0, Qt::white);
    linearGradient.setColorAt(1, Qt::darkGreen);

    const QRect rect(m_boundingRect.x(), yGround, m_boundingRect.width(), m_boundingRect.height());
    const QBrush brush(linearGradient);

    drawGround(painter, rect, brush);
}


void LinearGauge::setGeometry(const QRectF& geometry)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geometry);
    setPos(geometry.topLeft());
}


QSizeF LinearGauge::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
	case Qt::MinimumSize:
	    break;

	case Qt::PreferredSize:

	    return m_boundingRect.size();

	case Qt::MaximumSize:
	    break;

	default:
	    break;
    }
    return constraint;
}


void LinearGauge::drawGround(QPainter* painter, const QRect &rect, const QBrush& brush)
{
    painter->fillRect(rect, brush);
}


//void LinearGauge::keyPressEvent(QKeyEvent* event)
//{
//    if (event)
//    {
//        static auto value = 0;
//
//        switch(event->key())
//        {
//            case Qt::Key_Up:
//
////                m_valueY++;
//                value = m_value;
//                value += (1.f / 40.f) * 5;
//
//                m_value += (1.f / 40.f);
//                break;
//
//            case Qt::Key_Down:
//
////                m_valueY--;
//                value = m_value;
//                value -= (1.f / 40.f) * 5;
//                m_value -= (1.f / 40.f);
//
//                break;
//
//            default: break;
//        }
//
//        if (m_value >= .0f)
//        {
//            m_movableLinearGaugeValue->setValue(m_value);
//
//            update();
//        }
//    }
//}


int LinearGauge::valueToDraw(const float value, const int step) const
{
    return value * step;
}


void LinearGauge::drawBoundingRect(QPainter* painter) const
{
    const std::array<QPointF, 4> boundingRectItem = {
        m_boundingRect.topLeft(),
        m_boundingRect.topRight(),
        m_boundingRect.bottomRight(),
        m_boundingRect.bottomLeft()
    };

    painter->drawPolyline(boundingRectItem.data(), boundingRectItem.size());
}
