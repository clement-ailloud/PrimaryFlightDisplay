
#include "primary_flight_display_view.h"

#include "airspeed_indicator_view.h"
#include "altitude_indicator_view.h"
#include "attitude_indicator_view.h"
#include "heading_indicator_view.h"
#include "virtual_joystick_controller.h"

#include "QHBoxLayout"
#include "QSpacerItem"
#include "QVBoxLayout"
#include "qgridlayout.h"

#include "QDebug"

using namespace View;

PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget* parent)
    : QWidget(parent)
    , m_mainLayout(new QGridLayout())
    , m_flightInstrumentsLayout(new QGridLayout())
    , m_controllersLayout(new QHBoxLayout())
    , m_verticalLayout(new QVBoxLayout())
    , m_speedIndicator(new AirspeedIndicator(this))
    , m_altitudeIndicator(new AltitudeIndicator(this))
    , m_attitudeIndicator(new AttitudeIndicator(this))
    , m_headingIndicator(new HeadingIndicator(this))
    , m_leftJoystick(new Controller::Joystick(this))
    , m_rightJoystick(new Controller::Joystick(this))
{
    {
        auto left = 0, top = 0, right = 0, bottom = 0;
        m_controllersLayout->getContentsMargins(&left, &top, &right, &bottom);

        QMargins margins(left, top, right, bottom);
        m_flightInstrumentsLayout->setContentsMargins(width() * .9, top, width() * .9, bottom);
    }

    m_flightInstrumentsLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_flightInstrumentsLayout->addWidget(m_headingIndicator, 0, 1, 2,
                                         5); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    m_flightInstrumentsLayout->addWidget(m_speedIndicator, 2, 0, 10,
                                         1); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    m_flightInstrumentsLayout->addWidget(m_attitudeIndicator, 2, 2, 10,
                                         3); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    m_flightInstrumentsLayout->addWidget(m_altitudeIndicator, 2, 6, 10,
                                         1); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

    m_controllersLayout->addWidget(m_leftJoystick);
    m_controllersLayout->addWidget(m_rightJoystick);

    m_verticalLayout->addItem(new QSpacerItem(0, 200));
    m_verticalLayout->addLayout(m_flightInstrumentsLayout);
    m_verticalLayout->addLayout(m_controllersLayout);

    setLayout(m_verticalLayout);

    qDebug() << m_leftJoystick->geometry();
}

PrimaryFlightDisplay::~PrimaryFlightDisplay() = default;

void PrimaryFlightDisplay::setSpeed(const float speed)
{
    m_speedIndicator->setSpeed(speed);
}

void PrimaryFlightDisplay::setVerticalSpeed(const float) {}

void PrimaryFlightDisplay::setAltitude(const float) {}

void PrimaryFlightDisplay::setHeading(const float) {}
