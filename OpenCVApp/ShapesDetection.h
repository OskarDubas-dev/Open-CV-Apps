#pragma once
#include <opencv2/core/mat.hpp>

class ShapesDetection
{
public:
    ShapesDetection();
    void getContours(cv::Mat dilImg, cv::Mat img, int areaIgnored);
    
};
