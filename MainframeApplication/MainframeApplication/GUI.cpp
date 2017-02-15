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

#include <stdarg.h>

// Variable declaration
char keyboard; //input from keyboard

/////////////////////////////////////////////////// -AZS



void initializeGUI(char* title, int nArgs, ...) {
	//create GUI windows
	//namedWindow("Video Capture", WINDOW_NORMAL);     // Video capture is also used in main.cpp to show current frame and masks
	//namedWindow("FG Mask MOG 2");                    // FG Mask MOG 2 "" ^ as above
	//namedWindow("Thresholded");						 // Thresholded "" ^ as above
	//namedWindow("Object Detection", WINDOW_NORMAL);

	//-- Trackbars to set thresholds for hue values
	// createTrackbar("Hue min", "Object Detection", &lowHue, 255, on_low_hue_thresh_trackbar);
//	createTrackbar("Hue max", "Object Detection", &highHue, 255, on_high_hue_thresh_trackbar);


	//-- Trackbars to set thresholds for RGB values -- NOT CURRENTLY USED, SWITCHED TO HSV THRESHOLDING
	/*
	createTrackbar("Low R", "Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
	createTrackbar("High R", "Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
	createTrackbar("Low G", "Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
	createTrackbar("High G", "Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
	createTrackbar("Low B", "Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
	createTrackbar("High B", "Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
	*/

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
			|    |                                                       |    |   FEED 1   ON OFF            |  |
			|    |                                                       |    |   FEED 1   ON OFF            |  |
			|    |                                                       |    |   FEED 1   ON OFF            |  |
			|    |                                                       |    |   FEED 1   ON OFF            |  |
			|    |                                                       |    |   FEED 1   ON OFF            |  |
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

		2) LONG TERM USABILITY


			We should focus on the short term for now, but I will update this comment section with the plan before
			2/10/2017 - Molly

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
		*/


		//namedWindow("Master Window");
		//createTrackbar("Hue min", "Master Window", &lowHue, 255, on_low_hue_thresh_trackbar);
		//createTrackbar("Hue max", "Master Window", &highHue, 255, on_high_hue_thresh_trackbar);

		//int master_window_w = 550;
		//int master_window_h = 400;

		//resizeWindow("Master Window", master_window_w, master_window_h);

		////////////////////////////////////////////////////////////// -AZS

//void cvShowManyImages(char* title, int nArgs, ...) {

    // img - Used for getting the arguments 
    IplImage *img;

    // [[DispImage]] - the image in which input images are to be copied
    IplImage *DispImage;

    int size;
    int i;
    int m, n;
    int x, y;

    // w - Maximum number of images in a row 
    // h - Maximum number of images in a column 
    int w, h;

    // scale - How much we have to resize the image
    float scale;
    int max;

    // If the number of arguments is lesser than 0 or greater than 12
    // return without displaying 
    if (nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;

	}
    else if (nArgs > 12) {
        printf("Number of arguments too large....\n");
        return;

	}
    // Determine the size of the image, 
    // and the number of rows/cols 
    // from number of arguments 
    else if (nArgs == 1) {
        w = h = 1;
        size = 300;

	}
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 300;

	}
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 300;

	}
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 200;

	}
    else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 200;

	}
    else {
        w = 4; h = 3;
        size = 150;

	}
	    // Create a new 3 channel image
		[[DispImage]] = cvCreateImage(cvSize(100 + size*w, 60 + size*h), 8, 3);
		
		    // Used to get the arguments passed
		    va_list args;
		    va_start(args, nArgs);
		
		    // Loop for nArgs number of arguments
		    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {
		
        // Get the Pointer to the IplImage
        img = va_arg(args, IplImage*);

        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if (img == 0) {
            printf("Invalid arguments");
            cvReleaseImage(&DispImage);
            return;

			}

        // Find the width and height of the image
        x = img->width;
        y = img->height;

        // Find whether height or width is greater in order to resize the image
        max = (x > y) ? x : y;

        // Find the scaling factor to resize the image
        scale = (float)((float)max / size);

        // Used to Align the images
        if (i % w == 0 && m != 20) {
            m = 20;
            n += 20 + size;
			}

        // Set the image ROI to display the current image
        cvSetImageROI(DispImage, cvRect(m, n, (int)(x / scale), (int)(y / scale)));

        // Resize the input image and copy the it to the Single Big Image
        cvResize(img, DispImage);

        // Reset the ROI in order to display the next image
        cvResetImageROI(DispImage);
		}

	    // Create a new window, and show the Single Big Image
	    cvNamedWindow(title, 1);
	    cvShowImage(title, DispImage);
	
	    cvWaitKey();
	    cvDestroyWindow(title);
	
	    // End the number of arguments
	    va_end(args);
	
	    // Release the Image Memory
	    cvReleaseImage(&DispImage);
	
	}


