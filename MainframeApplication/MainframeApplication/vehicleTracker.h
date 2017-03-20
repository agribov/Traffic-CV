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
	std::vector<Vehicle> vehicles;
	cv::Mat frame; // Stores current frame
	cv::Mat lowThFrame; // UNUSED CURRENTLY
	cv::Mat highThFrame; // Stores image thresholded for hot-spots
	cv::Mat foregroundFrame; // Stores frame after background subtraction
	cv::Mat erodedFrame; // Stores frame after erosion
	cv::Mat dilatedFrame; // Stores frame after dilation
	std::vector < std::vector<cv::Point>> vehicleContours; // stores the contours of the vehicles in the current frame
	cv::Mat outputFrame; //Original frame, but with boxes overlayed on vehicles.
	//For VL Camera
	std::vector<Vehicle> vlvehicles;
	cv::Mat fgMaskMOG2; //Foreground mask for MOG2
	cv::Mat vlframe; //Stores current frame from VL camera
	cv::Mat vlhighThFrame; // Stores thresholded image for hot-spots
	cv::Mat vlforegroundFrame; // Stores foreground image after background subtraction
	cv::Mat vlerodedFrame; // Stores eroded frame
	cv::Mat vldilatedFrame; // Stores dilated frame
	std::vector < std::vector<cv::Point>> vlvehicleContours; // stores the contours of the vehicle in the current vl camera frame
	cv::Mat vloutputFrame; //Original vl frame, with boxes overlayed on vehicles
	cv::Mat vlforegroundMask; //Foreground mask created from background subtraction
	//end VL Camera
	int numCarsCurrent; // Number of cars currently in the intersection
	int numCarsTotal; //Number of cars that have gone through the intersection in total
	const int MAX_NUMBER_VEHICLES = 10; // Constant value: If number is more than this, algorithm will assume there is noise.
	const int MIN_VEHICLE_AREA = 5 * 5; // Unit is pixels
	const int MAX_VEHICLE_AREA = 200 * 200; // Unit is pixels

	int erosionVal, dilationVal;
	int lowHue, highHue;
	//For VL Camera
	int erosionValVL, dilationValVL;
	int mog2thVal; //Threshold value for MOG2
	//End VL Camera

	// Private functions
	// NOTE: These are called BY the update() function. They are "helper functions". Innaccesible, except by members of this class
	cv::Mat thresholdFrame(cv::Mat inputFrame, int lowH, int highH);
	cv::Mat erodeFrame(cv::Mat inputFrame, int sliderVal);
	cv::Mat dilateFrame(cv::Mat inputFrame, int sliderVal);
	//For VL Camera
	cv::Mat bgSubtractionMOG2(cv::Mat inputFrame);
	//cv::Mat bgSubtractionMOG(cv::Mat inputFrame); //Maybe nolonger in OpenCV core.
	//End VL Camera
	void findVehicleContours(cv::Mat inputFrame, std::vector<std::vector<cv::Point>> &outputContours);
	void updateVehicleList();
	void drawBoxes(cv::Mat &frame); // This function overlays boxes over the current location of the cars.
public:
	VehicleTracker::VehicleTracker();
	VehicleTracker(int lHue, int hHue, int er, int dil, int erVL, int dilVL); // This is the initializer for the VehicleTracker object
	std::vector<cv::Point> getVehiclePositions(); // This function returns a vector of the current vehicle centroids
	void update(cv::Mat currentFrame); // This function is called to update the algorithm when a new frame is available
	cv::Mat getTrackedFrame() { return outputFrame;}
	cv::Mat getThresholded() { return highThFrame; }
	cv::Mat getEroded() { return erodedFrame; }
	cv::Mat getDilated() { return dilatedFrame; }
	//For VL Camera
	void updatevl(cv::Mat vlcurrentFrame); // For visible light camera: This function is called to update the algorithm when a new frame is available
	//End VL Camera
	void setLowThVal(int val) { lowHue = val; };
	void setHighThVal(int val) { highHue = val; };
	void setErosionVal(int val) { erosionVal = val; };
	void setDilationVal(int val) { dilationVal = val; };
	//For VL Camera
	void setErosionValVL(int val) { erosionValVL = val; };
	void setDilationValVL(int val) { dilationValVL = val; };
	void setMOG2ThVal(int val) { mog2thVal = val; }; //Threshold value for MOG2
	//End VL Camera
};

#endif