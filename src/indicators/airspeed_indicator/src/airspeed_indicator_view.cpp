/*
 * @file	airspeed_indicator_view.cpp
 *
 * @brief	airspeed_indicator_view file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */



#include "airspeed_indicator_view.h"

#include "graphics_layout_item.h"
#include "linear_gauge.h"
#include "linear_gauge_value.h"


using namespace View;


AirspeedIndicator::AirspeedIndicator(QGraphicsItem* parent, QGraphicsLayoutItem* parentLayout)
    : QGraphicsItemGroup(parent)
    , QGraphicsLayoutItem(parentLayout)
    , m_linearGauge(std::make_unique<LinearGauge>(this, this))
    , m_linearGaugeValue(std::make_unique<LinearGaugeValue>(this, this))
{
    m_linearGauge->setGeometry(QRectF(-50.f, -150.f, 100.f, 300.f));
}


AirspeedIndicator::~AirspeedIndicator()
{
}


void AirspeedIndicator::setBoundingRect(const QRectF& boundingRect)
{
    m_linearGauge->setBoundingRect(boundingRect);
}


void AirspeedIndicator::setSpeed(const int speed)
{
    if (speed != m_speed)
    {
        m_speed = speed;

	m_linearGauge->setValue(m_speed);
	m_linearGaugeValue->setValue(m_speed);
    }
}


QSizeF AirspeedIndicator::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
	case Qt::MinimumSize:
	    break;

	case Qt::PreferredSize:

	    return m_linearGauge->geometry().size();

	case Qt::MaximumSize:
	    break;

	default:
	    break;
    }
    return constraint;
}
