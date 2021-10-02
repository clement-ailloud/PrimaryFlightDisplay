
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

#include <iostream>

using namespace Model;

AirspeedIndicator::AirspeedIndicator()
    : m_buffer(11)
{
    std::generate(m_buffer.begin(), m_buffer.end(), [n = 120]() mutable
                  {
                      n -= 20;
                      return n;
                  });

//    for (const auto& e : m_buffer)
//        std::cout << e << std::endl;
//    boost::signals2::signal<void()> overflow;
//
//    const auto& f = [this]()
//                    {
//                        const auto interval = m_axis.interval();
//                        const auto& range = m_axis.range();
//
//                        if (!m_speed) return;

//                        if (m_speed % interval == 0)
//                        {
//                          m_buffer.push_front(range.back() + interval);
//                        }
//                        else
//                        {
//                          m_buffer.push_back(range.back() - interval);
//                        }
//                    };

    // TODO: Each time speed has changed, check if it requires an update of the range
    // Push value accordingly
}

AirspeedIndicator::~AirspeedIndicator() = default;

float AirspeedIndicator::speed() const
{
    return m_speed;
}

void AirspeedIndicator::setSpeed(const float speed)
{
    m_speed = speed;
}

const std::vector<int>& AirspeedIndicator::range() const
{
    return m_axis.range();
}

void AirspeedIndicator::setRange(const std::vector<int>& range)
{
    m_axis.setRange(range);
}
