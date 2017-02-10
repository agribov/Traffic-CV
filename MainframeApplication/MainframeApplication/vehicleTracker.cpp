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
	// This function is called when a new frame is available. 
	// Its goal is to process the frame, and update the list of vehicles.
	// List of vehicles is in self.vehicles. Process outlined in comments

	// Step 1: Save current frame into self.frame

	// Step 2a: Take high threshold (isolate hot objects)
	// Step 2b: Take low threshold (isolate cold objects) (**SPIF)
	//		**SPIF = Solutions for Problems In the Future. Do not implement a SPIF unless we find we really need it.


	// Step 3: Use erode function (built into this class) to eliminate noise
	// Step 3b: Other noise-eliminating functions? (**SPIF)
	// Step 3c: Background subtraction? (**SPIF)
	
	// Step 4: Dilate the eroded image (to make cars very clear)
	// Step 4b: Other clarity functions? (**SPIF)
	
	// Step 5: Find contours of filtered image, to be stored in self.vehicleContours
	
	// Step 6: Check number and dimensions of vehicles:
	//		- Small and large contours are probably erroneous
	//		- Too many blobs is probably erroneus

	// Step 7: Find centroids of contours that have not been eliminated

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

Mat VehicleTracker::threshold(Mat inputFrame) {
	//Returns thresholded version of inputFrame
	return inputFrame;
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
void VehicleTracker::findContours(Mat inputFrame) {
	// Find the contours of the input frame and store them in self.vehicleContours
	return;
}
void VehicleTracker::updateVehicleList() {
	return;
}