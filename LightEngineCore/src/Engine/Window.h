#pragma once

#include "Engine/Event.h"

#include <string>
#include <functional>

struct GLFWwindow;

namespace light_engine {

class Window
{
public:
    using EventCallback = std::function<void(IEvent &)>;

    Window(int width, int height, std::string name);
    Window(const Window &) = delete;
    Window(Window &&) = delete;
    ~Window();

    Window & operator=(const Window &) = delete;
    Window & operator=(Window &&) = delete;

    void set_event_callback(const EventCallback & event_callback);

    void on_update();
    int get_width() const { return m_data.width; }
    int get_height() const { return m_data.height; }

private:
    struct WindowData
    {
        int width;
        int height;
        std::string name;
        EventCallback event_callback;
    };

    int init();
    void destroy();

    GLFWwindow * m_window = nullptr;
    WindowData m_data;
};

} // namespace light_engine
