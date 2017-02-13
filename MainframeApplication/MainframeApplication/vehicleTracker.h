/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: vehicleTracker.h                                                       */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#ifndef _vehicleTracker
#define _vehicleTracker

#include "globals.h"
#include "vehicle.h"

class VehicleTracker {
private:
	// Private variables
	// NOTE: Most variables are updated during the update(Mat frame) function. 
	// Please see it's definition in vehicleTracker.cpp for more info
	vector<Vehicle> vehicles;
	Mat frame; // Stores current frame
	Mat lowThFrame; // UNUSED CURRENTLY
	Mat highThFrame; // Stores image thresholded for hot-spots
	Mat foregroundFrame; // Stores frame after background subtraction
	Mat erodedFrame; // Stores frame after erosion
	Mat dilatedFrame; // Stores frame after dilation
	vector < vector<Point>> vehicleContours; // stores the contours of the vehicles in the current frame
	Mat outputFrame; //Original frame, but with boxes overlayed on vehicles.
	
	int numCarsCurrent; // Number of cars currently in the intersection
	int numCarsTotal; //Number of cars that have gone through the intersection in total
	const int MAX_NUMBER_VEHICLES = 10; // Constant value: If number is more than this, algorithm will assume there is noise.
	const int MIN_VEHICLE_AREA = 5 * 5; // Unit is pixels
	const int MAX_VEHICLE_AREA = 200 * 200; // Unit is pixels

	// Private functions
	// NOTE: These are called BY the update() function. They are "helper functions". Innaccesible, except by members of this class
	Mat thresholdFrame(Mat inputFrame, int lowH, int highH);
	Mat erodeFrame(Mat inputFrame, int sliderVal);
	Mat dilateFrame(Mat inputFrame, int sliderVal);
	Mat bgSubtractionMOG2(Mat inputFrame);
	void findVehicleContours(Mat inputFrame, vector<vector<Point>> &outputContours);
	void updateVehicleList();

public:
	VehicleTracker(); // This is the initializer for the VehicleTracker object
	vector<Point> getVehiclePositions(); // This function returns a vector of the current vehicle centroids
	void update(Mat currentFrame); // This function is called to update the algorithm when a new frame is available
	void drawBoxes(Mat &frame); // This function overlays boxes over the current location of the cars.
};

#endif