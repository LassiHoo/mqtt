cmake_minimum_required(VERSION 3.10)
project(homeAutomation VERSION 1.0)
configure_file(homeAutomationConfig.h.in homeAutomationConfig.h)

add_executable(homeAutomation main.cpp)
add_subdirectory(libs/cxxopts)
include_directories(libs/plog/include)
target_include_directories(homeAutomation PUBLIC 
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_BINARY_DIR}/libs/cxxopts")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
