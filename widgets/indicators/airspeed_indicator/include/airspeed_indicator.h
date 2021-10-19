//!
//! \file	    airspeed_indicator.h
//!
//! \brief
//!
//! \date
//!
//! \author	    Clement Ailloud
//!

#ifndef __AIRSPEED_INDICATOR_H
#define __AIRSPEED_INDICATOR_H

#include "indicator.h"

#include "airspeed_indicator_view.h"

class AirspeedIndicator : public Indicator
{
public:
    AirspeedIndicator();

    AirspeedIndicator(const AirspeedIndicator& indicator) = default;
    AirspeedIndicator(AirspeedIndicator&& other) = default;

    ~AirspeedIndicator();

    AirspeedIndicator& operator=(const AirspeedIndicator& other) = default;
    AirspeedIndicator& operator=(AirspeedIndicator&& other) = default;

private:
    std::unique_ptr<View::AirspeedIndicator> m_airspeedIndicatorView;
};

#endif
