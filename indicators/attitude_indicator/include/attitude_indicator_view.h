/**
 * @file	attitude_indicator_view.h
 *
 * @brief	attitude_indicator_view file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#ifndef __ATTITUDE_INDICATOR_VIEW_H
#define __ATTITUDE_INDICATOR_VIEW_H

#include "qwidget.h"

#include "qpointer.h"

class FlightDirectorSystem;
class QHBoxLayout;
class LinearGauge;
class LinearGaugeValue;

namespace View
{

class AttitudeIndicator : public QWidget
{
    public:

        AttitudeIndicator(QWidget* parent = nullptr);

        // Copy constructor and assignment
	AttitudeIndicator(const AttitudeIndicator&) = delete;
        AttitudeIndicator& operator=(const AttitudeIndicator&) = delete;

        // Move constructor and assignment
	AttitudeIndicator(AttitudeIndicator&&) = delete;
        AttitudeIndicator& operator=(AttitudeIndicator&&) = delete;

        ~AttitudeIndicator() override;

	/*
	 * @fn	    setFlightDirectorSystem(FlightDirectorSystem& fds
	 * @brief   add information from the navigation system to facilitate the steering
	 * @param   FlightDirectorSystem&
	 */
        void setFlightDirectorSystem(FlightDirectorSystem& fds);

    private:

        QPointer<QHBoxLayout> m_linearLayout;
	QPointer<LinearGauge> m_linearGauge;
	QPointer<LinearGaugeValue> m_linearGaugeValue;
};

}

#endif
