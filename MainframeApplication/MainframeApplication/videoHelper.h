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

#ifndef _videoHelper
#define _videoHelper

#include "globals.h"

void processVideo(VideoCapture* pCap);

VideoCapture* initializeVideo(char* videoFilename);
void releaseVideo(VideoCapture* pCap);

void addFrameNumber(Mat &frame, VideoCapture *pCap); // Adds the current frame number to the display


#endif // !_videoHelper
