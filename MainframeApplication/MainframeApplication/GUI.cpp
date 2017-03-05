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

/*
WHAT WE NEED TO DO FOR THE GUI:

1) SHORT TERM TESTING
The short term testing GUI will allow the testers (Alex, Alex, Kevin, and Molly) to ensure that the
code that they write works, and can be interacted with in an effective way. The preferred output will
look like the following:
____________________________________________________________________________________________________
|_________________________________________________________________________________________|_|  -  X |
|     _______________________________________________________      ______________________________   |
|    |   ACTUAL VIDEO FRAME                                  |    |  DEBUG TOOLS                 |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |    TRACKBAR 1                |  |
|    |                                                       |    |    TRACKBAR 2                |  |
|    |                                                       |    |    TRACKBAR 3                |  |
|    |                                                       |    |    TRACKBAR 4                |  |
|    |                                                       |    |       ETC..                  |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |   FEED 1   ON OFF            |  |
|    |                                                       |    |   FEED 2   ON OFF            |  |
|    |                                                       |    |   FEED 3   ON OFF            |  |
|    |                                                       |    |   FEED 4   ON OFF            |  |
|    |                                                       |    |   FEED 5   ON OFF            |  |
|    |                                                       |    |   FEED 6   ON OFF            |  |
|    |_______________________________________________________|    |       ETC..                  |  |
|                                                                 |                              |  |
|     _______________________________________________________     |                              |  |
|    |  FRAME DEPENDENT ON DEBUG TOOLS SETTINGS              |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |_______________________________________________________|    |______________________________|  |
|                                                                                                   |
|___________________________________________________________________________________________________|


Depending on what feed is toggled on and off in the debug tools interactive bar sets the frame in the
frame dependent window. All of the trackbar features should edit the frame inside the WINDOW, not the
frame itself.

*/

/*  HOW TO MAKE A WINDOW THAT DISPLAYS MORE THAN ONE VIDEO FEED IN IT */
// first, read this short tutorial!
// http://devblog.michalski.im/2012/05/18/combine-multiple-video-frames-into-one-using-opencv/

/*  we need to
1) make a "master window" - this is the only one with an 'x' '-' and 'dock'
2) find a reigon of interest that we can potnetially change video streams in
2.1) there should definately be two, one for the non-processed image and
one for the processed image. There should potentially be a third for the
toolbar, but I think that establishing the streams should happen first,
and messing with them should happen second.
3) create buttons that change the video in the reigon of interest (roi)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

WHERE WE ARE AS OF LAST PUSH:
We have made a master window with multiple feeds playing through it, but
the original feed does not come through. We need this feed to show up, but
in the meantime we can work on other solutions-
such as creating an enviornment for a proper trackbar. The problem with
the current location for the trackbar is that if it has to edit more
than 5 things, the trackbar takes up half of the height of my screen.
I want to make the adjustable trackbar and toggle buttons vertical on
the righthand side of the screen.

Another area that can be worked on while we try to get the original feed
up and running is creating a toggle button that shows different feeds when
pressed. This would be included in the trackbar toolbox
*/

/* LONG TERM DESIGN FOR GUI
the above GUI is solely for the debugging and testing purposes of our computer vision
application. The deliverable GUI will have 1) the original thermal video of an intersection
showing 2) A video of the objects being tracked and located below the original video 3) a
map of the intersection, with the current direction of the display overlayed upon it 4) a
toolbox, similar to that of the testing toolbox, that switches the video being shown and
alters the image processing being applied to the video.

____________________________________________________________________________________________________
|_________________________________________________________________________________________|_|  -  X |
|     _______________________________________________________      ______________________________   |
|    |   ACTUAL VIDEO FRAME                                  |    |  DEBUG TOOLS                 |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |    TRACKBAR 1                |  |
|    |                                                       |    |    TRACKBAR 2                |  |
|    |                                                       |    |    TRACKBAR 3                |  |
|    |                                                       |    |    TRACKBAR 4                |  |
|    |                                                       |    |       ETC..                  |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |_______________________________________________________|    |   FEED 1   ON OFF            |  |
|     _______________________________________________________     |   FEED 2   ON OFF            |  |
|    |   EDITED VIDEO FRAME                                  |    |   FEED 3   ON OFF            |  |
|    |                                                       |    |   FEED 4   ON OFF            |  |
|    |                                                       |    |   FEED 5   ON OFF            |  |
|    |                                                       |    |   FEED 6   ON OFF            |  |
|    |                                                       |    |       ETC..                  |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |_______________________________________________________|    |                              |  |
|     _______________________________________________________     |                              |  |
|    |   INTERACTIVE MAP FRAME                               |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |                                                       |    |                              |  |
|    |_______________________________________________________|    |______________________________|  |
|                                                                                                   |
|___________________________________________________________________________________________________|



*/

#include "globals.h"

// Variable declaration
char keyboard; //input from keyboard
int erosionVal= 0, dilationVal = 0;
int low_r = 30, low_g = 30, low_b = 30;
int high_r = 100, high_g = 100, high_b = 100;
int lowHue = 0, highHue = 50;

