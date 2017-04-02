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