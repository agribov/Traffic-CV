/********************************************************************************/
/*                                                                              */
/* Program: Mainframe Thermal Image Processor                                   */
/*                                                                              */
/* File: utilities.cpp                                                          */
/*                                                                              */
/* Author(s): Alex Gribov, Alexander Senckowski, Molly McGuire and Kevin Smida  */
/*                                                                              */
/* All Right Reserved (c) 2017                                                  */
/*                                                                              */
/********************************************************************************/

#include "globals.h"

using namespace std;
using namespace cv;

bool endCal = false;
vector<vector<Point>> calPoints;


double getDist(Point A, Point B) {
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double getDistToLine(Point A, Point B, Point X) {
	double size = getDist(A, B);

	B -= A;
	X -= A;

	// Cross-product (X x B) over line length
	double dist = ((X.x * B.y) - (X.y * B.x));
	return dist / size;

}

void drawPoints(Mat &frame, vector<Point> points) {
	vector<Point> center;
	Rect rect;
	const Scalar GREEN = Scalar(0, 255, 0);  //Assuming BGR color space.
	const Scalar RED = Scalar(0, 0, 255);  //Assuming BGR color space.
	Scalar COLOR;
	COLOR = GREEN;

	//for (int i = 0; i < getVehiclePositions().size(); i++)
	for (int i = 0; i < points.size(); i++) {
		//Point temp = points[i];
		//COLOR = (pointPolygonTest(inboundBorder, temp, false) >= 0) ? GREEN : RED;
		//rectangle(frame, Point(temp.x + 10, temp.y + 10), Point(temp.x - 10, temp.y - 10), COLOR, 3);	//Rectangle vertices are arbitrarily set.
		circle(frame, points[i], 2, GREEN, 3);
	}

}

void onMouse(int event, int x, int y, int flags, void* userData) {
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
		if (vCoordinates.size() % 4 == 0) {
			vvCoordinates.push_back(vCoordinates);
			endCal = true;
			destroyWindow("Calibration");
			calPoints = vvCoordinates;
			vCoordinates.clear();
			vvCoordinates.clear();
			cout << "\nSaving points: \n" << calPoints[0] << endl;
		}

		//Test code that prints vector coordinates
		cout << "Left Button of mouse was clicked at position(" << x << "," << y << ")" << endl;
		cout << "Vector coordinates\n" << vCoordinates << endl;

		//Test code that prints first three elements of the vector of vectors
		if (vvCoordinates.size() == 1)
			cout << "Vector of vector coordinates" << vvCoordinates[0] << endl;

		if (vvCoordinates.size() == 2)
			cout << "Vector of vector coordinates" << vvCoordinates[1] << endl;

		if (vvCoordinates.size() == 3)
			cout << "Vector of vector coordinates" << vvCoordinates[2] << endl;

	}
}

void calibrate(cv::Mat frame) {
	namedWindow("Calibration", WINDOW_AUTOSIZE);
	imshow("Calibration", frame);
	setMouseCallback("Calibration", onMouse, 0);
}