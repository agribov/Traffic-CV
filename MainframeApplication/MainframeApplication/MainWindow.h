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
	void setButtonVal(int);
	void setViewVal(int);
	void setCurrentState(int);
	void setLastState(int);
	void changeImage();
	int getButtonVal();
	int getViewVal();
	int getCurrentState();
	int getLastState();

private slots:
	void onStart();

	void buttonView1(bool val);
	void buttonView2(bool val);
	void buttonView3(bool val);
	void buttonView4(bool val);

	void buttonOriginalWindow(bool val);
	void buttonThreshold(bool val);
	void buttonErode(bool val);
	void buttonDilate(bool val);

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
	int currentState;
	
	int lastState = 0;
	int buttonVal = 0;
	int viewVal = 0;
	
	void viewOne();
	void viewTwo();

	//For VL Camera
	int dilateValVL;
	int erodeValVL;
	//End VL Camera

protected:
	void timerEvent(QTimerEvent *Event);
};

#endif // MAINWINDOW_H
