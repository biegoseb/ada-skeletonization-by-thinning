cmake_minimum_required(VERSION 3.1...3.18.4)

project(test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_subdirectory(ZhangSuen)
add_subdirectory(GuoHall)

add_executable(test main.cpp)
target_link_libraries(test ZhangSuen GuoHall)