//cv::Mat makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows) {
//
//	int N = vecMat.size();
//	nRows = nRows > N ? N : nRows;
//	int edgeThickness = 10;
//	int imagesPerRow = ceil(double(N) / nRows);
//	int resizeHeight = floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness;
//	int maxRowLength = 0;
//
//	std::vector<int> resizeWidth;
//	for (int i = 0; i < N;) {
//		int thisRowLen = 0;
//		for (int k = 0; k < imagesPerRow; k++) {
//			double aspectRatio = double(vecMat[i].cols) / vecMat[i].rows;
//			int temp = int(ceil(resizeHeight * aspectRatio));
//			resizeWidth.push_back(temp);
//			thisRowLen += temp;
//			if (++i == N) break;
//		}
//		if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
//			maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
//		}
//	}
//	int windowWidth = maxRowLength;
//	cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, Scalar(0, 0, 0));
//
//	for (int k = 0, i = 0; i < nRows; i++) {
//		int y = i * resizeHeight + (i + 1) * edgeThickness;
//		int x_end = edgeThickness;
//		for (int j = 0; j < imagesPerRow && k < N; k++, j++) {
//			int x = x_end;
//			cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
//			cv::Size s = canvasImage(roi).size();
//			
//			// change the number of channels to three
//			cv::Mat target_ROI(s, CV_8UC3);
//			if (vecMat[k].channels() != canvasImage.channels()) {
//				if (vecMat[k].channels() == 1) {
//					cv::cvtColor(vecMat[k], target_ROI, CV_GRAY2BGR);
//				}
//			}
//			cv::resize(target_ROI, target_ROI, s);
//			if (target_ROI.type() != canvasImage.type()) {
//				target_ROI.convertTo(target_ROI, canvasImage.type());
//			}
//			target_ROI.copyTo(canvasImage(roi));
//			x_end += resizeWidth[k] + edgeThickness;
//		}
//	}
//	return canvasImage;
//}

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



/*
int main(void) {

	cv::VideoCapture capVideo;
	cv::VideoCapture capVideo2;

	cv::Mat imgFrame;

	capVideo.open("768x576.avi");
	capVideo2.open("768x576.avi");

	if (!capVideo.isOpened()) {                                                 // if unable to open video file
		std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
		_getch();                    // it may be necessary to change or remove this line if not using Windows
		return(0);                                                              // and exit program
	}
	if (!capVideo2.isOpened()) {                                                 // if unable to open video file
		std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
		_getch();                    // it may be necessary to change or remove this line if not using Windows
		return(0);                                                              // and exit program
	}

	if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";
		_getch();
		return(0);
	}
	if (capVideo2.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";
		_getch();
		return(0);
	}


	char chCheckForEscKey = 0;

	while (true) {
	cv::Mat frame, f1, f2, f3, f4, merged_f, roi;

	//grab and retrieve each frames of the video sequentially

	frame = capVideo.read(imgFrame);
	capVideo2.read(imgFrame);



	// initialize each frame
	f1 = cv::Mat(cv::Size(320, 240), CV_8UC3);
	f2 = cv::Mat(cv::Size(320, 240), CV_8UC3);
	f3 = cv::Mat(cv::Size(320, 240), CV_8UC3);
	f4 = cv::Mat(cv::Size(320, 240), CV_8UC3);
	frame = cv::Mat(cv::Size(320, 240), CV_8UC3);
	roi = cv::Mat(cv::Size(320, 240), CV_8UC3);

	cv::resize(frame, f1, cv::Size(), 0.5, 0.5);
	cv::flip(f1, f1, 1);

	//copy the contents of the video for simplicity's sake
	f2 = f1.clone();
	f3 = f1.clone();
	f4 = f1.clone();
	//merge all frames together into one big frame
	merged_f = cv::Mat(cv::Size(640, 480), CV_8UC3);
	roi = cv::Mat(merged_f, cv::Rect(0, 0, 320, 240));
	f1.copyTo(roi);
	roi = cv::Mat(merged_f, cv::Rect(320, 0, 320, 240));
	f2.copyTo(roi);
	roi = cv::Mat(merged_f, cv::Rect(0, 240, 320, 240));
	f3.copyTo(roi);
	roi = cv::Mat(merged_f, cv::Rect(320, 240, 320, 240));
	f4.copyTo(roi);

	//disply the big frame
	cv::imshow("Video1", merged_f);

	//wait for 40 milliseconds
	int c = cvWaitKey(40);

	//exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27)
	if (27 == char(c)) break;
	}


	if (chCheckForEscKey != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
	cv::waitKey(0);                         // hold the windows open to allow the "end of video" message to show
	}
	// note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows

	return(0);
	}

	
	*/
	


	