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

#include <QDialog>
#include <QApplication>
#include <QMainWindow>
#include "cvimagewidget.h"

// Variable declarations: Move these to another .cpp file later!!! (NOT .h, you will get linker errors)
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
Ptr<BackgroundSubtractor> pKNN; //MOG2 Background subtractor
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
int currentCarCount;

void processVideo(VideoCapture* pCap);
int testGUI(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	testGUI(argc, argv);

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

int testGUI(int argc, char* argv[]) {
	QApplication app(argc, argv);
	QMainWindow window;

	// Create the image widget
	CVImageWidget* imageWidget = new CVImageWidget();
	window.setCentralWidget(imageWidget);

	// Load an image
	cv::Mat image = cv::imread("somepicture.jpg", true);
	imageWidget->showImage(image);

	window.show();

	return app.exec();
}