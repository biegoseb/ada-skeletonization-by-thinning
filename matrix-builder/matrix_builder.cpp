#include "matrix_builder.hpp"

#include <utility>

MatrixBuilder::MatrixBuilder(String filename, MatrixBuilder::matrix_t matrix,
                             int rows, int cols) : filename(move(filename))
{
    mat = Mat(rows, cols, CV_8UC1, matrix);
}

MatrixBuilder::~MatrixBuilder() {}

void MatrixBuilder::print() const
{
    cout << filename << endl;
    cout << mat << endl;
}

void MatrixBuilder::save()
{
    imwrite("../images/" + filename, mat, {IMWRITE_PNG_COMPRESSION});
}

void MatrixBuilder::show()
{
    imshow(filename, mat);
    waitKey(0);
}