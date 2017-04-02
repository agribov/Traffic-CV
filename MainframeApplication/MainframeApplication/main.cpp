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
#include "MainWindow.h"

using namespace std;
using namespace cv;

int currentCarCount;

int main(int argc, char* argv[]) {
	int x = __cplusplus;
	printf("%d", x);
	// Go to MainWindow.cpp for all of the starter code to run the application:
	//		- MainWindow::onStart() contains the code to set up the app.
	//		- MainWindow::timerEvent() contains all of the code that runs tracking
	//		  and displays the results
	//		- These two functions are original code

	// MainWindow.h contains the class definition which contains the declarations of
	// all objects and variables used by the above functions

	// VehicleTracker.h defines the class which actively does the tracking (called by 
	// the above functions). VehicleTracker.cpp contains the class function definitions.
	// VehicleTracker references the Vehicle class (.cpp and .h). 
	//		- All four of these files are entirely original work.

	// CQtOpenCVViewerGl(.cpp and .h) contains the code to create a widget that displays
	// a cv::Mat object. These were not written by us (see files for references).

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
	
	return EXIT_SUCCESS;
}
