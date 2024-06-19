cmake_minimum_required(VERSION 3.10)
project(mqtt VERSION 1.0 LANGUAGES CXX)
configure_file(Config.h.in Config.h)

find_library(PAHO_CPP_LIB paho-mqttpp3)
find_library(PAHO_C_LIB paho-mqtt3as)

add_executable(mqtt main.cpp mqtt/mqttInterface.cpp)
add_subdirectory(libs/cxxopts)
include_directories(libs/plog/include)
include_directories(mqtt)
target_include_directories(mqtt PUBLIC 
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_BINARY_DIR}/libs/cxxopts")
target_link_libraries(mqtt ${PAHO_CPP_LIB} ${PAHO_C_LIB})                      
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