void initializeGUI() {


	//create GUI windows
	namedWindow("Video Capture", WINDOW_NORMAL);     // Video capture is also used in main.cpp to show current frame and masks
	//namedWindow("FG Mask MOG 2");                    // FG Mask MOG 2 "" ^ as above
	//namedWindow("Thresholded");						 // Thresholded "" ^ as above
	//namedWindow("Video Capture", WINDOW_NORMAL);
	//namedWindow("Debug 1");
	//namedWindow("Debug 2");
	//namedWindow("Thresholded");
	//namedWindow("Object Detection", WINDOW_NORMAL);

	//-- Trackbars to set thresholds for hue values
	createTrackbar("Hue min", "Object Detection", &lowHue, 255, on_low_hue_thresh_trackbar);
	createTrackbar("Hue max", "Object Detection", &highHue, 255, on_high_hue_thresh_trackbar);

	createTrackbar("Erosion", "Object Detection", &erosionVal, 25, erodeTrackbar);
	createTrackbar("Dilation", "Object Detection", &dilationVal, 100, dilateTrackbar);






	//-- Trackbars to set thresholds for RGB values -- NOT CURRENTLY USED, SWITCHED TO HSV THRESHOLDING
	/*
	createTrackbar("Low R", "Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
	createTrackbar("High R", "Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
	createTrackbar("Low G", "Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
	createTrackbar("High G", "Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
	createTrackbar("Low B", "Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
	createTrackbar("High B", "Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
	*/


	namedWindow("Master Window");
	createTrackbar("Hue min", "Master Window", &lowHue, 255, on_low_hue_thresh_trackbar);
	createTrackbar("Hue max", "Master Window", &highHue, 255, on_high_hue_thresh_trackbar);
/* putting both trackbars on the master window, when built I think that this is why they show up on the first 
window that popps up. If you close out of the window, a new master window will appear- this time without the 
trackbars. Is this a bug? */



	int master_window_w = 550;
	int master_window_h = 400;

	//resizeWindow("Master Window", master_window_w, master_window_h);
}






cv::Mat makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, size_t nRows, cv::Mat original) {

	size_t N = vecMat.size();   //warning initilization size_t to int
	nRows = nRows > N ? N : nRows;
	int edgeThickness = 10;
	int imagesPerRow = ceil((N) / nRows);  //warning initialization double to int
	int resizeHeight = floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness; //warning initialization double to int
	int maxRowLength = 0;

	/*The above chunk of code sets variables for formatting reasons*/

	std::vector<int> resizeWidth;
	for (int i = 0; i < N;) {
		int thisRowLen = 0;
		for (int k = 0; k < imagesPerRow; k++) {
			double aspectRatio = double(vecMat[i].cols) / vecMat[i].rows;
			int temp = int(ceil(resizeHeight * aspectRatio));
			resizeWidth.push_back(temp);
			thisRowLen += temp;
			if (++i == N) break;
		}
		if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
			maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
		}
	}

	/* The above chunk of code makes the videos the optimal size to display in the window*/

	int windowWidth = maxRowLength;
	cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, Scalar(0, 0, 0));

	for (int k = 0, i = 0; i < nRows; i++) {
		int y = i * resizeHeight + (i + 1) * edgeThickness;
		int x_end = edgeThickness;
		/* the above formats the images in each row*/
		for (int j = 0; j < imagesPerRow && k < N; k++, j++) {
			int x = x_end;

			if (i == 0 && j == 0)
			{
				cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
				cv::Size s = canvasImage(roi).size();

				// change the number of channels to three
				cv::Mat target_ROI(s, CV_8UC3);

				if (vecMat[k].channels() != canvasImage.channels()) {
					if (vecMat[k].channels() == 1) {
						cv::cvtColor(vecMat[k], target_ROI, CV_GRAY2BGR, 3); /* this is where all of the images are converted to
																			 greyscale- is that what is happening to the colored image?
																			 I there a way to get all of the images to show without
																			 converting?*/
					}
				}
				cv::resize(original, original, s);
				if (original.type() != canvasImage.type()) {
					original.convertTo(original, canvasImage.type());
				}
				original.copyTo(canvasImage(roi));
				x_end += resizeWidth[k] + edgeThickness;
			}
			/*The above block controls what is shown in the first video frame.
			my plan is to take the image passed in as an argument and display it there*/
			else
			{
				cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
				cv::Size s = canvasImage(roi).size();

				// change the number of channels to three
				cv::Mat target_ROI(s, CV_8UC3);
				if (vecMat[k].channels() != canvasImage.channels()) {
					if (vecMat[k].channels() == 1) {
						cv::cvtColor(vecMat[k], target_ROI, CV_GRAY2BGR, 3); /* this is where all of the images are converted to
																		  greyscale- is that what is happening to the colored image?
																		  I there a way to get all of the images to show without
																		  converting?*/
					}
				}
				cv::resize(target_ROI, target_ROI, s);
				if (target_ROI.type() != canvasImage.type()) {
					target_ROI.convertTo(target_ROI, canvasImage.type());
				}
				target_ROI.copyTo(canvasImage(roi));
				x_end += resizeWidth[k] + edgeThickness;
			}
		}
	}
	return canvasImage;
}

void on_low_hue_thresh_trackbar(int, void *) {
	lowHue = min(highHue - 1, low_r);
	setTrackbarPos("Low Hue", "Object Detection", lowHue);
}
void on_high_hue_thresh_trackbar(int, void *) {
	highHue = max(highHue, lowHue);
	setTrackbarPos("Low Hue", "Object Detection", lowHue);
}
void erodeTrackbar(int, void *) {
	setTrackbarPos("Erosion", "Object Detection", erosionVal);
}
void dilateTrackbar(int, void *) {
	setTrackbarPos("Dilation", "Object Detection", dilationVal);
}


// BELOW: NOT USED

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