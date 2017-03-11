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

private:
	Ui::MainWindow *ui;
	cv::Mat topFrameMat;
	cv::Mat bottomFrameMat;

	cv::Mat inputFrame;
	cv::Mat outputFrame;
	cv::Mat debugFrame;
	
	cv::VideoCapture *pCap;
	VehicleTracker *tracker;

	int lowHueVal;
	int highHueVal;
	int dilateVal;
	int erodeVal;

protected:
	void timerEvent(QTimerEvent *Event);
};

#endif // MAINWINDOW_H