#ifndef __PRIMARY_FLIGHT_DISPLAY_H
#define __PRIMARY_FLIGHT_DISPLAY_H

#include "primary_flight_display_view_interface.h"

#include "qpointer.h"
#include "qwidget.h"

class QGridLayout;
class QHBoxLayout;

namespace View
{
class AirspeedIndicator;
class AltitudeIndicator;
class AttitudeIndicator;
class HeadingIndicator;

class PrimaryFlightDisplay
    : public QWidget
    , public IPrimaryFlightDisplayView
{
public:
    PrimaryFlightDisplay(QWidget* parent = nullptr);

    PrimaryFlightDisplay(const PrimaryFlightDisplay& display);
    PrimaryFlightDisplay& operator=(const PrimaryFlightDisplay& display);

    PrimaryFlightDisplay(PrimaryFlightDisplay&& display);
    PrimaryFlightDisplay& operator=(PrimaryFlightDisplay&& display);

    ~PrimaryFlightDisplay() override;

    void setSpeed(float speed) override;
    void setVerticalSpeed(float) override;
    void setAltitude(float) override;
    void setHeading(float) override;

private:
    QPointer<QGridLayout> m_gridLayout;
    QPointer<QHBoxLayout> m_linearLayout;
    QPointer<AirspeedIndicator> m_speedIndicator;
    QPointer<AltitudeIndicator> m_altitudeIndicator;
    QPointer<AttitudeIndicator> m_attitudeIndicator;
    QPointer<HeadingIndicator> m_headingIndicator;
};

} // namespace View

#endif
