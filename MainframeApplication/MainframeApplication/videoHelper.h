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

VideoCapture* initializeVideo(char* videoFilename);
void releaseVideo(VideoCapture* pCap);

#endif // !_videoHelper
