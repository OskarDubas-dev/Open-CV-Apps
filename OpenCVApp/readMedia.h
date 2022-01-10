#pragma once

#include <iostream>

using namespace std;

class readMedia
{
public:

	void readImage(cv::Mat image);
	void readVideo(cv::VideoCapture videoCapture, cv::Mat video);
	static void readWebCam();


};

