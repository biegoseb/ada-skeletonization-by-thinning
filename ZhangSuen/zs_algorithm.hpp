#pragma once

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

/**
 * iterative parallel thinning algorithm 
 */

class ZSAlgorithm
{
private:
    enum Color {
        BLACK = 0,
        WHITE = 255
    };
    typedef tuple<Color, Color, Color, Color, Color, Color, Color, Color> neighbours;
    typedef pair<int, int> pixel;

    Mat img;
    pixel dummyPixel = pixel(-1, -1);

public:
    explicit ZSAlgorithm(Mat img);
    ~ZSAlgorithm();
    Mat solve();

private:
    neighbours get_neighbours(int row, int col);
    static Color set_color(uchar color);
    void verify_conditions(vector<pixel> & aux, int tmp);
    array<Color, 9> get_array(int row, int col);
    int get_transitions(int row, int col);
    int count_black(int row, int col);
    static bool in_range(int num, int low, int high);
    static bool isBlack(Color color);
};