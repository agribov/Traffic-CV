/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: threshold.cpp                                                          */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include "globals.h"

// Variable declaration
int low_r = 30, low_g = 30, low_b = 30;
int high_r = 100, high_g = 100, high_b = 100;
int lowHue = 0, highHue = 50;

int colorThreshold(Mat &frame, Mat* p_frame_threshold) {
	Mat hsvFrame;
	// Convert frame to HSV space, to threshold color
	cvtColor(frame, hsvFrame, COLOR_BGR2HSV);

	inRange(hsvFrame, Scalar(lowHue, 100, 100), Scalar(highHue, 255, 255), (*p_frame_threshold));
	return 0;
}

int thresholding(Mat &frame, Mat* p_frame_threshold) {
	//int low_r = 30, low_g = 30, low_b = 30;
	//int high_r = 100, high_g = 100, high_b = 100;

	if (frame.empty())
		return -1;

	//-- Detect the object based on RGB Range Values
	inRange(frame, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), (*p_frame_threshold));

	//-- Show the frames
	//imshow("Object Detection", (*p_frame_threshold));

	return 0;
}

//Testing github
