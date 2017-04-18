/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: vehicleTracker.cpp                                                     */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include "globals.h"
#include "vehicleTracker.h"
#include "vehicle.h"

#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <cstdio>
#include <iostream>

using namespace std;
using namespace cv;

//PUBLIC FUNCTIONS:
VehicleTracker::VehicleTracker() {
	// Initialize the class. 
	lowHue = 0;
	highHue = 50;
	erosionVal = 0;
	dilationVal = 0;
}

VehicleTracker::VehicleTracker(int lHue = 0, int hHue = 50, int er = 0, int dil = 0) {
	// Initialize the class. 
	lowHue = lHue;
	highHue = hHue;
	erosionVal = er;
	dilationVal = dil;
}

vector<Point> VehicleTracker::getVehiclePositions() {
	// From list of vehicles in self.vehicles:
	// Get location of every vehicle, add to a vector<Point>
	// Return that vector
	vector<Point> positions;
	//printf("%d\n", vehicles.size());
	for (int i = 0; i < vehicles.size(); i++)
		positions.push_back(vehicles[i].getPosition());

	return positions;
}

void onMouse(int event, int x, int y, int flags, void* userData)
{
	if (event != EVENT_LBUTTONDOWN)
		return;
	//Save coordinates of left button click
	if (event == EVENT_LBUTTONDOWN)
	{
		static vector<Point> vCoordinates;
		static vector<vector<Point>> vvCoordinates;

		//Stores coordinates of every left click in a vector
		vCoordinates.push_back(Point(x, y));
		//The coordinates of every four left clicks are stored in a vector element
		if (vCoordinates.size() % 4 == 0 )
			vvCoordinates.push_back(vCoordinates);

		//Test code that prints vector coordinates
		cout << "Left Button of mouse was clicked at position(" << x << "," << y << ")" << endl;
		cout << "Vector coordinates" << vCoordinates << endl;
		
		//Test code that prints first three elements of the vector of vectors
		if (vvCoordinates.size() == 1)
			cout << "Vector of vector coordinates" << vvCoordinates[0] << endl;

		if (vvCoordinates.size() == 2)
			cout << "Vector of vector coordinates" << vvCoordinates[1] << endl;

		if (vvCoordinates.size() == 3)
			cout << "Vector of vector coordinates" << vvCoordinates[2] << endl;
	}
}


