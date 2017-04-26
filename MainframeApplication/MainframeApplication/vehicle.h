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
#include "utilities.h"

class Vehicle {
private:
	cv::Point position;	// Current position of vehicle
	cv::Point startPos;
	float velocity;	// Velocity of vehicle
	int totalTime; // Holds how long vehicle has been in video.
	int waitingTime; // Amount of time vehicle has been sitting still (IGNORE FOR NOW)
	int frameCount;
	//const int velScale = 10;
public:
	//VehicleTracker(); // DEFINE ME
	Vehicle(cv::Point2f pos, int fc) {
		position = (cv::Point)pos;
		startPos = position;
		velocity = 0;
		frameCount = fc;
		totalTime = 1;
	}
	void update(cv::Point pos, int fc); // Updates all information about vehicle, given new location.
	cv::Point getPosition() { return position; }
	int getFrameNum() { return frameCount; }
	int getVelocity() { return getDist(startPos, position) / totalTime; }
};

#endif