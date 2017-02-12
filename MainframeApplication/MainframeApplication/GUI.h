/********************************************************************************/
/*                                                                              */
/* Program: Main


Thermal Image Processor                                   */
/*                                                                              */
/* File: GUI.h                                                                  */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#ifndef _gui
#define _gui

#include "globals.h"

// Function declaration
void initializeGUI();

void on_low_hue_thresh_trackbar(int, void *);
void on_high_hue_thresh_trackbar(int, void *);

void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *);
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);

#endif // !_gui