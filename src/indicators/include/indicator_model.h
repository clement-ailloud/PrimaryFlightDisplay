
//!
//! @file	abstract_indicator_model.h
//!
//! @brief	abstract_indicator_model.h file description
//!
//! @date
//!
//! @author	Clement Ailloud
//!
//!



#ifndef __ABSTRACT_INDICATOR_MODEL_H
#define __ABSTRACT_INDICATOR_MODEL_H



class IndicatorModel {

    public:

        IndicatorModel() = default;

        IndicatorModel(const IndicatorModel& model) = default;

        ~IndicatorModel() = default;

//        virtual void valueChanged(void *) = 0;
};



#endif
