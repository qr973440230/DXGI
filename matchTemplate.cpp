//
// Created by qinrui on 2020/5/13.
//

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void getNextMinLoc(Mat &result,
                   Point &minLoc, Point &maxLoc,
                   double &minValue, double &maxValue,
                   int templateW, int templateH);

int main() {
    Mat src = imread("1.png");
    Mat tmp = imread("test.png");

    int resultRows = src.rows - tmp.rows + 1;
    int resultCols = src.cols - tmp.cols + 1;

    Mat result;
    result.create(resultRows, resultCols, CV_32FC1);
    matchTemplate(src, tmp, result, TM_SQDIFF_NORMED);

    normalize(result, result, 0, 1, NORM_MINMAX);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    cout << "MinVal: " << minVal << endl <<
         "MaxVal: " << maxVal << endl <<
         "MinPoint: " << minLoc << endl <<
         "MaxPoint: " << maxLoc << endl;


    while (minVal < 0.5 && minVal >= 0) {
        getNextMinLoc(result, minLoc, maxLoc, minVal, maxVal, tmp.rows, tmp.cols);
        cout << "MinVal: " << minVal << endl <<
             "MaxVal: " << maxVal << endl <<
             "MinPoint: " << minLoc << endl <<
             "MaxPoint: " << maxLoc << endl;
    }

    return 0;
}


void getNextMinLoc(Mat &result,
                   Point &minLoc, Point &maxLoc,
                   double &minValue, double &maxValue,
                   int templateW, int templateH) {

    int startX = minLoc.x - templateW / 3;
    int startY = minLoc.y - templateH / 3;
    int endX = minLoc.x + templateW / 3;
    int endY = minLoc.y + templateH / 3;

    if (startX < 0 || startY < 0) {
        startX = 0;
        startY = 0;
    }
    if (endX > result.cols - 1 || endY > result.rows - 1) {
        endX = result.cols - 1;
        endY = result.rows - 1;
    }

    int x, y;
    for (y = startY; y < endY; ++y) {
        for (x = startX; x < endX; ++x) {
            auto *data = result.ptr<double>(y);
            data[x] = maxValue;
        }
    }

    // 获取最新的值
    double newMinValue, newMaxValue;
    Point newMinLoc, newMaxLoc;
    minMaxLoc(result, &newMinValue, &newMaxValue, &newMinLoc, &newMaxLoc);

    minValue = newMinValue;
    maxValue = newMaxValue;
    minLoc = newMinLoc;
    maxLoc = newMaxLoc;
}


