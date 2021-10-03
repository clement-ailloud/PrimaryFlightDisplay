#ifndef PRIMARY_FLIGHT_DISPLAY_H
#define PRIMARY_FLIGHT_DISPLAY_H

#include "primary_flight_display_view_interface.h"

#include "qpointer.h"
#include "qwidget.h"

class QGridLayout;

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
    QPointer<QGridLayout> m_gridLayout;
    QPointer<AirspeedIndicator> m_speedIndicator;
    QPointer<AltitudeIndicator> m_altitudeIndicator;
    QPointer<AttitudeIndicator> m_attitudeIndicator;
    QPointer<HeadingIndicator> m_headingIndicator;

    Q_DISABLE_COPY(PrimaryFlightDisplay);
};

} // namespace View

#endif
