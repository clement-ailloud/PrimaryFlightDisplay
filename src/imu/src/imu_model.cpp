
//!
//! @file	inertial_measurement_unit_model.c
//!
//! @brief	inertial_measurement_unit_model file description
//!
//! @date
//!
//! @author	Clement Ailloud
//!
//!



#include "inertial_measurement_unit_model.h"


ImuModel::ImuModel()
{
    m_axis.x = static_cast<short>(0);
    m_axis.y = static_cast<short>(0);
    m_axis.z = static_cast<short>(0);
}


short ImuModel::x() const {
    return m_axis.x;
}

short ImuModel::y() const {
    return m_axis.x;
}

short ImuModel::z() const {
    return m_axis.x;
