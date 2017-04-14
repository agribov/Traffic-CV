#include "globals.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "videoHelper.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	tracker(new VehicleTracker(0, 50, 0, 0, 0, 0))
{
	//tracker = new VehicleTracker(lowHueVal, highHueVal, dilateVal, erodeVal);
	//tracker = new VehicleTracker();
	ui->setupUi(this);

	ui->thresholdLowSlider->setMinimum(0);
	ui->thresholdLowSlider->setMaximum(100);
	ui->thresholdHighSlider->setMinimum(0);
	ui->thresholdHighSlider->setMaximum(100);
	ui->dilateSlider->setMinimum(0);
	ui->dilateSlider->setMaximum(100);
	ui->erodeSlider->setMinimum(0);
	ui->erodeSlider->setMaximum(100);
	//For VL Camera
	ui->dilateSliderVL->setMinimum(0);
	ui->dilateSliderVL->setMaximum(100);
	ui->erodeSliderVL->setMinimum(0);
	ui->erodeSliderVL->setMaximum(100);
	//End VL Camera


	lowHueVal = 0;
	highHueVal = 50;
	dilateVal = 0;
	erodeVal = 0;
	//For VL Camera
	dilateValVL = 0;
	erodeValVL = 0;
	//End VL Camera

	ui->thresholdLowSlider->setValue(lowHueVal);
	ui->thresholdHighSlider->setValue(highHueVal);
	ui->dilateSlider->setValue(dilateVal);
	ui->erodeSlider->setValue(erodeVal);
	//For VL Camera
	ui->dilateSliderVL->setValue(dilateValVL);
	ui->erodeSliderVL->setValue(erodeValVL);
	//End VL Camera
}

MainWindow::~MainWindow()
{
	delete ui;
	(*pCap).release();
}

void MainWindow::timerEvent(QTimerEvent *Event) {
	
	//read the current frame
	if (!(*pCap).read(inputFrame)) {
		cerr << "Unable to read next frame." << endl;
		cerr << "Exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	//tracker->update(inputFrame);
	//outputFrame = tracker->getTrackedFrame();
	//debugFrame = tracker->getEroded();

	//For VL Camera
	tracker->updatevl(inputFrame);
	outputFrame = tracker->getTrackedFrame();
	debugFrame = tracker->getErodedVL();

	ui->topFrameWidget->showImage(outputFrame);
	ui->bottomFrameWidget->showImage(debugFrame);
	//End VL Camera

	// Show the image
	//ui->topFrameWidget->showImage(outputFrame);
	//ui->bottomFrameWidget->showImage(debugFrame);

}

void MainWindow::updateFrames(Mat top, Mat bottom) {
	topFrameMat = top;
	bottomFrameMat = bottom;
}

// Slot function definitions

void MainWindow::onStart() {

	char* sampleVideo1 = "thermalSample.mp4";
	char* sampleVideo2 = "4th_floor_ball_2-23-2017.mp4";
	char* vlsampleVideo1 = "FroggerHighway.mp4"; //visual light test video.
	pCap = initializeVideo(sampleVideo1); // This functions defined in videoHelper.cpp

	startTimer(50);

	return;
}

void MainWindow::onLowThValueChanged(int val) {
	lowHueVal = val;
	tracker->setLowThVal(val);
}
void MainWindow::onHighThValueChanged(int val) {
	highHueVal = val;
	tracker->setHighThVal(val);
}

void MainWindow::onDilateValueChanged(int val) {
	dilateVal = val;
	tracker->setDilationVal(val);
}

void MainWindow::onErodeValueChanged(int val) {
	erodeVal = val;
	tracker->setErosionVal(val);
}
//For VL Camera
void MainWindow::onDilateValueChangedVL(int val) {
	erodeValVL = val;
	tracker->setDilationValVL(val);
}

void MainWindow::onErodeValueChangedVL(int val) {
	dilateValVL = val;
	tracker->setErosionValVL(val);
}
//End VL Camera