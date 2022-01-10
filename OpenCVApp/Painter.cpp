#include "Painter.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "readMedia.h"


Painter::Painter()
{
    //findColor();
    cv::VideoCapture cap(0);
    cv::Mat img, flipImg;

    while (true)
    {

        cap.read(img);
        cv::flip(img, flipImg, 1);
        findColor(flipImg);
        if (img.empty()) { break; }
        else {
            cv::imshow("image", flipImg);
            cv::waitKey(1);
        }

    }
    
}

void Painter::findColor()
{
    cv::VideoCapture cap(0);
    cv::Mat img;
    cap.read(img);


    cv::namedWindow("Trackbars", (640, 200));
    cv::createTrackbar("Hue min", "Trackbars", &hmin, 179);
    cv::createTrackbar("Sat min", "Trackbars", &smin, 255);
    cv::createTrackbar("Val min", "Trackbars", &vmin, 255);
    cv::createTrackbar("Hue max", "Trackbars", &hmax, 179);
    cv::createTrackbar("Sat max", "Trackbars", &smax, 255);
    cv::createTrackbar("Val max", "Trackbars", &vmax, 255);


    while (true)
    {
        cap.read(img);
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
        cv::inRange(imgHSV, lower, upper, mask);
        if (img.empty()) { break; }
        else
        {
            //cv::imshow("HSV", imgHSV);
            cv::imshow("mask", mask);
            cv::imshow("image", img);
            cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
            cv::waitKey(1);
        }
    }


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

void Painter::findColor(cv::Mat img)
{
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    for (int i = 0; i < paintColors.size(); i++)
    {
        cv::Scalar lower(paintColors[i][0], paintColors[i][1], paintColors[i][2]);
        cv::Scalar upper(paintColors[i][3], paintColors[i][4], paintColors[i][5]);
        cv::inRange(imgHSV, lower, upper, mask);
        imshow(to_string(i), mask);
    }
}
