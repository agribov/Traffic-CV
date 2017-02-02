/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: main.cpp                                                               */
/*                                                                              */
/* Author(s): Alex Gribov, Kevin Smida                                          */
/*                                                                              */
/********************************************************************************/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void connectToCamera();

int main(int argc, char* argv[]) {
	
	// FIXME: In the future all declarations will be in file globals.h, but I left this here for now so everyone can see how the stream works.
	VideoCapture cap;		// Number is the ID of video device.

	//*****************************************************//
	// BEGIN SETUP                                         //
	//*****************************************************//

	// FIXME: Future home of FLIR ONE address
	const std::string videoStreamAddress = "http://10.253.77.174:8080/cam_1.mjpg";
	// Address of sample video feed
	const std::string sampleStreamAddress = "http://66.193.157.18/mjpg/video.mjpg";
	const std::string ipCamStreamAddress = "http://192.168.0.102:8080/video";
	

	// Load the videostrem into VideoCapture object.
	cap.open(sampleStreamAddress);
	if (!cap.isOpened())  // If not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	// Not yet needed, but may be useful
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	// Create output windows for displaying video
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	namedWindow("MyNegativeVideo", CV_WINDOW_AUTOSIZE);

	//*****************************************************//
	// BEGIN SETUP                                         //
	//*****************************************************//

	//*****************************************************//
	// BEGIN EXECUTION                                     //
	//*****************************************************//

	// While loop is main program body -- Gets image from stream, operates on it, then repeats
	// Loop breaks when user hits "esc" key
	while (1) {
		Mat frame;
		Mat contours;

		bool bSuccess = cap.read(frame); // Read a new frame from video

		if (!bSuccess) { // If not success, break loop
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		//flip(frame, frame, 1);
		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		// Sample image processing
		Canny(frame, contours, 500, 1000, 5, true);
		imshow("MyNegativeVideo", contours);

		if (waitKey(30) == 27) {//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}

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