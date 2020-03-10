
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


#include <string>

#include "types.h"

//#include "QObject" // Required for Qt signals

#include "indicator_model.h"

//#include "accelerometer_interface.h"

class IAccelerometer;

namespace Model {

class AirspeedIndicator : public IndicatorModel
{
    public:


	AirspeedIndicator();

        //!
        //! \fn         Model::AirspeedIndicator(Model::AirspeedIndicator& model)
        //!
        //! \brief      Copy deleted constructor
        //!
        //! \param      const Model::AirspeedIndicator &
        //!

        AirspeedIndicator(const Model::AirspeedIndicator&) = delete;


        //!
        //! \fn         Model::AirspeedIndicator(AirspeedIndicator&&)
        //!
        //! \brief      Copy deleted constructor
        //!
        //! \param      const Model::AirspeedIndicator &
        //!

        AirspeedIndicator(AirspeedIndicator&&) = delete;


        //!
        //! \fn         Model::~AirspeedIndicator()
        //!
        //! \brief      Default virtual destructor
        //!

        ~AirspeedIndicator();


        //!
        //! \fn         speed() const
        //!
        //! \brief
        //!
        //! \return     float
        //!

        float speed() const;


        //!
        //! \fn         setSpeed(float value)
        //!
        //! \brief
        //!
        //! \param      float value
        //!

        void setSpeed(float value);

	// Assignments operators
	AirspeedIndicator& operator=(const AirspeedIndicator&) = delete;
	AirspeedIndicator& operator=(AirspeedIndicator&&) = delete;


    private:

        float m_speed;

        int m_x, m_y;

        uint m_width, m_height;

        std::string m_unit; // User configuration, require additional conversion computation

        IAccelerometer* m_accelerometer;
};

}

#endif
