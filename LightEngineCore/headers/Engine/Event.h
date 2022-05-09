#pragma once

#include <functional>
#include <array>

namespace light_engine {

enum class EventType
{
    WindowResize = 0,
    WindowClose,

    KeyPressed,
    KeyReleased,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,

    EventsCount
};

struct IEvent
{
    virtual ~IEvent() = default;
    virtual EventType get_type() const = 0;
};

class EventDispatcher
{
public:
    template <typename EventT>
    void add_event_listener(std::function<void(EventT &)> event_callback)
    {
        auto casted_callback = [func = std::move(event_callback)](IEvent & event) {
            func(static_cast<EventT &>(event));
        };

        m_event_callbacks[static_cast<size_t>(EventT::type)] = std::move(casted_callback);
    }

    void dispatch(IEvent & event)
    {
        const auto & event_callback = m_event_callbacks[static_cast<size_t>(event.get_type())];
        if (event_callback)
            event_callback(event);
    }

private:
    std::array<std::function<void(IEvent &)>, static_cast<int>(EventType::EventsCount)> m_event_callbacks;
};

struct EventMouseMoved : IEvent
{
    EventMouseMoved(const double new_x, const double new_y)
        : x(new_x)
        , y(new_y)
    {
    }

    EventType get_type() const override
    {
        return type;
    }

    double x;
    double y;

    static constexpr EventType type = EventType::MouseMoved;
};

struct EventWindowResize : IEvent
{
    EventWindowResize(const int new_width, const int new_height)
        : width(new_width)
        , height(new_height)
    {
    }

    EventType get_type() const override
    {
        return type;
    }

    int width;
    int height;

    static constexpr EventType type = EventType::WindowResize;
};

struct EventWindowClose : IEvent
{
    EventType get_type() const override
    {
        return type;
    }

    static constexpr EventType type = EventType::WindowClose;
};

} // namespace light_engine
