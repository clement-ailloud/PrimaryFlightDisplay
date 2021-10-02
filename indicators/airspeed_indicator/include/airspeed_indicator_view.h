/**
 * @file	airspeed_indicator_view.h
 *
 * @brief	airspeed_indicator_view file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#ifndef __AIRSPEED_INDICATOR_VIEW_H
#define __AIRSPEED_INDICATOR_VIEW_H

#include "qwidget.h"

#include "qpointer.h"

class LinearGauge;
class LinearGaugeValue;
class QHBoxLayout;

namespace View
{

class AirspeedIndicator : public QWidget
{
    public:

	AirspeedIndicator(QWidget* parent = nullptr);

        // Copy constructor and assignment
	AirspeedIndicator(const AirspeedIndicator&) = delete;
        AirspeedIndicator& operator=(const AirspeedIndicator&) = delete;

        // Move constructor and assignment
	AirspeedIndicator(AirspeedIndicator&&) = delete;
        AirspeedIndicator& operator=(AirspeedIndicator&&) = delete;

	~AirspeedIndicator() override;

        int speed() const;
	void setSpeed(int speed);

    private:

        QPointer<QHBoxLayout> m_linearLayout;
        QPointer<LinearGauge> m_linearGauge;
	QPointer<LinearGaugeValue> m_linearGaugeValue;
};

}

#endif
