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
