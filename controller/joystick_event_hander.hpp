/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#ifndef JOYSTICK_EVENT_HANDLER_HPP
#define JOYSTICK_EVENT_HANDLER_HPP

#include <functional>

class IHandler
{
public:
    template <class ValueType> void handle(ValueType value);
};

template <class ReturnType, class... ArgTypes> class ValueChangedHandler<ReturnType(ArgTypes...)>;

template <class ReturnType, class... ArgTypes>
class ValueChangedHandler<ReturnType(ArgTypes...)> : public IHandler
{
public:
    ReturnType handle(ArgTypes...&& args) { m_handler(std::forward<ArgTypes>(args)...); }

private:
    std::function<ReturnType(ArgTypes...)> m_handler;
};

class JoystickEventProxyHandler
{
public:
    JoystickEventProxyHandler() = default;

    template <class ReturnType, class... ArgTypes>
    using Handler = std::function < ReturnType(ArgTypes...);

    explicit JoystickEventProxyHandler(IValueChangeHandler& xHandler, IValueChangeHandler& yHandler)
        : m_xHandler(&xHandler)
        , m_yHandler(&yHandler)
    {
    }

    void handle(const Value& value)
    {
        m_xHandler->handle(value.x());
        m_yHandler->handle(value.y());
    }

    enum class Axis
    {
        X,
        Y
    };

    template <Axis> void setValueChangeHandler(IValueChangeHandler& handler);

private:
    IValueChangeHandler* m_xHandler;
    IValueChangeHandler* m_yHandler;
};

#endif
