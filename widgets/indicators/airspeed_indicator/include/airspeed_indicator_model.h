
//!
//! @file	airspeed_indicator_model.h
//!
//! @brief	airspeed_indicator_model.h file description
//!
//! @date
//!
//! @author	Clement Ailloud
//!
//!

#ifndef __AIRSPEED_INDICATOR_MODEL_H
#define __AIRSPEED_INDICATOR_MODEL_H

#include "indicator_model.h"

#include "axis.h"
#include "circular_buffer.h"

#include "boost/circular_buffer.hpp"
#include "boost/signals2/signal.hpp"

#include <string>
#include <vector>

//#include "accelerometer_interface.h"

class IAccelerometer;

namespace Model
{

class AirspeedIndicator : public IndicatorModel
{
public:
    AirspeedIndicator();

    // Copy constructor and assignment
    AirspeedIndicator(const AirspeedIndicator&) = delete;
    AirspeedIndicator& operator=(const AirspeedIndicator&) = delete;

    // Move constructor and assignment
    AirspeedIndicator(AirspeedIndicator&&) = delete;
    AirspeedIndicator& operator=(AirspeedIndicator&&) = delete;

    ~AirspeedIndicator() override;

    /**
     * @brief      Get the current speed
     *
     * @return     float
     */
    float speed() const;

    /**
     * @brief      Set the speed
     *
     * @param      float value
     */
    void setSpeed(float value);

    /**
     *
     */
    const std::vector<int>& range() const;

    /**
     * @brief      Set the range that will be displayed on the indicator
     */
    void setRange(const std::vector<int>& range);

    // Signals
    template <typename T> using Signal = boost::signals2::signal<T>;

    Signal<void()> unitChanged;
    Signal<void()> speedChanged;

private:
    Axis<int> m_axis;

    boost::circular_buffer<int> m_buffer;

    float m_speed;

    std::string m_unit; // User configuration, require additional conversion computation

    IAccelerometer* m_accelerometer;
};

} // namespace Model

#endif