void VehicleTracker::update(Mat currentFrame) {
	size_t numContours;
	double area;
	Moments blobMoment;
	vector<vector<Point>>::iterator firstContour;
	int i;
	Point2f center;
	vector<Point2f> centroids;
	static int frameNumber = 0;

	// This function is called when a new frame is available. 
	// Its goal is to process the frame, and update the list of vehicles.
	// List of vehicles is in self.vehicles. Process outlined in comments

	// Step 1: Save current frame into self.frame
	frame = currentFrame;

	// Step 2a: Take high threshold (isolate hot objects)
	// Step 2b: Take low threshold (isolate cold objects) (**SPIF)
	//		**SPIF = Solutions for Problems In the Future. Do not implement a SPIF unless we find we really need it.
	highThFrame = thresholdFrame(frame, lowHue, highHue);	

	// Step 3: Use erode function (built into this class) to eliminate noise
	// Step 3b: Other noise-eliminating functions? (**SPIF)
	// Step 3c: Background subtraction? (**SPIF)
	erodedFrame = erodeFrame(highThFrame, erosionVal);
	//printf("%d\n", highHue);
	
	// Step 4: Dilate the eroded image (to make cars very clear)
	// Step 4b: Other clarity functions? (**SPIF)
	dilatedFrame = dilateFrame(erodedFrame, dilationVal);
	
	// Step 5: Find contours of filtered image, to be stored in self.vehicleContours
	findVehicleContours(dilatedFrame, vehicleContours);
	
	// Step 6: Check number and dimensions of vehicles:
	//		- Small and large contours are probably erroneous
	//		- Too many blobs is probably erroneus

	numContours = (size_t)vehicleContours.size();
	while (numContours > MAX_NUMBER_VEHICLES) {
		//ERROR: Too many objects
		//Insert additional filtering here
		break; //Remove this when above filtering is implemented
	}

	firstContour = vehicleContours.begin();
	for (i = 0; i < numContours; i++) {
		blobMoment = moments((Mat)vehicleContours[i]);
		area = blobMoment.m00;
		if (area < MIN_VEHICLE_AREA) {
			//vehicleContours.erase(firstContour + i);
			//i--;
			//numContours--;
		}
		// Step 7: Find centroids of contours that have not been eliminated
		else {
			center = Point2f(blobMoment.m10 / area, blobMoment.m01 / area);
			centroids.push_back(center);
		}
	}
	//***For Step 7 look into using meanshift() and camshift() to find the centroid of the blobs. -AZS ****

	// TODO: ***
	// Step 8: Iterate through self.vehicles. Compare old vehicle locations to current centroids.
	//		- If a centroid is ahead of old vehicle location, update that vehicle with new location.
	//		- If a vehicle was near trailing edge, and is now gone, mark it as gone or delete it (we need to pick)
	//		- If a centroid is near leading edge, create new vehicle in the list
	//		- If a vehicle in the middle of the intersection has disappeared, 'mark it as suspicious' (TBD, SPIF)

	// TEMP SOLUTION: Replace vehicles with a vector of new vehicles everytime.
	vector<Vehicle> tempList;
	//printf("%d\n", centroids.size());
	for (i = 0; i < centroids.size(); i++) {
		Vehicle x(centroids[i]);
		tempList.push_back(x);
	}
	vehicles = tempList;
	currentCarCount = 0;
	frame.copyTo(outputFrame);

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", currentFrame);
	setMouseCallback("Display window", onMouse, 0);

	drawBoxes(outputFrame);
	

//////*QUICK AND DIRTY CODE*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/*Controls what frame comes up
	frameNumber++;
	if (frameNumber == 50 || frameNumber == 200) {

		line(currentFrame, Point(0, 50), Point(200, 50), Scalar(255), 2, 8, 0);
		imshow("image", currentFrame);
	}*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VehicleTracker::drawBoxes(Mat &frame) {
	// Use function self.getVehiclePositions() to get the vehicle positions, and overlay boxes on top of the current thermal frame
	// drawBoxes may be unnecessary as meanshift and camshift draw boxes. -AZS
	vector<Point> center;
	Rect rect;
	const Scalar GREEN = Scalar(0, 255, 0);  //Assuming BGR color space.

	for (int i = 0; i < getVehiclePositions().size(); i++)
	{
		Point temp;
		temp.x = getVehiclePositions()[i].x;	//find more efficient method
		temp.y = getVehiclePositions()[i].y;
		rectangle(frame, Point(temp.x + 20, temp.y + 20), Point(temp.x - 20, temp.y - 20), GREEN, 3);	//Rectangle vertices are arbitrarily set.
		currentCarCount++;
	}
	//printf("%d\n", getVehiclePositions().size());

}
//PRIVATE FUNCTIONS:

Mat VehicleTracker::thresholdFrame(Mat inputFrame, int lowH, int highH) {
	//Returns thresholded version of inputFrame
	Mat hsvFrame;
	Mat temp;
	// Convert frame to HSV space, to threshold color
	cvtColor(inputFrame, hsvFrame, COLOR_BGR2HSV);

	inRange(hsvFrame, Scalar(lowH, 100, 100), Scalar(highH, 255, 255), temp);
	return temp;
}

Mat VehicleTracker::erodeFrame(Mat inputFrame, int sliderVal) {
	//Returns eroded version of inputFrame
	int eV = sliderVal;
	Mat outputFrame;
	//Mat eElement = getStructuringElement(MORPH_RECT, Size(3, 3)); 
	Mat erodedElement = getStructuringElement(MORPH_RECT, Size(2 * eV + 1, 2 * eV + 1), Point(eV, eV));
	erode(inputFrame, outputFrame, erodedElement);
	return outputFrame;
}

Mat VehicleTracker::dilateFrame(Mat inputFrame, int sliderVal) {
	//Returns dilated version of inputFrame
	int dV = sliderVal;
	Mat outputFrame;
	Mat dilatedElement = getStructuringElement(MORPH_RECT, Size(2 * dV + 1, 2 * dV + 1), Point(dV, dV));
	//perform dilation
	dilate(inputFrame, outputFrame, dilatedElement);
	return outputFrame;
}

Mat VehicleTracker::bgSubtractionMOG2(Mat inputFrame) {
	//Returns bgSubtracted version of inputFrame, using MOG2 method
	return inputFrame;
}

void VehicleTracker::findVehicleContours(Mat inputFrame, vector<vector<Point>> &outputContours) {
	// Find the contours of the input frame and store them in self.vehicleContours
	//vector<Vec4i> heirarchy;
	findContours(inputFrame, vehicleContours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	return;
}

void VehicleTracker::updateVehicleList() {
	return;
}