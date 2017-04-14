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
	explicit MainWindow(QWidget *parent = 0);
	void updateFrames(cv::Mat top, cv::Mat bottom);
	~MainWindow();

private slots:
	void onStart();
	void onLowThValueChanged(int val);
	void onHighThValueChanged(int val);
	void onDilateValueChanged(int val);
	void onErodeValueChanged(int val);
	//For VL Camera
	void onDilateValueChangedVL(int val);
	void onErodeValueChangedVL(int val);
	//End VL Camera

private:
	Ui::MainWindow *ui;
	cv::Mat topFrameMat;
	cv::Mat bottomFrameMat;

	cv::Mat inputFrame;
	cv::Mat outputFrame;
	cv::Mat debugFrame;

	//For VL Camera
	cv::Mat outputFrameVL;
	cv::Mat debugFrameVL;
	
	cv::VideoCapture *pCap;
	VehicleTracker *tracker;

	int lowHueVal;
	int highHueVal;
	int dilateVal;
	int erodeVal;

	//For VL Camera
	int dilateValVL;
	int erodeValVL;
	//End VL Camera

protected:
	void timerEvent(QTimerEvent *Event);
};

#endif // MAINWINDOW_H
