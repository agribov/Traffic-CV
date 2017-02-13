/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: main.cpp                                                               */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include "globals.h"
#include "videoHelper.h"
#include "GUI.h"
#include "threshold.h"
#include "vehicle.h"
#include "vehicleTracker.h"

// Variable declarations: Move these to another .cpp file later!!! (NOT .h, you will get linker errors)
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
Ptr<BackgroundSubtractor> pKNN; //MOG2 Background subtractor
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor

void processVideo(VideoCapture* pCap);
void OLDprocessVideo(VideoCapture* pCap);

int main(int argc, char* argv[]) {
	const string sampleStreamAddress = "http://66.193.157.18/mjpg/video.mjpg";

	VideoCapture* pCap;

	char* sampleVideo = "thermalSample.mp4";
	pCap = initializeVideo(sampleVideo); // Defined in videoHelper.cpp

	initializeGUI(); // Defined in GUI.cpp

	//create Background Subtractor objects
	pKNN = createBackgroundSubtractorKNN(500,16,true);
	pMOG2 = createBackgroundSubtractorMOG2(500, 16, true); //MOG2 approach

	processVideo(pCap);

	//destroy GUI windows
	destroyAllWindows();
	return EXIT_SUCCESS;
}

void processVideo(VideoCapture* pCap) {

	//read input data. ESC or 'q' for quitting
	keyboard = 0;
	VehicleTracker tracker;

	Mat frame; //current frame
	Mat output;

	while (keyboard != 'q' && keyboard != 27) {

		//read the current frame
		if (!(*pCap).read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}
		tracker.update(frame);
		output = tracker.getTrackedFrame();
		imshow("Video Capture", output);
		imshow("Debug 1", tracker.getDilated());
		imshow("Debug 2", tracker.getEroded());

		//get the input from the keyboard
		keyboard = (char)waitKey(30);
	}
}

// NOT USED, here as a historic monument
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