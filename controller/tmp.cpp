/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

// System's boot
// Remote controller pairing
// Flight

#include <functional>
#include <iostream>
#include <map>

class Button
{
public:
};

class JoystickEvent
{
public:
    using value_type = int;

    value_type x() const { return m_x; }
    value_type y() const { return m_y; }

    // private:
    value_type m_x{}, m_y{};
};

class LeftJoystick : public JoystickEvent
{
public:
};

class RightJoystick : public JoystickEvent
{
public:
};

// Controller builder
class Controller
{
public:
    enum InputEvent
    {
        FlightButtonPressed,
        PowerButtonPressed,
        LeftJoystickValueChanged,
        RightJoystickValueChanged
    };

    const JoystickEvent& leftJoystick() const { return m_leftJoystick; }

private:
    Button m_powerButton;

    JoystickEvent m_leftJoystick;
    JoystickEvent m_rightJoystick;
};

class AbstractState
{
public:
};

class InputEventHandler
{
public:
    void handle(Controller::InputEvent event);

private:
    AbstractState* m_state;
};

class Engine
{
public:
};

class EngineControl
{
public:
    void setValue(Engine& engine, short value);
};

/**
 * System's boot finished, ready to flight
 */
class Standby : public AbstractState
{
public:
    AbstractState* handle(Controller& controller, Controller::InputEvent event);
};

template <class HandlerType> class JoystickControlHandler
{
public:
    JoystickControlHandler() = default;

    explicit JoystickControlHandler(HandlerType&& xHandler, HandlerType&& yHandler)
        : m_xHandler(xHandler)
        , m_yHandler(yHandler)
    {
    }

    void handle(const JoystickEvent& event)
    {
        m_xHandler(event.x());
        m_yHandler(event.y());
    }

    enum class Axis
    {
        X,
        Y
    };

    // template <Axis>
    // void setValueChangeHandler(IValueChangeHandler& handler);

private:
    HandlerType m_xHandler;
    HandlerType m_yHandler;
};

// template <>
// void
// JoystickControlHandler::setValueChangeHandler<JoystickControlHandler::Axis::X>(IValueChangeHandler&
// handler)
//{
//     m_xHandler = &handler;
// }

// template <>
// void
// JoystickControlHandler::setValueChangeHandler<JoystickControlHandler::Axis::Y>(IValueChangeHandler&
// handler)
//{
//     m_yHandler = &handler;
// }

class YawChangeHandler
{
public:
    void operator()(int value) { std::cout << "Process yaw value: " << value << '\n'; }
};

class EngineControl
{
public:
    void adjustSpeed
};

class ThrottleControl
{
public:
    EngineControl
};

class ThrottleChangeHandler
{
public:
    void operator()(int value) { std::cout << "Process throttle value: " << value << '\n'; }
};

class YawControl
{
public:
    YawControl(EngineControl& control);

    void setYaw(float);
};

/**
 * Manages engines throttle
 *
 * A positive or negative offset is applied to each engine to increase or decrease throttle.
 */
class ThrottleControl
{
public:
    void setThrottle(EngineControl& control, float throttle);
};

class InFlight : public AbstractState
{
public:
    AbstractState* handle(Controller& controller, Controller::InputEvent event);

private:
};

AbstractState* InFlight::handle(Controller& controller, Controller::InputEvent event)
{
    switch (event)
    {
    };

    return this;
}

AbstractState* Standby::handle(Controller& controller, Controller::InputEvent event)
{
    switch (event)
    {
    case Controller::InputEvent::FlightButtonPressed:
        return new InFlight();
    };

    return this;
}

int main()
{
    YawChangeHandler yawHandler;
    ThrottleChangeHandler throttleHandler;
    // JoystickControlHandler<YawChangeHandler, ThrottleChangeHandler> joystickHandler;

    // Setting-up yaw control
    // YawChangeHandler yawHandler;
    // joystickHandler.setValueChangeHandler<JoystickControlHandler::Axis::X>(yawHandler);

    // Setting-up throttle control
    // ThrottleChangeHandler throttleHandler;
    // joystickHandler.setValueChangeHandler<JoystickControlHandler::Axis::Y>(throttleHandler);

    JoystickEvent controller;
    controller.m_x = 135;
    controller.m_y = 70;

    yawHandler(controller.m_x);
    throttleHandler(controller.m_y);

    // joystickHandler.handle(controller);

    return 0;
}
