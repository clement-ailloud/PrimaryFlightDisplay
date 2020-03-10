#ifndef __INDICATOR_H
#define __INDICATOR_H


#include <memory>


class Indicator
{
    public:

        Indicator();

        Indicator(const Indicator& indicator) = default;

        ~Indicator();


    protected:

//        std::unique_ptr<IndicatorView> m_abstractIndicatorView;
//
//        std::unique_ptr<IndicatorModel> m_abstractIndicatorModel;
};


#endif
