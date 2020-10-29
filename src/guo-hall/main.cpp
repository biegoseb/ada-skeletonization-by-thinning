#include "guo_hall.hpp"

int main()
{
    string file = "duck.png";
    auto skeleton = GuoHall::solve_guo_hall(file);
    GuoHall::save(file, skeleton);
    return 0;
}