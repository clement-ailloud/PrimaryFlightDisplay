//!
//! \file	    airspeed_indicator.cpp
//!
//! \brief	    file description
//!
//! \date
//!
//! \author	    Clement Ailloud
//!


#include "airspeed_indicator.h"

#include <memory>

#include "movable_linear_gauge.h"


AirspeedIndicator::AirspeedIndicator()
{
    m_airspeedIndicatorView = std::make_unique<View::AirspeedIndicator>();
    m_airspeedIndicatorView->graphicsItem()->setBoundingRect(QRectF(-50.f, -150.f, 100.f, 300.f));
}


AirspeedIndicator::~AirspeedIndicator()
{
    // Do nothing
}
