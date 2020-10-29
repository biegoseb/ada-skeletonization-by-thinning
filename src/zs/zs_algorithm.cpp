#include "zs_algorithm.hpp"
#include <utility>

ZSAlgorithm::ZSAlgorithm(Mat img) : img(move(img)) {}

ZSAlgorithm::~ZSAlgorithm() = default;

void ZSAlgorithm::verify_conditions(vector<pixel> & aux, int tmp){
    int row, col;   
    for (row = 1; row < img.rows - 1; ++row){                                 /* c6*(m-1) */
        for (col = 1; col < img.cols - 1; ++col){                          /* c7*(n-1)*(m-2) */
            // cout << row << " - " << col << endl;
            auto p1 = set_color(img.at<uchar>(row, col));                       /* c8 */
            auto [p2, p3, p4, p5, p6, p7, p8, p9] = get_neighbours(row, col);   /* c9 */

            if( p1 == BLACK and                                                 /* c10 */
                in_range(count_black(row, col), 2, 6) and                       /* c11 */
                get_transitions(row, col) == 1)
            {
                if (tmp == 1 and                                                /* c12 */
                    (p2 == WHITE or p4 == WHITE or p6 == WHITE) and             /* c13 */
                    (p4 == WHITE or p6 == WHITE or p8 == WHITE))                /* c14 */
                    aux.emplace_back(row, col);                                 /* c15 */

                else if (tmp == 2 and                                           /* c12 */
                    (p2 == WHITE or p4 == WHITE or p8 == WHITE) and             /* c13 */
                    (p2 == WHITE or p6 == WHITE or p8 == WHITE))                /* c14 */
                    aux.emplace_back(row, col);                                 /* c15 */
            }
        }
    }
        for (auto const &[row, col] : aux){                                     /* c16*(n-1)*(m-1) */

            cout << "removing: " << row << ", " << col << endl;

            img.at<uchar>(row, col) = WHITE;                                        /* c */
        }
}


//aumentar cuadro blanco al rededor de la imagen

/* Worst Case Analysis:     */
Mat ZSAlgorithm::solve()
{
    int row, col;                                                                   /* c1 */
    vector<pixel> pixels1 = {dummyPixel};                                           /* c2 */
    vector<pixel> pixels2 = {dummyPixel};                                           /* c3 */
    while (!(pixels1.empty() and pixels2.empty())){                                 /* c4* */       /* TO DO */
        pixels1.clear();                                                            /* c5 */

        cout << "Step 1" << endl;
        verify_conditions(pixels1, 1); 

        imshow("result", img);
        waitKey(0);
        pixels2.clear();                                                            /* c5 */

        cout << "Step 2" << endl;
        verify_conditions(pixels2,2);

        imshow("result", img);
        waitKey(0);
    }
    return img;
}

ZSAlgorithm::neighbours ZSAlgorithm::get_neighbours(int row, int col)
{
    auto p2 = set_color(img.at<uchar>(row - 1, col));
    auto p3 = set_color(img.at<uchar>(row - 1, col + 1));
    auto p4 = set_color(img.at<uchar>(row, col + 1));
    auto p5 = set_color(img.at<uchar>(row + 1, col + 1));
    auto p6 = set_color(img.at<uchar>(row + 1, col));
    auto p7 = set_color(img.at<uchar>(row + 1, col - 1));
    auto p8 = set_color(img.at<uchar>(row, col - 1));
    auto p9 = set_color(img.at<uchar>(row - 1, col - 1));
    return neighbours(p2, p3, p4, p5, p6, p7, p8, p9);                /* 8*c1 = c */
}

ZSAlgorithm::Color ZSAlgorithm::set_color(uchar color)
{
    return color == 255 ? WHITE : BLACK;
}

array<ZSAlgorithm::Color, 9> ZSAlgorithm::get_array(int row, int col)
{
    array<Color, 9> arr{};
    arr[0] = set_color(img.at<uchar>(row - 1, col));
    arr[1] = set_color(img.at<uchar>(row - 1, col + 1));
    arr[2] = set_color(img.at<uchar>(row, col + 1));
    arr[3] = set_color(img.at<uchar>(row + 1, col + 1));
    arr[4] = set_color(img.at<uchar>(row + 1, col));
    arr[5] = set_color(img.at<uchar>(row + 1, col - 1));
    arr[6] = set_color(img.at<uchar>(row, col - 1));
    arr[7] = set_color(img.at<uchar>(row - 1, col - 1));
    arr[8] = set_color(img.at<uchar>(row - 1, col));
    return arr;                                                      /* 8c */
}

int ZSAlgorithm::get_transitions(int row, int col)
{
    auto arr = get_array(row, col);                                  /* 8c1 */
    int i;                                                           /* c2 */
    int transitions = 0;                                             /* c3 */

    for (i = 0; i < arr.size() - 1; ++i)                             /* 8*c4 */
    {
        if (arr[i] == WHITE and arr[i + 1] == BLACK)                 /* c5 */
            ++transitions;                                           /* c6 */
    }
    return transitions;                                              /* 8c1 + c2 + c3 + 8*c4 + c5 + c6 = c */
}

int ZSAlgorithm::count_black(int row, int col)
{
    auto arr = get_array(row, col);                                  /* 8*c1 */
    return count_if(arr.begin(), arr.end() - 1, isBlack);            /* 8*c1 = c */
}

bool ZSAlgorithm::isBlack(Color color)
{
    return color == BLACK;                                           /* c */
}

bool ZSAlgorithm::in_range(int num, int low, int high)
{
    return (low <= num) and (num <= high);                           /* c */
}