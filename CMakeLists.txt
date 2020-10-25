cmake_minimum_required(VERSION 3.17.3)
project(test)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test
        main.cpp
        zs_algorithm.hpp
        zs_algorithm.cpp
        matrix_builder.hpp
        matrix_builder.cpp
        )

target_link_libraries(test ${OpenCV_LIBS})
