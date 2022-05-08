#include <iostream>

#include "Engine/Utils/test.h"

int main()
{
	std::cout << "Hello from Light Engine Editor" << std::endl;

	light_engine::check_glfw();

	std::cin.get();
}
