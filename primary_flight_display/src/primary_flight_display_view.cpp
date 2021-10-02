
#include "primary_flight_display_view.h"

#include "qgridlayout.h"
#include "QHBoxLayout"
#include "QDebug"

#include "airspeed_indicator_view.h"
#include "attitude_indicator_view.h"
#include "altitude_indicator_view.h"
#include "heading_indicator_view.h"

using namespace View;

PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget* parent)
    : QWidget(parent)
    , m_gridLayout(new QGridLayout())
    , m_speedIndicator(new AirspeedIndicator(this))
    , m_altitudeIndicator(new AltitudeIndicator(this))
    , m_attitudeIndicator(new AttitudeIndicator(this))
    , m_headingIndicator(new HeadingIndicator(this))
{
//    m_gridLayout->setHorizontalSpacing(200);
//    m_gridLayout->setVerticalSpacing(50);

    m_gridLayout->addWidget(m_headingIndicator, 0, 1, 1, 5); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    m_gridLayout->addWidget(m_speedIndicator, 1, 0, 7, 1); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    m_gridLayout->addWidget(m_attitudeIndicator, 2, 2, 5, 3); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    m_gridLayout->addWidget(m_altitudeIndicator, 1, 6, 7, 1); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    setLayout(m_gridLayout);
}

PrimaryFlightDisplay::~PrimaryFlightDisplay() = default;

void PrimaryFlightDisplay::setSpeed(const float speed)
{
    m_speedIndicator->setSpeed(speed);
}

void PrimaryFlightDisplay::setVerticalSpeed(const float)
{
}

void PrimaryFlightDisplay::setAltitude(const float)
{
}

void PrimaryFlightDisplay::setHeading(const float)
{
}
