cmake_minimum_required(VERSION 3.13)

set(ENGINE_PROJECT_NAME LightEngineCore)

set(ENGINE_PUBLIC_HEADERS
	headers/Engine/Application.h
	headers/Engine/Log.h
	headers/Engine/Event.h
)

set(ENGINE_PRIVATE_HEADERS
	src/Engine/Window.h
)

set(ENGINE_PRIVATE_SOURCES
	src/Engine/Application.cpp
	src/Engine/Window.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_PUBLIC_HEADERS}
	${ENGINE_PRIVATE_HEADERS}
	${ENGINE_PRIVATE_SOURCES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC headers)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)