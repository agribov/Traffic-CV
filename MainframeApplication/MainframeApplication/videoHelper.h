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


cv::VideoCapture* initializeVideo(char* videoFilename);
void releaseVideo(cv::VideoCapture* pCap);

void addFrameNumber(cv::Mat &frame, cv::VideoCapture *pCap); // Adds the current frame number to the display
void addCarCount(cv::Mat &frame, cv::VideoCapture *pCap);

double getDist(cv::Point A, cv::Point B);
double getDistToLine(cv::Point A, cv::Point B, cv::Point X);

#endif // !_videoHelper
