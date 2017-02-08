/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: GUI.cpp                                                                */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include "globals.h"
#include "GUI.h"
#include "threshold.h"

// Variable declaration
char keyboard; //input from keyboard

void initializeGUI() {


	//create GUI windows
	namedWindow("Video Capture", WINDOW_NORMAL);
	namedWindow("FG Mask MOG 2");
	namedWindow("Thresholded");
	namedWindow("Object Detection", WINDOW_NORMAL);

	//-- Trackbars to set thresholds for hue values
	createTrackbar("Hue min", "Object Detection", &lowHue, 255, on_low_hue_thresh_trackbar);
	createTrackbar("Hue max", "Object Detection", &highHue, 255, on_high_hue_thresh_trackbar);


	//-- Trackbars to set thresholds for RGB values -- NOT CURRENTLY USED, SWITCHED TO HSV THRESHOLDING
	/*
	createTrackbar("Low R", "Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
	createTrackbar("High R", "Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
	createTrackbar("Low G", "Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
	createTrackbar("High G", "Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
	createTrackbar("Low B", "Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
	createTrackbar("High B", "Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
	*/
}

void on_low_hue_thresh_trackbar(int, void *) {
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "Object Detection", low_r);
}
void on_high_hue_thresh_trackbar(int, void *) {
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "Object Detection", low_r);
}

void on_low_r_thresh_trackbar(int, void *) {
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "Object Detection", low_r);
}
void on_high_r_thresh_trackbar(int, void *) {
	high_r = max(high_r, low_r + 1);
	setTrackbarPos("High R", "Object Detection", high_r);
}
void on_low_g_thresh_trackbar(int, void *) {
	low_g = min(high_g - 1, low_g);
	setTrackbarPos("Low G", "Object Detection", low_g);
}
void on_high_g_thresh_trackbar(int, void *) {
	high_g = max(high_g, low_g + 1);
	setTrackbarPos("High G", "Object Detection", high_g);
}
void on_low_b_thresh_trackbar(int, void *) {
	low_b = min(high_b - 1, low_b);
	setTrackbarPos("Low B", "Object Detection", low_b);
}
void on_high_b_thresh_trackbar(int, void *) {
	high_b = max(high_b, low_b + 1);
	setTrackbarPos("High B", "Object Detection", high_b);
}