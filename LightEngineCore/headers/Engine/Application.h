#pragma once

#include "Engine/Event.h"

#include <memory>

namespace light_engine {

class Window;

class Application
{
public:
    Application();
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    virtual ~Application();

    Application & operator=(const Application &) = delete;
    Application & operator=(Application &&) = delete;

    virtual int start(int window_width, int window_height, const char * window_name);
    virtual void on_update() {}

private:
    std::unique_ptr<Window> m_window;
    EventDispatcher m_event_dispatcher;
    bool m_window_closed = false;
};

} // namespace light_engine
