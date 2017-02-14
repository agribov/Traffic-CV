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

#include "globals.h"
#include "videoHelper.h"
#include "vehicle.h"
#include "vehicleTracker.h"

void processVideo(VideoCapture* pCap) {

	//read input data. ESC or 'q' for quitting
	keyboard = 0;
	VehicleTracker tracker;

	Mat frame, outputFrame;

	while (keyboard != 'q' && keyboard != 27) {

		//read the current frame
		if (!(*pCap).read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		tracker.update(frame);
		//tracker.cumulativeCarCount(currentCarCount);
		outputFrame = tracker.getTrackedFrame();
		addFrameNumber(outputFrame, pCap);
		addCarCount(outputFrame, pCap);

		imshow("Video Capture", outputFrame);
		imshow("Debug 1", tracker.getDilated());
		imshow("Debug 2", tracker.getEroded());

		//get the input from the keyboard
		keyboard = (char)waitKey(30);
	}
}

VideoCapture* initializeVideo(char* videoFilename) {
	//create the capture object
	VideoCapture* capture = new VideoCapture(videoFilename);
	if (!capture->isOpened()) {
		//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}

	return capture;
}

void releaseVideo(VideoCapture* pCap) {
	(*pCap).release();
}

void addFrameNumber(Mat &frame, VideoCapture *pCap) {
	//get the frame number and write it on the current frame
	stringstream ss;
	rectangle(frame, cv::Point(10, 2), cv::Point(100, 45),
		cv::Scalar(255, 255, 255), -1);
	ss << (*pCap).get(CAP_PROP_POS_FRAMES);
	string frameNumberString = ss.str();
	putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
		FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
}

void addCarCount(Mat &frame, VideoCapture *pCap) {
	string result;          //contains result of converting int --> string
	ostringstream convert;   // stream used for the conversion
	convert << currentCarCount;      // insert the textual representation of 'currentCarCount' in the characters in the stream
	result = convert.str(); // set 'result' to the contents of the stream. result is now "count"
	result += " cars";
	putText(frame, result , cv::Point(15, 40), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
}

// NOT USED, here as a historic monument
/*
void OLDprocessVideo(VideoCapture* pCap) {

	//read input data. ESC or 'q' for quitting
	keyboard = 0;

	Mat frame, threshFrame, adaptiveFrame; //current frame
	Mat fgMaskKNN;

	while (keyboard != 'q' && keyboard != 27) {

		//read the current frame
		if (!(*pCap).read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		colorThreshold(frame, &threshFrame);
		//Test adaptive thresholding
		//cvtColor(frame, adaptiveFrame, COLOR_BGR2GRAY);	//BGR to gray color conversion
		//adaptiveThreshold(adaptiveFrame, adaptiveFrame, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);

		for (int i = 0; i < erosionVal; i++)
		{
			erodeFrame(threshFrame, &threshFrame);
			//erodeFrame(adaptiveFrame, &adaptiveFrame);
		}

		for (int i = 0; i < dilationVal; i++)
		{
			dilateFrame(threshFrame, &threshFrame);
			//dilateFrame(adaptiveFrame, &adaptiveFrame);
		}

		//update the background model
		pMOG2->apply(threshFrame, fgMaskMOG2);
		pKNN->apply(threshFrame, fgMaskKNN);

		//get the frame number and write it on the current frame
		stringstream ss;
		rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
			cv::Scalar(255, 255, 255), -1);
		ss << (*pCap).get(CAP_PROP_POS_FRAMES);
		string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
			FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

		//Run Thresholding
		//thresholding(frame, &threshFrame);

		//show current frame and masks
		imshow("Video Capture", frame);
		imshow("FG Mask KNN", fgMaskKNN);
		//imshow("FG Mask MOG 2", fgMaskMOG2);
		imshow("Thresholded", (threshFrame));
		//imshow("Adaptive Thresholding", adaptiveFrame);

		//get the input from the keyboard
		keyboard = (char)waitKey(30);
	}
	//delete capture object
	releaseVideo(pCap);
}
*/