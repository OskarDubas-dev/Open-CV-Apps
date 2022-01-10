#pragma once
#include <opencv2/core/mat.hpp>

class Painter
{
private:
    cv::Mat imgHSV, mask, maskBlue, maskRed;
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    std::vector<std::vector<int>> paintColors{
        {72,151,177,133,222,255}, //blue
        {0, 186, 108, 82, 255, 255}, //red

    };

    std::vector<cv::Scalar> colorValues{
        {255, 0, 0}, //blue
        {0, 0, 255} //red
    };

public:
    Painter();
    void findColor();
    void findColor(cv::Mat img);
};
