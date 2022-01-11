#pragma once
#include <opencv2/core/mat.hpp>

class Painter
{
private:
    cv::Mat imgHSV, mask, maskBlue, maskRed;
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    std::vector<std::vector<int>> paintColors{
       // {139,146,57,173,242,255}, //pink
      //  {9,0,76,67,167,180}, //yellow
 //{89,130,35,114,255,219} //blue
        {123,75,102,152,175,215}//purple
    };

    std::vector<cv::Scalar> colorValues{
        //{255, 192, 203}, //pink
       // {255, 255, 0}, //yellow
      // {10, 128, 255} //blue
        {255,0,255} //purple
    };

    //
    //vector holds three values {x position, y position , integer from 0 to 2 representing color in colorValues vector (value is index in vector array)}
    std::vector<std::vector<int>> drawPoints;

public:
    Painter();
    void findColor();
    void findColor(cv::Mat img);
    cv::Point getContours(cv::Mat dilImg, cv::Mat img, int areaIgnored);
    void drawOnCanvas(std::vector<std::vector<int>> drawPoints, std::vector<cv::Scalar> colorValues, cv::Mat img);
};
