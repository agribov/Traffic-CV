/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: main.cpp                                                               */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

/************************** AZS Start *******************************************/
#include "subtractionMethod.h"
//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
/************************** AZS End *********************************************/
using namespace cv;
using namespace std;
/************************** AZS Start *******************************************/
// Global variables
Mat frame; //current frame
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
char keyboard; //input from keyboard
			   /************************** AZS End *********************************************/

void connectToCamera();
void processVideo(char* videoFilename);	//AZS

int main(int argc, char* argv[])
{
	//create GUI windows
	namedWindow("Frame");
	namedWindow("FG Mask MOG 2");
	//create Background Subtractor objects
	pMOG2 = createBackgroundSubtractorMOG2(); //MOG2 approach

	processVideo("http://66.193.157.18/mjpg/video.mjpg");

	//destroy GUI windows
	destroyAllWindows();
	return EXIT_SUCCESS;
}

void processVideo(char* videoFilename) {
	//create the capture object
	VideoCapture capture(videoFilename);
	if (!capture.isOpened()) {
		//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}
	//read input data. ESC or 'q' for quitting
	keyboard = 0;
	while (keyboard != 'q' && keyboard != 27) {
		//read the current frame
		if (!capture.read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}
		//update the background model
		pMOG2->apply(frame, fgMaskMOG2);
		//get the frame number and write it on the current frame
		stringstream ss;
		rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
			cv::Scalar(255, 255, 255), -1);
		ss << capture.get(CAP_PROP_POS_FRAMES);
		string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
			FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
		//show the current frame and the fg masks
		imshow("Frame", frame);
		imshow("FG Mask MOG 2", fgMaskMOG2);
		//get the input from the keyboard
		keyboard = (char)waitKey(30);
	}
	//delete capture object
	capture.release();
}


//int main(int argc, char* argv[]) {
//
//	// FIXME: In the future all declarations will be in file globals.h, but I left this here for now so everyone can see how the stream works.
//	VideoCapture cap;		// Number is the ID of video device.
//
//	//*****************************************************//
//	// BEGIN SETUP                                         //
//	//*****************************************************//
//
//	// FIXME: Future home of FLIR ONE address
//	const std::string videoStreamAddress = "http://192.168.0.117:8080/cam_1.mjpg";
//	// Address of sample video feed
//	const std::string sampleStreamAddress = "http://66.193.157.18/mjpg/video.mjpg";
//
//	// Load the videostrem into VideoCapture object.
//	cap.open(sampleStreamAddress);
//	if (!cap.isOpened())  // If not success, exit program
//	{
//		cout << "Cannot open the video cam" << endl;
//		return -1;
//	}
//
//	// Not yet needed, but may be useful
//	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
//	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
//
//	cout << "Frame size : " << dWidth << " x " << dHeight << endl;
//
//	// Create output windows for displaying video
//	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
//	namedWindow("MyNegativeVideo", CV_WINDOW_AUTOSIZE);
//
//	//*****************************************************//
//	// BEGIN SETUP                                         //
//	//*****************************************************//
//
//	//*****************************************************//
//	// BEGIN EXECUTION                                     //
//	//*****************************************************//
//
//	// While loop is main program body -- Gets image from stream, operates on it, then repeats
//	// Loop breaks when user hits "esc" key
//	while (1) {
//		Mat frame;
//		Mat contours;
//
//		bool bSuccess = cap.read(frame); // Read a new frame from video
//
//		if (!bSuccess) { // If not success, break loop
//			cout << "Cannot read a frame from video stream" << endl;
//			break;
//		}
//
//		flip(frame, frame, 1);
//		imshow("MyVideo", frame); //show the frame in "MyVideo" window
//
//		// Sample image processing
//		Canny(frame, contours, 500, 1000, 5, true);
//		imshow("MyNegativeVideo", contours);
//
//		if (waitKey(30) == 27) {//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
//			cout << "esc key is pressed by user" << endl;
//			break;
//		}
//	}
//	return 0;
//}

// TEST FUNCTION, IGNORE THIS:
void connectToCamera() {
	VideoCapture stream(0);		// Number is the ID of video device.
	stream.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	stream.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	stream.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);

	if (!stream.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera";
	}

	//unconditional loop
	while (true) {
		Mat cameraFrame;
		stream.read(cameraFrame);
		imshow("cam", cameraFrame);
		if (waitKey(30) >= 0)
			break;
	}
}