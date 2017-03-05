/********************************************************************************/
/*                                                                              */
/* Program: Main Thermal Image Processor                                        */
/*                                                                              */
/* File: vehicle.h		                                                        */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#ifndef _vehicle
#define _vehicle

#include "globals.h"

class Vehicle {
private:
	cv::Point position;	// Current position of vehicle
	float velocity;	// Velocity of vehicle
	int totalTime; // Holds how long vehicle has been in video.
	int waitingTime; // Amount of time vehicle has been sitting still (IGNORE FOR NOW)
public:
	//VehicleTracker(); // DEFINE ME
	Vehicle(cv::Point2f pos) {
		position = (cv::Point)pos;
		velocity = 0;
	}
	void update(cv::Point pos); // Updates all information about vehicle, given new location.
	cv::Point getPosition() { return position; }
};

#endif