#include "zs_algorithm.hpp"
#include "matrix_builder.hpp"

using namespace cv;
using namespace std;

uchar m[] = {
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};

Mat read_image(string filename);

void
convert_to_grayscale(Mat src, Mat &dest);

Mat
convert_to_black_and_white(Mat src);

/*
void
print_image(Mat mat);

Mat
reverse_color(Mat mat);
*/

int main(int argc, char *argv[])
{
    // auto matrixBuilder = MatrixBuilder("matrix1.png", m, 27, 27);
    // matrixBuilder.save();
    // matrixBuilder.print();

    if (argc != 2)
    {
        cerr << "No argument given." << endl;
        return 1;
    }

    Mat img;

    string filename = argv[1];

    if (img = read_image(filename); img.empty())
    {
        cerr << "Couldn't read image." << endl;
        return 1;
    }

    img = convert_to_black_and_white(img);

    auto zsalgo = ZSAlgorithm(img);
    auto skeleton = zsalgo.solve();
    // cout << skeleton << endl;
    if (int k = waitKey(0); k == 's')
        imwrite("../output/skeleton-" + filename, skeleton,
                {IMWRITE_PNG_COMPRESSION});
    return 0;
}

Mat read_image(string filename)
{
    return imread("../images/" + filename);
}

void convert_to_grayscale(Mat src, Mat &dest) {
    cvtColor(src, dest, COLOR_BGR2GRAY);
}

Mat convert_to_black_and_white(Mat src) {
    Mat gray_img, bw_img;
    
    convert_to_grayscale(src, gray_img);
    threshold(gray_img, bw_img, 127, 255, THRESH_BINARY);

    return bw_img;
}

/*
void print_image(Mat mat) {
    for (int i = 0; i < mat.rows; ++i)
	{
		for (int j = 0; j < mat.cols; ++j)
		{
			cout << (double)mat.at<uchar>(i, j) / 255 << " ";
			if (j == (mat.cols - 1))
					cout << endl;
		}
	}
}

Mat reverse_color(Mat mat) {
    Mat result = mat.clone();
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            if (mat.at<uchar>(i, j) == 255)
                result.at<uchar>(i, j) = 0;
            else
                result.at<uchar>(i, j) = 255;
            
        }
    }
    return result;
}
*/