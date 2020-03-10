#ifndef __PRIMARY_FLIGHT_DISPLAY_H
#define __PRIMARY_FLIGHT_DISPLAY_H

#include "primary_flight_display_view_interface.h"

#include "QGraphicsWidget"

#include <memory>


class QGraphicsGridLayout;


namespace View
{
class AirspeedIndicator;
class AttitudeIndicator;

class PrimaryFlightDisplay final : public IPrimaryFlightDisplayView, public QGraphicsWidget
{
    public:

        PrimaryFlightDisplay(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = 0);
        PrimaryFlightDisplay(const PrimaryFlightDisplay& display);
        PrimaryFlightDisplay(PrimaryFlightDisplay&& display);

        ~PrimaryFlightDisplay();

        void setSpeed(float) override;

        void setVerticalSpeed(float) override;

        void setAltitude(float) override;

        void setHeading(float) override;


    private:

	std::unique_ptr<QGraphicsGridLayout> m_graphicsGridLayout;
        std::unique_ptr<View::AirspeedIndicator> m_speedIndicator;
	std::unique_ptr<View::AttitudeIndicator> m_attitudeIndicator;
};

} // namespace View

#endif
