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
#include "utilities.h"

#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <cstdio>
#include <iostream>

using namespace std;
using namespace cv;

Ptr<BackgroundSubtractorMOG2> pMOG2 = createBackgroundSubtractorMOG2(); //MOG2 background subtractor

const int MAX_FRAME_DISTANCE = 50;
const int START_ZONE_DIST = 30;
const int FRAME_COUNT_TIMEOUT = 10;

//PUBLIC FUNCTIONS:
VehicleTracker::VehicleTracker() {
	// Initialize the class. 
	lowHue = 0;
	highHue = 50;
	erosionVal = 0;
	dilationVal = 0;
	frameCount = 0;
	//For VL Camera
	erosionValVL = 0;
	dilationValVL = 0;
	//End VL Camera
}

VehicleTracker::VehicleTracker(int lHue = 0, int hHue = 50, int er = 0, int dil = 0, int erVL = 0, int dilVL = 0) {
	// Initialize the class. 
	Point temp;
	vector<vector<Point>> bounds;
	frameCount = 0;

	lowHue = lHue;
	highHue = hHue;
	erosionVal = er;
	dilationVal = dil;
	//For VL Camera
	erosionValVL = er;
	dilationValVL = dil;

	temp.x = 0;
	temp.y = 150;
	inboundBorder.push_back(temp);
	temp.x = 200;
	temp.y = 400;
	inboundBorder.push_back(temp);
	temp.x = 500;
	temp.y = 250;
	inboundBorder.push_back(temp);
	temp.x = 0;
	temp.y = 30;
	inboundBorder.push_back(temp);
	
	bounds.push_back(inboundBorder);
	updateLaneBounds(0, 1, 15, bounds);
	//laneBounds.push_back(inboundBorder);
	borders.push_back(inboundBorder);
} 

vector<Point> VehicleTracker::getVehiclePositions() {
	// From list of vehicles in self.vehicles:
	// Get location of every vehicle, add to a vector<Point>
	// Return that vector
	vector<Point> positions;
	//printf("%d\n", vehicles.size());
	for (int i = 0; i < vehicles.size(); i++)
		positions.push_back(vehicles[0][i].getPosition());

	return positions;
}


