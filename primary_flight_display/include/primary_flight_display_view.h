#ifndef PRIMARY_FLIGHT_DISPLAY_H
#define PRIMARY_FLIGHT_DISPLAY_H

#include "primary_flight_display_view_interface.h"

#include "qpointer.h"
#include "qwidget.h"

class QGridLayout;
class QHBoxLayout;
class QSpacerItem;
class QVBoxLayout;

namespace Controller
{
class Joystick;
}

namespace View
{
class AirspeedIndicator;
class AltitudeIndicator;
class AttitudeIndicator;
class HeadingIndicator;

class PrimaryFlightDisplay : public QWidget, public IPrimaryFlightDisplayView
{
public:
    explicit PrimaryFlightDisplay(QWidget* parent = nullptr);

    ~PrimaryFlightDisplay() override;

    void setSpeed(float speed) override;
    void setVerticalSpeed(float) override;
    void setAltitude(float) override;
    void setHeading(float) override;

private:
    QSpacerItem* m_topSpacer;
    QPointer<QGridLayout> m_mainLayout;
    QPointer<QGridLayout> m_flightInstrumentsLayout;
    QPointer<QHBoxLayout> m_controllersLayout;
    QPointer<QVBoxLayout> m_verticalLayout;
    QPointer<AirspeedIndicator> m_speedIndicator;
    QPointer<AltitudeIndicator> m_altitudeIndicator;
    QPointer<AttitudeIndicator> m_attitudeIndicator;
    QPointer<HeadingIndicator> m_headingIndicator;
    QPointer<Controller::Joystick> m_leftJoystick;
    QPointer<Controller::Joystick> m_rightJoystick;

    Q_DISABLE_COPY(PrimaryFlightDisplay);
};

} // namespace View

#endif
