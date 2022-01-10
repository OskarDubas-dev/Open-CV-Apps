#include "ShapesDetection.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


ShapesDetection::ShapesDetection()
{
    //load and display the image
    std::string path = "Resources/shapes.png";
    cv::Mat img = cv::imread(path);

    //variables declarations
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    cv::imshow("Image", img);

    /***Preprocessing***/
    //in order to use Canny edge detection 1st we convert image to gray scale and then add blur
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);

    //dilate the image so edges are more visible
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imgCanny, imgDil, kernel);

    //display each step
    //cv::imshow("blur", imgBlur);
    //cv::imshow("canny", imgCanny);
    //cv::imshow("dilate", imgDil);

    getContours(imgDil, img, 1000);
    cv::imshow("ImgCont", img);

    cv::VideoCapture cap(0);
    cv::Mat imgCam;

    /*while (true)
    {
        cv::Mat imgCamGray, imgCamBlur, imgCamCanny, imgCamDil;
        cap.read(imgCam);
        if (img.empty()) { break; }
        else
        {
            cv::cvtColor(imgCam, imgCamGray, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(imgCamGray, imgCamBlur, cv::Size(3, 3), 3, 0);
            cv::Canny(imgCamBlur, imgCamCanny, 25, 75);

            //dilate the image so edges are more visible
            cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
            cv::dilate(imgCamCanny, imgCamDil, kernel);
            cv::imshow("image", imgCamDil);
            // getContours(imgCamDil, imgCam, 1000);
            // cv::imshow("image", imgCam);
            cv::waitKey(1);
        }
    }*/
}

void ShapesDetection::getContours(cv::Mat dilImg, cv::Mat img, int areaIgnored)
{
    std::vector<std::vector<cv::Point>> contours;


    std::vector<cv::Vec4i> hierarchy;
    //find the contours in the image(dilImg) and draw on image(img)
    cv::findContours(dilImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
    std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
    std::vector<cv::Rect> boundRectangle(contours.size());

    std::string objectType;

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
            

            int objectCorner = static_cast<int>(contoursPoly[i].size());

            if (objectCorner == 3) { objectType = "Triangle"; }
            else if (objectCorner == 4)
            {
                float aspRatio = static_cast<float>(boundRectangle[i].width) / static_cast<float>(boundRectangle[i].
                    height);
                if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
                else { objectType = "Rectangle"; }
            }
            else if (objectCorner > 4) { objectType = "Circle"; }

            cv::drawContours(img, contoursPoly, i, cv::Scalar(255, 0, 255), 2);
            cv::rectangle(img, boundRectangle[i].tl(), boundRectangle[i].br(), cv::Scalar(0, 255, 0), 5);
            cv::putText(img, objectType, {boundRectangle[i].x, boundRectangle[i].y -5}, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,60,30), 1);
        }
       
    }
}
