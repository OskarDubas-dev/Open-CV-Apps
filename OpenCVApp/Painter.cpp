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
        // cv::flip(flipImg, flipImg, 0);
        findColor(flipImg);
        if (img.empty()) { break; }
        else
        {
            drawOnCanvas(drawPoints, colorValues, flipImg);
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
        cv::Point drawPoint = getContours(mask, img, 1000);
        if (drawPoint.x != 0 && drawPoint.y != 0)
        {
            drawPoints.push_back({drawPoint.x, drawPoint.y, i});
        }
    }
}

cv::Point Painter::getContours(cv::Mat dilImg, cv::Mat img, int areaIgnored)
{
    std::vector<std::vector<cv::Point>> contours;


    std::vector<cv::Vec4i> hierarchy;
    //find the contours in the image(dilImg) and draw on image(img)
    cv::findContours(dilImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
    std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
    std::vector<cv::Rect> boundRectangle(contours.size());

    std::string objectType;

    cv::Point drawPoint(0, 0);

    //reduce the noise, draw only if area of contour is above given threshold
    for (int i = 0; i < contours.size(); i++)
    {
        int area = cv::contourArea(contours[i]);
        if (area > areaIgnored)
        {
            float perimeter = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], contoursPoly[i], 0.02 * perimeter, true);


            //rectangle that will be drawn around the object
            boundRectangle[i] = cv::boundingRect(contoursPoly[i]);
            drawPoint.x = boundRectangle[i].x + boundRectangle[i].width / 2;
            drawPoint.y = boundRectangle[i].y;

            cv::drawContours(img, contoursPoly, i, cv::Scalar(255, 0, 255), 2);
        }
    }

    return drawPoint;
}

void Painter::drawOnCanvas(std::vector<std::vector<int>> drawPoints, std::vector<cv::Scalar> colorValues, cv::Mat img)
{
    for (int i = 0; i < drawPoints.size(); i++)
    {
        cv::circle(img, (cv::Point(drawPoints[i][0], drawPoints[i][1])), 10, colorValues[drawPoints[i][2]], cv::FILLED);
    }
}
