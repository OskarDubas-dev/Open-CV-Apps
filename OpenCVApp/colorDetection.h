#pragma once
#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>

using namespace std;


class colorDetection
{
public:
	void detectColor(cv::Mat image);
};

