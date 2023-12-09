cmake_minimum_required(VERSION 3.10)
project(mqtt VERSION 1.0)
configure_file(Config.h.in Config.h)

add_executable(mqtt main.cpp)
add_subdirectory(libs/cxxopts)
include_directories(libs/plog/include)
target_include_directories(mqtt PUBLIC 
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_BINARY_DIR}/libs/cxxopts")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
