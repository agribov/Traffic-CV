#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globals.h"
#include "vehicleTracker.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	static const int NUM_ROADS = 4;

	explicit MainWindow(QWidget *parent = 0);
	void updateFrames(cv::Mat top, cv::Mat bottom);
	~MainWindow();
	void setButtonVal(int);
	void setLastState(int);

private slots:
	void onStart();

	void buttonView1(bool val);
	void buttonView2(bool val);
	void buttonView3(bool val);
	void buttonView4(bool val);

	void buttonOriginalImage(bool val);
	void buttonThreshold(bool val);
	void buttonErode(bool val);
	void buttonDilate(bool val);

	void buttonVisual(bool val);
	void buttonThermal(bool val);

	void buttonCalibrate();

	void onLowThValueChanged(int val);
	void onHighThValueChanged(int val);
	void onDilateValueChanged(int val);
	void onErodeValueChanged(int val);
	//For VL Camera
	void onDilateValueChangedVL(int val);
	void onErodeValueChangedVL(int val);
	//End VL Camera

	void slotOpen();

private:
	Ui::MainWindow *ui;
	cv::Mat topFrameMat;
	cv::Mat bottomFrameMat;

	cv::Mat inputFrame;
	cv::Mat inputFrames[NUM_ROADS];
	cv::Mat inputFramesVl[NUM_ROADS];
	cv::Mat outputFrame;
	cv::Mat outputFrames[NUM_ROADS];
	cv::Mat debugFrame;

	//For VL Camera
	cv::Mat outputFrameVL;
	cv::Mat debugFrameVL;
	
	cv::VideoCapture *pCapTh[NUM_ROADS];
	cv::VideoCapture *pCapVl[NUM_ROADS];

	VehicleTracker *tracker;
	VehicleTracker *trackers[4];

	//Thermal video declarations
	char *videoTh[NUM_ROADS] = { "croppedSample.mp4", "4th_floor_ball_2-23-2017.mp4", "Alina's apt1.mp4", "croppedSample.mp4" };
	//Visual video declarations
	char *videoVl[NUM_ROADS] = { "visualVid1.mp4", "visualVid1.mp4", "visualVid1.mp4", "visualVid1.mp4" };

	int lowHueVal;
	int highHueVal;
	int dilateVal;
	int erodeVal;
	int currentState;
	
	int lastState = 0;
	int buttonVal = 0;
	int viewVal = 0;

	bool viewType; // 0 is thermal, 1 is visual

	bool cal;

	//For VL Camera
	int dilateValVL;
	int erodeValVL;
	//End VL Camera

	bool started = false;

protected:
	void timerEvent(QTimerEvent *Event);
};

#endif // MAINWINDOW_H
