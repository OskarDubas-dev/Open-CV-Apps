#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "readMedia.h"

using namespace std;


/// <summary>
/// Importing Images
/// </summary>
/// <param name="image">mat object to display</param>
void readMedia::readImage(cv::Mat image)
{
	cv::imshow("image", image);
}
/// <summary>
/// Importing Videos
/// </summary>
/// <param name="videoCapture"></param>
/// <param name="video"></param>
void readMedia::readVideo(cv::VideoCapture videoCapture, cv::Mat video)
{
	while (true)
	{
		
		videoCapture.read(video);
		if (video.empty()) { break; }
		else {
			cv::imshow("image", video);
			cv::waitKey(20);
		}
		
	}
}
/// <summary>
/// Importing webCam stream (default web cam)
/// </summary>
void readMedia::readWebCam()
{
	cv::VideoCapture cap(0);
	cv::Mat img;

	while (true)
	{

		cap.read(img);
		if (img.empty()) { break; }
		else {
			cv::imshow("image", img);
			cv::waitKey(1);
		}

	}
}
