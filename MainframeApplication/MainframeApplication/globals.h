
/********************************************************************************/
/*                                                                              */
/* Program: Main


Thermal Image Processor                                   */
/*                                                                              */
/* File: globals.cpp                                                            */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#ifndef _globals
#define _globals

// This file contains any declarations that are ubiquitous throughout the entire software

// Opencv includes
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "subtractionMethod.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

// C includes
#include <stdio.h>

// C++ includes
#include <iostream>
#include <sstream>
#include <vector>

// Namespace declarations
using namespace cv;
using namespace std;

// Global variables
extern Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
extern Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
extern char keyboard; //input from keyboard

// Global values for Threshold settings
extern int low_r, low_g, low_b;
extern int high_r, high_g, high_b;
extern int erosionVal, dilationVal;
extern int lowHue, highHue;

#endif // !_globals
