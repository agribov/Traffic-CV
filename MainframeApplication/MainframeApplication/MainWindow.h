#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globals.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	void updateFrames(Mat top, Mat bottom);
	~MainWindow();

private slots:
	void onStart();

private:
	Ui::MainWindow *ui;
	Mat topFrameMat;
	Mat bottomFrameMat;

	Mat inputFrame;
	Mat outputFrame;
	Mat debugFrame;
	
	VideoCapture *pCap;
	VehicleTracker tracker;

protected:
	void timerEvent(QTimerEvent *Event);
};

#endif // MAINWINDOW_H
