#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream> 
#include "readMedia.h"
#include "colorDetection.h"
#include "FaceDetection.h"
#include "Painter.h"
#include "ShapesDetection.h"

int main() 
{ 
	// readMedia* rm = new readMedia;
	// colorDetection* cd = new colorDetection;
	//
	//
	// //Frank Image
	// string Frankpath = "Resources/frank.jpg";
	// cv::Mat frankImg = cv::imread(Frankpath);
	//
	// //Grill or Parrot video
	// string videoPathmp4 = "Resources/grill.mp4";
	// string videoPathmov = "Resources/parrot.MOV";
	// cv::VideoCapture cap(videoPathmov);
	// cv::Mat videoMat;
	//
	// //Lamborghini photo
	// string colorDetpath = "Resources/lambo.png";
	// cv::Mat colorDetectionImg = cv::imread(colorDetpath);
	//print
	//rm->readImage(colorDetectionImg);
	//cd->detectColor(colorDetectionImg);
	//rm->readImage(frankImg);
	//rm->readVideo(cap, videoMat);
	//rm->readWebCam();

	Painter painter;




	
	cv::waitKey(0);
return 0; 
}
