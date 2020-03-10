
//!
//! @file	imu_model.h
//!
//! @brief	imu_model.h file description
//!
//! @date
//!
//! @author	Clement Ailloud
//!
//!



#ifndef __IMU_MODEL_H
#define __IMU_MODEL_H


#include "accelerometer.h"
#include "gyroscope.h"
#include "magnetometer.h"


class ImuModel
{
    public:

        ImuModel();

        ImuModel(const ImuModel& model) = delete;

        ~ImuModel() = default;

        short x() const noexcept;
        short y() const noexcept;
        short z() const noexcept;


    private:

        Axis m_axis;

        IAccelerometer* m_accelerometer;

        IGyroscope* m_gyroscope;

        IMagnetometer* m_magnetometer;
};



#endif
