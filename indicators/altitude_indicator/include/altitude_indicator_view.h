/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */


#ifndef __ALTITUDE_INDICATOR_VIEW_H
#define __ALTITUDE_INDICATOR_VIEW_H

#include "qwidget.h"

#include "qpointer.h"

class LinearGauge;
class LinearGaugeValue;
class QHBoxLayout;

namespace View
{

class AltitudeIndicator : public QWidget
{
    public:

	AltitudeIndicator(QWidget* parent = nullptr);

        // Copy constructor and assignment
	AltitudeIndicator(const AltitudeIndicator&) = delete;
        AltitudeIndicator& operator=(const AltitudeIndicator&) = delete;

        // Move constructor and assignment
	AltitudeIndicator(AltitudeIndicator&&) = delete;
        AltitudeIndicator& operator=(AltitudeIndicator&&) = delete;

	~AltitudeIndicator() override;

        int altitude() const;
	void setAltitude(int altitude);

    private:

        QPointer<QHBoxLayout> m_linearLayout;
        QPointer<LinearGauge> m_linearGauge;
	QPointer<LinearGaugeValue> m_linearGaugeValue;
};

}

#endif
