/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: threshold.h                                                            */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#ifndef _threshold
#define _threshold

#include "globals.h"

int colorThreshold(Mat &frame, Mat* p_frame_threshold);
int thresholding(Mat &frame, Mat* p_frame_threshold);

extern int lowHue;
extern int highHue;

#endif // !_threshold