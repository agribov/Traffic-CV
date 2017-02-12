/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: videoHelper.cpp                                                        */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include "globals.h"
#include "videoHelper.h"

VideoCapture* initializeVideo(char* videoFilename) {
	//create the capture object
	VideoCapture* capture = new VideoCapture(videoFilename);
	if (!capture->isOpened()) {
		//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}

	return capture;
}

void releaseVideo(VideoCapture* pCap) {
	(*pCap).release();
}

void dilateFrame(Mat inputFrame, Mat* p_returnFrame) {
	//Morph type set to Rectangle, 3x3 rectangle - arbitrary size.
	Mat dElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//perform dilation
	dilate(inputFrame, *p_returnFrame, dElement);
	return;
}
void erodeFrame(Mat outputFrame, Mat* p_returnFrame) {
	//Morph type set to Rectangle, 3x3 rectangle - arbitrary size.
	Mat eElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(outputFrame, *p_returnFrame, eElement);
	return;
}