#include "attitude_indicator_view.h"

#include "graphics_layout_item.h"
#include "linear_gauge.h"

//#include "attitude_indicator_symbol.h"

// Move assist
//#include "flight_director.h"


using namespace View;


AttitudeIndicator::AttitudeIndicator(QGraphicsItem* parent, QGraphicsLayoutItem* parentLayout)
    : QGraphicsItemGroup(parent)
    , QGraphicsLayoutItem(parentLayout)
    , m_linearGauge(std::make_unique<LinearGauge>(this, this))
{
    m_linearGauge->setGeometry(QRectF(-50.f, -150.f, 100.f, 300.f));
    m_linearGauge->setAlignment(LinearGauge::AlignCenter);
    m_linearGauge->setTextVisible(false);
    m_linearGauge->setBorder(false);

//    m_attitudeIndicatorSymbol = std::make_unique<AttitudeIndicatorSymbol>(parent);

    // Items representing the Attitude Indicator (symbol + with flight director overlay)
//    QGraphicsItemGroup* group = new QGraphicsItemGroup();
//    group->addToGroup(m_levelIndicator->graphicsItem());
//    group->addToGroup(m_attitudeIndicatorSymbol);
}


AttitudeIndicator::~AttitudeIndicator()
{
}


void AttitudeIndicator::setGeometry(const QRectF& geometry)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geometry);
    setPos(geometry.topLeft());
}


QSizeF AttitudeIndicator::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
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
