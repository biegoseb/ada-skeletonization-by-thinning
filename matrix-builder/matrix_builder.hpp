#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

class MatrixBuilder
{
private:
    typedef uchar *matrix_t;

public:
    MatrixBuilder(String filename, matrix_t matrix, int rows, int cols);
    ~MatrixBuilder();
    void print() const;
    void save();
    void show();

public:
    Mat mat;
    string filename;
    string outputFilename;
};