void VehicleTracker::update(Mat currentFrame) {
	size_t numContours;
	double area;
	Moments blobMoment;
	vector<vector<Point>>::iterator firstContour;
	int i, j, k;
	Point2f center;
	vector<Point2f> centroids;
	static int frameNumber = 0;

	// Increment frame counter
	frameCount++;

	// This function is called when a new frame is available. 
	// Its goal is to process the frame, and update the list of vehicles.
	// List of vehicles is in self.vehicles. Process outlined in comments

	// Step 1: Save current frame into self.frame
	frame = currentFrame;

	// Step 2a: Take high threshold (isolate hot objects)
	// Step 2b: Take low threshold (isolate cold objects) (**SPIF)
	//		**SPIF = Solutions for Problems In the Future. Do not implement a SPIF unless we find we really need it.
	highThFrame = thresholdFrame(frame, lowHue, highHue);

	//For testing background subtraction
	//imshow("No Subtraction", frame);
	//highThFrame = bgSubtractionMOG2(frame);
	//imshow("MOG2", highThFrame);
	//erodedFrame = erodeFrame(highThFrame, erosionValVL);


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

	vector<vector<Point>> sortedBlobs;
	sortedBlobs.resize(numLanes);
	vector<Point> blobList;
	frame.copyTo(outputFrame);

	// Sort the centroids into the container for the lane they are in.
	for (i = 0; i < centroids.size(); i++) {
		for (j = 0; j < numLanes; j++)
			if (pointPolygonTest(laneBounds[j], centroids[i], false) >= 0)
				sortedBlobs[j].push_back(centroids[i]);

	}
	
	double dist;
	for (i = 0; i < numLanes; i++) {
		size_t numVehicles = (size_t)vehicles[i].size();

		// Destroy vehicles that have not been updated in a while
		for (k = 0; k < numVehicles; k++) {
			if (vehicles[i][k].getFrameNum() < frameCount - FRAME_COUNT_TIMEOUT) {
				vehicles[i].erase(vehicles[i].begin() + k--);
				numVehicles--;
			}
		}

		drawPoints(outputFrame, sortedBlobs[i]);
		
		// If they already exist, continue. Else make a new vehicle		
		for (j = 0; j < sortedBlobs[i].size(); j++) {
			bool found = false;
			
			// Try to match the centroid to an existing vehicle
			for (k = 0; k < numVehicles; k++) {
				dist = getDist(vehicles[i][k].getPosition(), sortedBlobs[i][j]);
				
				// If current vehicle is near current frame, and vehicle has not been updated yet, update
				if (dist <= MAX_FRAME_DISTANCE && vehicles[i][k].getFrameNum() < frameCount) {
					vehicles[i][k].update(sortedBlobs[i][j], frameCount);
					found = true;
					//printf("Updated Vehicle %d, in lane %d.\n", k, i);
					break;
				}
			}
			
			// If centroid has not been yet matched to a vehicle, then check if it's near the lane start
			if (!found) {
				// Distance function defined in videohelper.cpp for now
				dist = getDistToLine(laneBounds[i][1], laneBounds[i][2], sortedBlobs[i][j]);
				//printf("Distance to vehicle is: %lf.\n", dist);
				if (dist < START_ZONE_DIST) {
					// It's a new vehicle: Create an object and add it to the list
					Vehicle x(sortedBlobs[i][j], frameCount);
					vehicles[i].push_back(x);
					found = true;
					//printf("Created Vehicle, in lane %d.\n", i);
					//printf("Distance to vehicle is: %d.\n", dist);
				}

			}
			
		}
		
		// If they are near the beginning of the lane, and don't exist, make a new vehicle.
	}
	
	/*
	//printf("%d\n", centroids.size());
	for (i = 0; i < centroids.size(); i++) {
		Vehicle x(centroids[i]);
		tempList.push_back(x);
	}
	vehicles[1] = tempList;

	*/
	currentCarCount = 0;
	drawBoxes(outputFrame);

}
//For Visible Light camera
void VehicleTracker::updatevl(Mat currentFrameVL) {
	size_t numContours;
	double area;
	Moments blobMoment;
	vector<vector<Point>>::iterator firstContour;
	int i;
	Point2f center;
	vector<Point2f> centroids;



	//cv::RotatedRect camBox;

	//float hranges[] = { 0,180 };
	//const float* phranges = hranges;

	//cv::cvtColor(currentFrameVL, hsvFrameVL, CV_BGR2HSV);

	//cv::inRange(hsvFrameVL, cv::Scalar(0, SMin, MIN(VMin, VMax)),
	//	cv::Scalar(180, 256, MAX(VMin, VMax)), mask);
	//int ch[] = { 0, 0 };
	//hue.create(hsv.size(), hsv.depth());
	//cv::mixChannels(&hsv, 1, &hue, 1, ch, 1);

	///Move
	//Step 1: Save current frame to liveFrame.
	frameVL = currentFrameVL;
	//Step 2: Perform background subtraction.

	//For testing background subtraction
	//imshow("No Subtraction", frameVL);

	fgMaskMOG2 = bgSubtractionMOG2(frameVL);
	//For testing background subtraction
	//imshow("MOG2", fgMaskMOG2);

	//Step 2: Perform thresholding.
	//highThFrameVL = thresholdFrame(vlframe, lowHue, highHue);
	//Step 3: Perform errosion.
	erodedFrameVL = erodeFrame(fgMaskMOG2, erosionValVL);
	//Step 4: Perform dilation.
	dilatedFrameVL = dilateFrame(erodedFrameVL, dilationValVL);

	findVehicleContoursVL(dilatedFrameVL, vehicleContoursVL);

	numContours = (size_t)vehicleContoursVL.size();
	while (numContours > MAX_NUMBER_VEHICLES) {
		//ERROR: Too many objects
		//Insert additional filtering here
		break; //Remove this when above filtering is implemented
	}

	firstContour = vehicleContoursVL.begin();
	for (i = 0; i < numContours; i++) {
		blobMoment = moments((Mat)vehicleContoursVL[i]);
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
	// TEMP SOLUTION: Replace vehicles with a vector of new vehicles everytime.
	vector<Vehicle> tempList;
	//printf("%d\n", centroids.size());
	for (i = 0; i < centroids.size(); i++) {
		//Vehicle x(centroids[i]);
		//tempList.push_back(x);
	}
	//vehicles = tempList;
	currentCarCount = 0;

	frameVL.copyTo(outputFrameVL);
	//imshow("MOG2", frameVL);

	drawBoxes(outputFrameVL);
	//imshow("No Subtraction", outputFrame);

//////*QUICK AND DIRTY CODE*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/*Controls what frame comes up
	frameNumber++;
	if (frameNumber == 50 || frameNumber == 200) {

		line(currentFrame, Point(0, 50), Point(200, 50), Scalar(255), 2, 8, 0);
		imshow("image", currentFrame);
	}*/

	//Step 5: Find contours of blobs.
	//findVehicleContoursVL(vldilatedFrame, vlvehicleContours);
	////Step 6: Determine number and dimensions of blobs.
	//vlnumContours = (size_t)vlvehicleContours.size();
	//while (vlnumContours > MAX_NUMBER_VEHICLES) {
	//	//ERROR: Too many objects
	//	//Insert additional filtering here
	//	break; //Remove this when above filtering is implemented
	//}
	////Step 7: Determine centroid of blobs.
	//vlfirstContour = vlvehicleContours.begin();
	//for (i = 0; i < vlnumContours; i++) {
	//	vlblobMoment = moments((Mat)vlvehicleContours[i]);
	//	vlarea = vlblobMoment.m00;
	//	if (vlarea < MIN_VEHICLE_AREA) {
	//		//vehicleContours.erase(firstContour + i);
	//		//i--;
	//		//numContours--;
	//	}
	//	// Step 7: Find centroids of contours that have not been eliminated
	//	else {
	//		vlcenter = Point2f(vlblobMoment.m10 / vlarea, vlblobMoment.m01 / vlarea);
	//		vlcentroids.push_back(vlcenter);
	//	}
	//}
	//vector<Vehicle> vltempList;
	////printf("%d\n", centroids.size());
	//for (i = 0; i < vlcentroids.size(); i++) {
	//	Vehicle x(vlcentroids[i]);
	//	vltempList.push_back(x);
	//}
	//vlvehicles = vltempList;
	//currentCarCount = 0;
	//frame.copyTo(outputFrame);
	//drawBoxes(outputFrame);
}

void VehicleTracker::drawBoxes(Mat &frame) {
	// Use function self.getVehiclePositions() to get the vehicle positions, and overlay boxes on top of the current thermal frame
	// drawBoxes may be unnecessary as meanshift and camshift draw boxes. -AZS
	vector<Point> center;
	Rect rect;
	const Scalar GREEN = Scalar(0, 255, 0);  //Assuming BGR color space.
	const Scalar RED = Scalar(0, 0, 255);  //Assuming BGR color space.
	Scalar COLOR;
	COLOR = GREEN;
	
	//for (int i = 0; i < getVehiclePositions().size(); i++)
	for (int i = 0; i < numLanes; i++) {
		for (int j = 0; j < vehicles[i].size(); j++) {
			Point temp;
			temp.x = vehicles[i][j].getPosition().x;
			temp.y = vehicles[i][j].getPosition().y;
			//COLOR = (pointPolygonTest(inboundBorder, temp, false) >= 0) ? GREEN : RED;
			rectangle(frame, Point(temp.x + 20, temp.y + 20), Point(temp.x - 20, temp.y - 20), COLOR, 3);	//Rectangle vertices are arbitrarily set.
			currentCarCount++;
		}
	}
	//printf("%d\n", getVehiclePositions().size());

	line(frame, laneBounds[0][0], laneBounds[0][1], GREEN, 3);
	line(frame, laneBounds[0][2], laneBounds[0][3], GREEN, 3);
	//line(frame, inboundBorder[2], inboundBorder[3], GREEN, 3);

}

//PRIVATE FUNCTIONS:
Mat VehicleTracker::thresholdFrame(Mat inputFrame, int lowH, int highH) {
	//Returns thresholded version of inputFrame
	Mat hsvFrame;
	Mat temp;
	// Convert frame to HSV space, to threshold color
	cvtColor(inputFrame, hsvFrame, COLOR_BGR2HSV);
	//Checks if array elements lie between lowH and highH
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
	pMOG2->apply(inputFrame, fgMaskMOG2);
	return fgMaskMOG2;
}
//BackgroundsubtractionMOG is nolonger in the opencv core. Maybe
//Mat VehicleTracker::bgSubtractionMOG(Mat inputFrame) {
//	//Returns bgSubtracted version of inputFrame, using MOG method
//	Mat fgMaskMOG;
//	Ptr<BackgroundSubtractor> pMOG;
//	pMOG = createBackgroundSubtractorMOG()
//	pMOG->apply(inputFrame, fgMaskMOG);
//	return fgMaskMOG;
//}

void VehicleTracker::findVehicleContours(Mat inputFrame, vector<vector<Point>> &outputContours) {
	// Find the contours of the input frame and store them in self.vehicleContours
	//vector<Vec4i> heirarchy;
	findContours(inputFrame, vehicleContours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	return;
}

void VehicleTracker::updateVehicleList(std::vector<Vehicle> &vehicleList, std::vector<cv::Point> boundary) {
	

	return;
}

//For VL Camera
void VehicleTracker::findVehicleContoursVL(Mat inputFrame, vector<vector<Point>> &outputContours) {
	// Find the contours of the input frame and store them in self.vehicleContours
	//vector<Vec4i> heirarchy;
	findContours(inputFrame, vehicleContoursVL, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	return;
}
//End VL Camera

void VehicleTracker::updateLaneBounds(int type,  int n, double thetaDB, std::vector<std::vector<cv::Point>> b) {
	int i;
	double slope = 0;
	//double slopeBound[2];
	
	if (n != b.size()) {
		perror("Error: numLanes provided not equal to actual number of lanes.");
		exit(1);
	}

	numLanes = n;
	if (type) {
		laneBoundsVL.clear();
		laneBoundsVL = b;
		cout << "B" << endl;
	}
	else {
		cout << "A" << endl;
		laneBounds.clear();
		laneBounds = b;
	}

	laneSlopeBounds[0].clear();
	laneSlopeBounds[1].clear();
	for (i = 0; i < b.size(); i++) {
		slope = (b[i][0].y - b[i][1].y) / (b[i][0].x - b[i][1].x);
		slope += (b[i][3].y - b[i][2].y) / (b[i][3].x - b[i][2].x);
		slope /= 2;

		laneSlopeBounds[0].push_back(tan(atan(slope) - thetaDB));
		laneSlopeBounds[1].push_back(tan(atan(slope) + thetaDB));
		//laneSlopeBounds.push_back(slopeBound);
	}
	cout << "\n Saved points: \n" << laneBounds[0] <<  endl;

	vehicles.resize(numLanes);
	return;
}

