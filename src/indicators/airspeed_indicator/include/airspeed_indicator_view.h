
//!
//! \file	airspeed_indicator_view.h
//!
//! \brief	airspeed_indicator_view.h file description
//!
//! \date
//!
//! \author	Clement Ailloud
//!
//!



#ifndef __AIRSPEED_INDICATOR_VIEW_H
#define __AIRSPEED_INDICATOR_VIEW_H


#include "QGraphicsItemGroup"
#include "QGraphicsLayoutItem"

#include <memory>

#include "QSizeF"


class QGraphicsItem;
class QGraphicsLayoutItem;
class LinearGauge;
class LinearGaugeValue;


namespace View {


class AirspeedIndicator : public QGraphicsItemGroup, public QGraphicsLayoutItem
{
    public:

	AirspeedIndicator(QGraphicsItem* parent = nullptr,
			  QGraphicsLayoutItem* parentLayout = nullptr);

	AirspeedIndicator(const AirspeedIndicator&) = delete;
	AirspeedIndicator(AirspeedIndicator&&) = delete;

	virtual ~AirspeedIndicator();

	void setBoundingRect(const QRectF& boundingRect);

	// TODO: remove later because already stored as value in linear gauge
	void setSpeed(int speed);

	AirspeedIndicator& operator=(const AirspeedIndicator&) = delete;
	AirspeedIndicator& operator=(AirspeedIndicator&&) = delete;

//        void updateGeometry() override;


    protected:

	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;


    private:

	// TODO: remove later because already stored as value in linear gauge
	float m_speed;

	std::unique_ptr<LinearGauge> m_linearGauge;
	std::unique_ptr<LinearGaugeValue> m_linearGaugeValue;
};

}

#endif
