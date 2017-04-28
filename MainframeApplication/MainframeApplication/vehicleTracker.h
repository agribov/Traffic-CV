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
#include "package_bgs/FrameDifference.h"
#include "package_bgs/IBGS.h"

class VehicleTracker {
private:
	// Private variables
	// NOTE: Most variables are updated during the update(Mat frame) function. 
	// Please see it's definition in vehicleTracker.cpp for more info

	// Variables for thermal tracking
	cv::Mat frame; // Stores current frame
	cv::Mat lowThFrame; // UNUSED CURRENTLY
	cv::Mat highThFrame; // Stores image thresholded for hot-spots
	cv::Mat foregroundFrame; // Stores frame after background subtraction
	cv::Mat erodedFrame; // Stores frame after erosion
	cv::Mat dilatedFrame; // Stores frame after dilation
	std::vector<std::vector<cv::Point>> vehicleContours; // stores the contours of the vehicles in the current frame

	// Variables for visual light tracking
	std::vector<Vehicle> vlvehicles;
	void *bgs;

	cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2;
	cv::Mat	bgMask;
	cv::Mat fgMaskMOG2; //Foreground mask for MOG2
	cv::Mat frameVL; //Stores current frame from VL camera
	cv::Mat highThFrameVL; // Stores thresholded image for hot-spots
	cv::Mat foregroundFrameVL; // Stores foreground image after background subtraction
	cv::Mat erodedFrameVL; // Stores eroded frame
	cv::Mat dilatedFrameVL; // Stores dilated frame
	std::vector < std::vector<cv::Point>> vehicleContoursVL; // stores the contours of the vehicle in the current vl camera frame
	cv::Mat outputFrameVL; //Original vl frame, with boxes overlayed on vehicles
	cv::Mat foregroundMaskVL; //Foreground mask created from background subtraction
	cv::Mat hsvFrameVL; //Converted vl frame to hsv frame
	//end VL Camera
	int numCarsCurrent; // Number of cars currently in the intersection
	int numCarsTotal; //Number of cars that have gone through the intersection in total
	const int MAX_NUMBER_VEHICLES = 10; // Constant value: If number is more than this, algorithm will assume there is noise.
	const int MIN_VEHICLE_AREA = 5 * 5; // Unit is pixels
	const int MAX_VEHICLE_AREA = 200 * 200; // Unit is pixels
	std::vector<std::vector<Vehicle>> vehicles;
	std::vector<Vehicle> vehiclesVL;
	cv::Mat outputFrame; //Original frame, but with boxes overlayed on vehicles.
	int frameCount;
	int frameCountVL;

	bgslibrary::algorithms::IBGS *newbgs;

	int numLanes;
	int numLanesVL;
	std::vector<std::vector<cv::Point>> laneBounds;
	std::vector<std::vector<cv::Point>> laneBoundsVL;

	std::vector<double> laneSlopeBounds[2];
	std::vector<std::vector<cv::Point>> borders;
	std::vector<cv::Point> inboundBorder;


	int erosionVal, dilationVal;
	int lowHue, highHue;
	//For VL Camera
	int erosionValVL, dilationValVL;
	int mog2thVal; //Threshold value for MOG2
	//End VL Camera

	int totalCount;
	int totalCountVL;

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
	void updateVehicleList(std::vector<Vehicle> &vehicleList, std::vector<cv::Point> boundary);
	void drawBoxes(bool type, cv::Mat &frame); // This function overlays boxes over the current location of the cars.
	//For VL Camera
	void findVehicleContoursVL(cv::Mat inputFrame, std::vector<std::vector<cv::Point>> &outputContours);
	//End VL Camera
public:
	VehicleTracker::VehicleTracker();
	VehicleTracker::~VehicleTracker();
	VehicleTracker(int lHue, int hHue, int er, int dil, int erVL, int dilVL); // This is the initializer for the VehicleTracker object
	std::vector<cv::Point> getVehiclePositions(); // This function returns a vector of the current vehicle centroids
	void update(cv::Mat currentFrame); // This function is called to update the algorithm when a new frame is available
	cv::Mat getTrackedFrame() { return outputFrame; }
	cv::Mat getThresholded() { return highThFrame; }
	cv::Mat getEroded() { return erodedFrame; }
	cv::Mat getDilated() { return dilatedFrame; }
	//For VL Camera
	void updatevl(cv::Mat currentFrameVL); // For visible light camera: This function is called to update the algorithm when a new frame is available
	cv::Mat getTrackedFrameVL() { return outputFrameVL; }
	cv::Mat getErodedVL() { return erodedFrameVL; }
	cv::Mat getDilatedVL() { return dilatedFrameVL; }
	cv::Mat getBgSub() { return fgMaskMOG2; }
	//End VL Camera
	void setLowThVal(int val) { lowHue = val; };
	void setHighThVal(int val) { highHue = val; };
	void setErosionVal(int val) { erosionVal = val; };
	void setDilationVal(int val) { dilationVal = val; };
	int getLowThVal() { return lowHue; };
	int getHighThVal() { return highHue; };
	int getErosionVal() { return erosionVal; };
	int getDilationVal() { return dilationVal; };
	//For VL Camera
	void setErosionValVL(int val) { erosionValVL = val; };
	void setDilationValVL(int val) { dilationValVL = val; };
	int getErosionValVL() { return erosionValVL; };
	int getDilationValVL() { return dilationValVL; };
	void setMOG2ThVal(int val) { mog2thVal = val; }; //Threshold value for MOG2
	//End VL Camera

	void updateLaneBounds(int type, int n, double thetaDB, std::vector<std::vector<cv::Point>> bounds);
	int isCalibrated(int type) { return (type) ? (bool)numLanesVL : (bool)numLanes; };

	int getNumCars() { return currentCarCount; }
	int getNumCarsVL() { return vehiclesVL.size(); }
	int getAvgVel();
	int getAvgVelVL();
	int getTotalCars() { return totalCount; }
	int getTotalCarsVL() { return totalCountVL; }
};

#endif