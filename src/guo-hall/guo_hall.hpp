#ifndef GUO_HALL_HPP
#define GUO_HALL_HPP

#include <iostream>
#include <tuple>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <array>
#include <algorithm>
#include <utility>

using namespace std;
using namespace cv;

class GuoHall
{
private:
    enum Color { FG = 0, BG = 255 };
    static Color set_type(uchar uc);
    static void thinning_iteration(Mat& img, int tmp);
    static void thinning(cv::Mat& img);  

public:
    static Mat solve_guo_hall(const string& file);
    static void save(const string& file, Mat& skeleton);
};

#endif // GUO_HALL_HPP