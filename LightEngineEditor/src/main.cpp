#include "Engine/Application.h"

#include <iostream>

class EditorApplication final : public light_engine::Application
{
public:
    void on_update() override
    {
        //std::cout << "Update tick: " << m_tick++ << '\n';
    }

private:
    unsigned int m_tick = 0;
};

int main()
{
    EditorApplication editor_application;
    const int return_code = editor_application.start(1024, 576, "Light Engine Editor");

    std::cin.get();
    return return_code;
}
