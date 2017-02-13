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

// Variable declarations: Move these to another .cpp file later!!! (NOT .h, you will get linker errors)
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor

Mat frame, threshFrame, frame_duplicate; //current frame

void processVideo(VideoCapture* pCap);

int main(int argc, char* argv[]) {
	const string sampleStreamAddress = "http://66.193.157.18/mjpg/video.mjpg";
	VideoCapture* pCap;
	char* sampleVideo = "thermalSample.mp4";

	initializeGUI(); // Defined in GUI.cpp

	//create Background Subtractor objects
	pMOG2 = createBackgroundSubtractorMOG2(500, 16, true); //MOG2 approach

	//initializeVideo(sampleStreamAddress.c_str());

	pCap = initializeVideo(sampleVideo); // Defined in videoHelper.cpp

	processVideo(pCap);

	//destroy GUI windows
	destroyAllWindows();
	return EXIT_SUCCESS;
}

/************************** AZS Start Subtraction Method *************************/
void processVideo(VideoCapture* pCap) {
	
	//read input data. ESC or 'q' for quitting
	keyboard = 0;

	//Mat frame, threshFrame; //current frame

	while (keyboard != 'q' && keyboard != 27) {

		//read the current frame
		if (!(*pCap).read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		colorThreshold(frame, &threshFrame);

		//update the background model
		pMOG2->apply(threshFrame, fgMaskMOG2);

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

		std::vector<cv::Mat> testing;

	//	testing.push_back(threshFrame);
	//	testing.push_back(fgMaskMOG2);
	//	testing.push_back(frame);

		cvtColor(frame, frame_duplicate, COLOR_BGR2HSV);

		//show current frame and masks
		//imshow("Video Capture", frame);	//-AZS
		//imshow("FG Mask MOG 2", fgMaskMOG2);
		//imshow("Thresholded", (threshFrame));
	//	imshow("Master Window", frame); 
		// frame should always be shown in the master window

		//frame_duplicate = frame.clone();	//-AZS

		//testing.push_back(threshFrame);
		//testing.push_back(frame);
		testing.push_back(fgMaskMOG2);
		//testing.push_back(fgMaskMOG2);
		//testing.push_back(fgMaskMOG2);
		//testing.push_back(fgMaskMOG2);
		testing.push_back(frame_duplicate);

		imshow("Master Window", makeCanvas(testing, 400, 2));

		//get the input from the keyboard
		keyboard = (char)waitKey(30);
	}
	//delete capture object
	releaseVideo(pCap);
}