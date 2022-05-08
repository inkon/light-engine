cmake_minimum_required(VERSION 3.13)

set(ENGINE_PROJECT_NAME LightEngineCore)

add_library(${ENGINE_PROJECT_NAME} STATIC
	src/Engine/Utils/test.cpp
	headers/Engine/Utils/test.h
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC headers)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)