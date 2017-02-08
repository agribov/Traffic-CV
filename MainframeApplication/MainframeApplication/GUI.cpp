/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: GUI.cpp                                                                */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/


/*
SOURCES
http://devblog.michalski.im/2012/05/18/combine-multiple-video-frames-into-one-using-opencv/

http://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_video_display/py_video_display.html

http://docs.opencv.org/trunk/d3/d63/classcv_1_1Mat.html#af1d014cecd1510cdf580bf2ed7e5aafc

*/

#include "globals.h"
#include "GUI.h"
#include "threshold.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"opencv2/highgui.hpp"
#include<iostream>
#include<conio.h>
#include<opencv2/core/mat.hpp>

// Variable declaration
char keyboard; //input from keyboard

void initializeGUI() {
	//create GUI windows
	namedWindow("Video Capture", WINDOW_NORMAL);
	namedWindow("FG Mask MOG 2");
	namedWindow("Thresholded");
	namedWindow("Object Detection", WINDOW_NORMAL);

	//-- Trackbars to set thresholds for hue values
	createTrackbar("Hue min", "Object Detection", &lowHue, 255, on_low_hue_thresh_trackbar);
	createTrackbar("Hue max", "Object Detection", &highHue, 255, on_high_hue_thresh_trackbar);


	//-- Trackbars to set thresholds for RGB values -- NOT CURRENTLY USED, SWITCHED TO HSV THRESHOLDING
	/*
	createTrackbar("Low R", "Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
	createTrackbar("High R", "Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
	createTrackbar("Low G", "Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
	createTrackbar("High G", "Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
	createTrackbar("Low B", "Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
	createTrackbar("High B", "Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
	*/
}

void on_low_hue_thresh_trackbar(int, void *) {
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "Object Detection", low_r);
}
void on_high_hue_thresh_trackbar(int, void *) {
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "Object Detection", low_r);
}

void on_low_r_thresh_trackbar(int, void *) {
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "Object Detection", low_r);
}
void on_high_r_thresh_trackbar(int, void *) {
	high_r = max(high_r, low_r + 1);
	setTrackbarPos("High R", "Object Detection", high_r);
}
void on_low_g_thresh_trackbar(int, void *) {
	low_g = min(high_g - 1, low_g);
	setTrackbarPos("Low G", "Object Detection", low_g);
}
void on_high_g_thresh_trackbar(int, void *) {
	high_g = max(high_g, low_g + 1);
	setTrackbarPos("High G", "Object Detection", high_g);
}
void on_low_b_thresh_trackbar(int, void *) {
	low_b = min(high_b - 1, low_b);
	setTrackbarPos("Low B", "Object Detection", low_b);
}
void on_high_b_thresh_trackbar(int, void *) {
	high_b = max(high_b, low_b + 1);
	setTrackbarPos("High B", "Object Detection", high_b);
}




/*
NO MAIN!!!!!

make a function that you can call from main.cpp
pass video capture as args
*/
int main(void) {

	cv::VideoCapture capVideo;
	cv::VideoCapture capVideo2;

	cv::Mat imgFrame;

	capVideo.open("768x576.avi");
	capVideo2.open("768x576.avi");

	if (!capVideo.isOpened()) {                                                 // if unable to open video file
		std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
		_getch();                    // it may be necessary to change or remove this line if not using Windows
		return(0);                                                              // and exit program
	}
	if (!capVideo2.isOpened()) {                                                 // if unable to open video file
		std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
		_getch();                    // it may be necessary to change or remove this line if not using Windows
		return(0);                                                              // and exit program
	}

	if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";
		_getch();
		return(0);
	}
	if (capVideo2.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";
		_getch();
		return(0);
	}


	/*************************************************************************/


	char chCheckForEscKey = 0;



	/******************************************************************/

	while (true) {
		cv::Mat frame, f1, f2, f3, f4, merged_f, roi;

		//grab and retrieve each frames of the video sequentially

		frame = capVideo.read(imgFrame);
		capVideo2.read(imgFrame);



		// initialize each frame
		f1 = cv::Mat(cv::Size(320, 240), CV_8UC3);
		f2 = cv::Mat(cv::Size(320, 240), CV_8UC3);
		f3 = cv::Mat(cv::Size(320, 240), CV_8UC3);
		f4 = cv::Mat(cv::Size(320, 240), CV_8UC3);
		frame = cv::Mat(cv::Size(320, 240), CV_8UC3);
		roi = cv::Mat(cv::Size(320, 240), CV_8UC3);

		cv::resize(frame, f1, cv::Size(), 0.5, 0.5);
		cv::flip(f1, f1, 1);

		//copy the contents of the video for simplicity's sake
		f2 = f1.clone();
		f3 = f1.clone();
		f4 = f1.clone();
		//merge all frames together into one big frame
		merged_f = cv::Mat(cv::Size(640, 480), CV_8UC3);
		roi = cv::Mat(merged_f, cv::Rect(0, 0, 320, 240));
		f1.copyTo(roi);
		roi = cv::Mat(merged_f, cv::Rect(320, 0, 320, 240));
		f2.copyTo(roi);
		roi = cv::Mat(merged_f, cv::Rect(0, 240, 320, 240));
		f3.copyTo(roi);
		roi = cv::Mat(merged_f, cv::Rect(320, 240, 320, 240));
		f4.copyTo(roi);

		//disply the big frame
		cv::imshow("Video1", merged_f);

		//wait for 40 milliseconds
		int c = cvWaitKey(40);

		//exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27) 
		if (27 == char(c)) break;
	}


	if (chCheckForEscKey != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
		cv::waitKey(0);                         // hold the windows open to allow the "end of video" message to show
	}
	// note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows

	return(0);
}