
//!
//! \file	airspeed_indicator_model.cpp
//!
//! \brief	airspeed_indicator_model file description
//!
//! \date
//!
//! \author	Clement Ailloud
//!
//!



#include "airspeed_indicator_model.h"


using namespace Model;


AirspeedIndicator::AirspeedIndicator()
{
}


AirspeedIndicator::~AirspeedIndicator()
{
}


float AirspeedIndicator::speed() const
{
    return m_speed;
}


void AirspeedIndicator::setSpeed(const float speed)
{
    m_speed = speed;
}
