
#include "primary_flight_display_view.h"

#include "QGraphicsGridLayout"
#include "airspeed_indicator_view.h"
#include "attitude_indicator_view.h"


using namespace View;


PrimaryFlightDisplay::PrimaryFlightDisplay(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags)
    , m_graphicsGridLayout(std::make_unique<QGraphicsGridLayout>())
    , m_speedIndicator(std::make_unique<View::AirspeedIndicator>(this, m_graphicsGridLayout.get()))
    , m_attitudeIndicator(std::make_unique<View::AttitudeIndicator>(this, m_graphicsGridLayout.get()))
{
    m_speedIndicator->setSpeed(17.0f);

    m_graphicsGridLayout->addItem(m_speedIndicator.get(), 0, 0);
    m_graphicsGridLayout->addItem(m_attitudeIndicator.get(), 0, 1);
    setLayout(m_graphicsGridLayout.release());
}


PrimaryFlightDisplay::~PrimaryFlightDisplay() = default;


void PrimaryFlightDisplay::setSpeed(const float)
{

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
