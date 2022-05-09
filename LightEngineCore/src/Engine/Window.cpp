#include "Engine/Window.h"
#include "Engine/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace light_engine {

static bool s_glfw_initialized = false;

Window::Window(int width, int height, std::string name)
    : m_data{width, height, std::move(name), nullptr}
{
    int result = init();
}

Window::~Window()
{
    destroy();
}

void Window::set_event_callback(const EventCallback & event_callback)
{
    m_data.event_callback = event_callback;
}

void Window::on_update()
{
    glClearColor(1, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

int Window::init()
{
    LOG_INFO("Initializing window '{0} {1}x{2}'", m_data.name, m_data.width, m_data.height);

    if (!s_glfw_initialized) {
        if (!glfwInit()) {
            LOG_CRITICAL("GLFW failed to initialize!");
            return -1;
        }
        s_glfw_initialized = true;
    }

    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.name.c_str(), nullptr, nullptr);
    if (!m_window) {
        LOG_CRITICAL("Failed to create window '{0} {1}x{2}'", m_data.name, m_data.width, m_data.height);
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_CRITICAL("Failed to initialize GLAD");
        return -3;
    }

    glfwSetWindowUserPointer(m_window, &m_data);

    glfwSetWindowSizeCallback(m_window,
                              [](GLFWwindow * window, int width, int height) {
                                  WindowData & data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
                                  data.width = width;
                                  data.height = height;

                                  EventWindowResize event{width, height};
                                  data.event_callback(event);
                              });

    glfwSetCursorPosCallback(m_window,
                             [](GLFWwindow * window, double x, double y) {
                                 WindowData & data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

                                 EventMouseMoved event{x, y};
                                 data.event_callback(event);
                             });

    glfwSetWindowCloseCallback(m_window,
                               [](GLFWwindow * window) {
                                   WindowData & data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

                                   EventWindowClose event;
                                   data.event_callback(event);
                               });

    return 0;
}

void Window::destroy()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

} // namespace light_engine
