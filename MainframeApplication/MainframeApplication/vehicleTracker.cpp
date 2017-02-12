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

//PUBLIC FUNCTIONS:

VehicleTracker::VehicleTracker() {
	// Initialize the class. 
}

vector<Point> VehicleTracker::getVehiclePositions() {
	// From list of vehicles in self.vehicles:
	// Get location of every vehicle, add to a vector<Point>
	// Return that vector

	vector<Point> PLACEHOLDER;
	return PLACEHOLDER;
}

void VehicleTracker::update(Mat currentFrame) {
	size_t numContours;
	double area;
	Moments blobMoment;
	vector<vector<Point>>::iterator firstContour;
	int i;
	Point2f center;
	vector<Point2f> centroids;

	// This function is called when a new frame is available. 
	// Its goal is to process the frame, and update the list of vehicles.
	// List of vehicles is in self.vehicles. Process outlined in comments

	// Step 1: Save current frame into self.frame
	frame = currentFrame;

	// Step 2a: Take high threshold (isolate hot objects)
	// Step 2b: Take low threshold (isolate cold objects) (**SPIF)
	//		**SPIF = Solutions for Problems In the Future. Do not implement a SPIF unless we find we really need it.
	highThFrame = threshold(frame, 5, 5);	

	// Step 3: Use erode function (built into this class) to eliminate noise
	// Step 3b: Other noise-eliminating functions? (**SPIF)
	// Step 3c: Background subtraction? (**SPIF)
	erodedFrame = erode(highThFrame);
	
	// Step 4: Dilate the eroded image (to make cars very clear)
	// Step 4b: Other clarity functions? (**SPIF)
	dilatedFrame = dilate(erodedFrame);
	
	// Step 5: Find contours of filtered image, to be stored in self.vehicleContours
	findContours(dilatedFrame, vehicleContours);
	
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
			vehicleContours.erase(firstContour + i);
			i--;
			numContours--;
		}
		// Step 7: Find centroids of contours that have not been eliminated
		else {
			center = Point2f(blobMoment.m10 / area, blobMoment.m01 / area);
			centroids.push_back(center);
		}
	}

	// TODO: ***
	// Step 8: Iterate through self.vehicles. Compare old vehicle locations to current centroids.
	//		- If a centroid is ahead of old vehicle location, update that vehicle with new location.
	//		- If a vehicle was near trailing edge, and is now gone, mark it as gone or delete it (we need to pick)
	//		- If a centroid is near leading edge, create new vehicle in the list
	//		- If a vehicle in the middle of the intersection has disappeared, 'mark it as suspicious' (TBD, SPIF)

}

void VehicleTracker::drawBoxes(Mat &frame) {
	// Use function self.getVehiclePositions() to get the vehicle positions, and overlay boxes on top of the current thermal frame
}

//PRIVATE FUNCTIONS:

Mat VehicleTracker::threshold(Mat inputFrame, int lowH, int highH) {
	//Returns thresholded version of inputFrame
	Mat hsvFrame;
	Mat temp;
	// Convert frame to HSV space, to threshold color
	cvtColor(inputFrame, hsvFrame, COLOR_BGR2HSV);

	inRange(hsvFrame, Scalar(lowH, 100, 100), Scalar(highH, 255, 255), temp);
	return temp;
}
Mat VehicleTracker::erode(Mat inputFrame) {
	//Returns eroded version of inputFrame
	return inputFrame;
}
Mat VehicleTracker::dilate(Mat inputFrame) {
	//Returns dilated version of inputFrame
	return inputFrame;
}
Mat VehicleTracker::bgSubtractionMOG2(Mat inputFrame) {
	//Returns bgSubtracted version of inputFrame, using MOG2 method
	return inputFrame;
}
void VehicleTracker::findContours(Mat inputFrame, vector<vector<Point>> &outputContours) {
	// Find the contours of the input frame and store them in self.vehicleContours
	return;
}
void VehicleTracker::updateVehicleList() {
	return;
}