/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: utilities.cpp                                                          */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#ifndef _utilities
#define _utilities

#include "globals.h"

double getDist(cv::Point A, cv::Point B);
double getDistToLine(cv::Point A, cv::Point B, cv::Point X);
void drawPoints(cv::Mat &frame, std::vector<cv::Point> points);
void onMouse(int event, int x, int y, int flags, void* userData);
void calibrate(cv::Mat frame);

extern bool endCal;
extern std::vector<std::vector<cv::Point>> calPoints;

#endif // !_utilities