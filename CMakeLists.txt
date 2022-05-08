cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME LightEngine)

project(${PROJECT_NAME})

add_subdirectory(LightEngineCore)
add_subdirectory(LightEngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LightEngineEditor)