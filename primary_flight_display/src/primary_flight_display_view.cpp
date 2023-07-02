
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
    , m_topSpacer(new QSpacerItem(0, 200))
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
    m_headingIndicator->setMinimumSize({ 400, 60 });
    m_speedIndicator->setMinimumSize({ 100, 300 });
    m_attitudeIndicator->setMinimumSize({ 400, 400 });
    m_altitudeIndicator->setMinimumSize({ 100, 300 });

    // m_flightInstrumentsLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_flightInstrumentsLayout->addWidget(m_headingIndicator, 0, 1,
                                         Qt::AlignBottom | Qt::AlignCenter);
    m_flightInstrumentsLayout->addWidget(m_speedIndicator, 2, 0, Qt::AlignRight);
    m_flightInstrumentsLayout->addWidget(m_attitudeIndicator, 2, 1, Qt::AlignCenter);
    m_flightInstrumentsLayout->addWidget(m_altitudeIndicator, 2, 2, Qt::AlignLeft);

    m_controllersLayout->addWidget(m_leftJoystick, Qt::AlignVCenter | Qt::AlignLeft);
    m_controllersLayout->addWidget(m_rightJoystick, Qt::AlignVCenter | Qt::AlignRight);

    m_verticalLayout->addItem(m_topSpacer);
    m_verticalLayout->addLayout(m_flightInstrumentsLayout);
    m_verticalLayout->addLayout(m_controllersLayout, Qt::AlignBottom);

    setLayout(m_verticalLayout);
}

PrimaryFlightDisplay::~PrimaryFlightDisplay() = default;

void PrimaryFlightDisplay::setSpeed(const float speed)
{
    m_speedIndicator->setSpeed(speed);
}

void PrimaryFlightDisplay::setVerticalSpeed(const float) {}

void PrimaryFlightDisplay::setAltitude(const float) {}

void PrimaryFlightDisplay::setHeading(const float) {}
