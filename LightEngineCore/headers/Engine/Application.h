#pragma once

namespace light_engine {

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
};

} // namespace light_engine
