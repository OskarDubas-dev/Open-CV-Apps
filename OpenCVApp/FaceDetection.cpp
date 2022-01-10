#include "FaceDetection.h"

#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>

FaceDetection::FaceDetection()
{

    //std::string path = "Resources/DSC_0400.jpg";
    //std::string path = "Resources/frank.jpg";
    //std::string path = "Resources/DSC_0965.jpg";
    std::string path = "Resources/img040.jpg";
   
    

    cv::Mat img = cv::imread(path);

    //camera
    cv::VideoCapture cap(0);
    cv::Mat imgCam;
    std::vector<cv::Rect> faces;
    if (true)
    {
        while (true)
        {
            cap.read(imgCam);
            if (imgCam.empty()) { break; }
            else
            {
                cv::CascadeClassifier faceCascade;
                if (faceCascade.load("Resources/haarcascade_frontalface_default.xml"))
                {
                    
                    faceCascade.detectMultiScale(imgCam, faces, 1.1, 10);

                    for (int i = 0; i < faces.size(); i++)
                    {
                        cv::rectangle(imgCam, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 2);
                    }
                    /*for (auto value : faces)
                    {
                        cv::rectangle(imgCam, value.tl(), value.br(), cv::Scalar(255, 0, 255), 2);
                    }*/
                }
                cv::imshow("image", imgCam);
                cv::waitKey(1);
            }
        }
    }


    cv::CascadeClassifier faceCascade;
    if (faceCascade.load("Resources/haarcascade_frontalface_default.xml"))
    {
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(img, faces, 1.1, 10);

        for (int i = 0; i < faces.size(); i++)
        {
            cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 2);
        }
    }

    cv::imshow("image", img);
}
