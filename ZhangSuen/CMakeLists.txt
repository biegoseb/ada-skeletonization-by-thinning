add_library(
    ZhangSuen
    zs_algorithm.hpp
    zs_algorithm.cpp
)

target_link_libraries(ZhangSuen ${OpenCV_LIBS})