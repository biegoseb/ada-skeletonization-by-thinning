add_library(
    GuoHall
    guo_hall.hpp
    guo_hall.cpp
)

target_link_libraries(GuoHall ${OpenCV_LIBS})