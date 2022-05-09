#include "Engine/Application.h"
#include "Engine/Log.h"
#include "Engine/Window.h"


namespace light_engine {

Application::Application()
{
    LOG_INFO("Starting Application");
}

Application::~Application()
{
    LOG_INFO("Closing Application");
}

int Application::start(int window_width, int window_height, const char * window_name)
{
    m_window = std::make_unique<Window>(window_width, window_height, window_name);

    m_event_dispatcher.add_event_listener<EventMouseMoved>([](EventMouseMoved & event) {
        LOG_INFO("(MouseMoved) New mouse position 'x:{0} y:{1}'", event.x, event.y);
    });

    m_event_dispatcher.add_event_listener<EventWindowResize>([](EventWindowResize & event) {
        LOG_INFO("(WindowResize) New window size '{0}x{1}'", event.width, event.height);
    });

    m_event_dispatcher.add_event_listener<EventWindowClose>([this](EventWindowClose & event) {
        LOG_INFO("(WindowClose) Window closed");
        m_window_closed = true;
    });

    m_window->set_event_callback([this](IEvent & event) {
        m_event_dispatcher.dispatch(event);
    });

    while (!m_window_closed) 
    {
        m_window->on_update();
        on_update();
    }
    m_window = nullptr;

    return 0;
}

} // namespace light_engine
