
/********************************************************************************/
/*                                                                              */
/* Program: MainThermal Image Processor			                                */
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

// QT includes
#include <QApplication>

// C includes
#include <stdio.h>
#include <conio.h>

// C++ includes
#include <iostream>
#include <sstream>
#include <vector>

// Opencv includes
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "subtractionMethod.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/core/mat.hpp>

// Custom includes
/*
#include "CQtOpenCVViewerGl.h"
#include "GUI.h"
#include "threshold.h"
#include "vehicle.h"
#include "vehicleTracker.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "videoHelper.h"
*/

// Namespace declarations
//using namespace std;
//using namespace cv;

// Global variables
//extern cv::Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
//extern Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
extern char keyboard; //input from keyboard
extern int currentCarCount;

// Global values for Threshold settings
extern int low_r, low_g, low_b;
extern int high_r, high_g, high_b;
extern int erosionVal, dilationVal;
extern int lowHue, highHue;

#endif // !_globals
