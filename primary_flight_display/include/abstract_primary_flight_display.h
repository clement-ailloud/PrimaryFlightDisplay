#ifndef __ABSTRACT_PRIMARY_FLIGHT_DISPLAY_H
#define __ABSTRACT_PRIMARY_FLIGHT_DISPLAY_H

#include <memory>


namespace Presenter {

class View::PrimaryFlightDisplay;
class Model::PrimaryFlightDisplay

class AbstractPrimaryFlightDisplay
{
    public:

        AbstractPrimaryFlightDisplay() = default;

        AbstractPrimaryFlightDisplay(const AbstractPrimaryFlightDisplay& display);

        ~AbstractPrimaryFlightDisplay() = default;


    protected:

        std::share_ptr<View::PrimaryFlightDisplay> m_view;
        std::share_ptr<Model::PrimaryFlightDisplay> m_model;
};

} // namespace Presenter

#endif
