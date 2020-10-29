#include "guo_hall.hpp"

GuoHall::Color GuoHall::set_type(uchar uc)
{
    return uc == 1 ? FG : BG;
}

void GuoHall::thinning_iteration(Mat& img, int itr)
{
    Mat marker = Mat::zeros(img.size(), CV_8UC1);
    for (int row = 1; row < img.rows; ++row)
    {
        for (int col = 1; col < img.cols; ++col)
        {
            auto p1 = set_type(img.at<uchar>(row-1, col-1));
            auto p2 = set_type(img.at<uchar>(row-1, col));
            auto p3 = set_type(img.at<uchar>(row-1, col+1));
            auto p4 = set_type(img.at<uchar>(row, col+1));
            auto p5 = set_type(img.at<uchar>(row+1, col+1));
            auto p6 = set_type(img.at<uchar>(row+1, col));
            auto p7 = set_type(img.at<uchar>(row+1, col-1));
            auto p8 = set_type(img.at<uchar>(row, col-1));

            int C  = (p2 == BG & (p3 == FG | p4 == FG)) +
                     (p4 == BG & (p5 == FG | p6 == FG)) +
                     (p6 == BG & (p7 == FG | p8 == FG)) +
                     (p8 == BG & (p1 == FG | p2 == FG));
            int N1 = (p1 == FG | p2 == FG) + (p3 == FG | p4 == FG) +
                     (p5 == FG | p6 == FG) + (p7 == FG | p8 == FG);
            int N2 = (p2 == FG | p3 == FG) + (p4 == FG | p5 == FG) +
                     (p6 == FG | p7 == FG) + (p8 == FG | p1 == FG);
            int N = std::min(N1, N2);
            int m = itr == 0 ? ((p6 == FG | p7 == FG | p1 == BG) & p8 == FG)
                             : ((p2 == FG | p3 == FG | p5 == BG) & p4 == FG);
            
            if (C == 1 && (N >= 2 && N <= 3) && m == 0)
                marker.at<uchar>(row, col) = 1;
        }
    }
    img &= ~marker;
}

void GuoHall::thinning(cv::Mat& img)
{
    img = ~img;
    img /= 255;

    Mat prev = Mat::zeros(img.size(), CV_8UC1);
    Mat diff;
    do {
        thinning_iteration(img, 0);
        thinning_iteration(img, 1);
        cv::absdiff(img, prev, diff);
        img.copyTo(prev);
    } while (cv::countNonZero(diff) > 0);
    
    img *= 255;
    img = ~img;
}

Mat GuoHall::solve_guo_hall(const string& file)
{
    Mat img = cv::imread("../images/" + file);
    if (img.empty())
    {
        cout << "Couldn't open image." << endl;
    }
    Mat skeleton;
    cvtColor(img, skeleton, COLOR_BGR2GRAY);
    GuoHall::thinning(skeleton);

    imshow("input ", img);
    imshow("output", skeleton);
    waitKey();
    
    return skeleton;
}

void GuoHall::save(const string& file, Mat& skeleton)
{
    imwrite("../output/skeleton-gh-" + file, skeleton,
            {IMWRITE_PNG_COMPRESSION});
}