#include "colorDetection.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "readMedia.h"

using namespace std;

void colorDetection::detectColor(cv::Mat image)
{
    cv::Mat imgHSV, mask;
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;

    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);

    cv::namedWindow("Trackbars", (640, 200));
    cv::createTrackbar("Hue min", "Trackbars", &hmin, 179);


    while (true)
    {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(imgHSV, lower, upper, mask);
        //cv::imshow("HSV", imgHSV);
        cv::imshow("mask", mask);
        cv::waitKey(1);
    }
}
