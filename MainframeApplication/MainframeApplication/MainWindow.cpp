#include "globals.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "videoHelper.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	tracker(new VehicleTracker(0, 50, 0, 0))
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

	lowHueVal = 0;
	highHueVal = 50;
	dilateVal = 0;
	erodeVal = 0;

	ui->thresholdLowSlider->setValue(lowHueVal);
	ui->thresholdHighSlider->setValue(highHueVal);
	ui->dilateSlider->setValue(dilateVal);
	ui->erodeSlider->setValue(erodeVal);
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

	tracker->update(inputFrame);
	outputFrame = tracker->getTrackedFrame();
	debugFrame = tracker->getEroded();

	//begin switch statement
	int sVal = getButtonVal();
	switch (sVal) {
	case 0: debugFrame = tracker->getEroded();
		break;
	case 1: debugFrame = tracker->getTrackedFrame();
		break;
	case 2: debugFrame = tracker->getThresholded();
		break;
	case 3: debugFrame = tracker->getEroded();
		break;
	case 4: debugFrame = tracker->getDilated();
		break;
	default: cerr << "switch value invalid, exiting..." << endl;
		exit(EXIT_FAILURE);
		break;
	}
	
	// Show the image
	ui->topFrameWidget->showImage(outputFrame);
	ui->bottomFrameWidget->showImage(debugFrame);

}

void MainWindow::updateFrames(Mat top, Mat bottom) {
	topFrameMat = top;
	bottomFrameMat = bottom;
}

// Slot function definitions

void MainWindow::onStart() {

	char* sampleVideo1 = "thermalSample.mp4";
	char* sampleVideo2 = "4th_floor_ball_2-23-2017.mp4";
	pCap = initializeVideo(sampleVideo1); // This functions defined in videoHelper.cpp

	startTimer(50);

	return;
}
//buttons for the ui, setting booleans to numerical 
//values to use in a switch statement.
void MainWindow::buttonOriginalWindow(bool val){
	if (val == TRUE)
		setButtonVal(1);
}

void MainWindow::buttonThreshold(bool val){
	if (val == TRUE)
		setButtonVal(2);
}

void MainWindow::buttonErode(bool val){
	if (val == TRUE)
		setButtonVal(3);
}

void MainWindow::buttonDilate(bool val){
	if (val == TRUE)
		setButtonVal(4);
}
// trackbar ui 
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
//switch statement setters and getters
void MainWindow::setButtonVal(int val)
{
	buttonVal = val;
}
int MainWindow::getButtonVal() {
	return buttonVal;
}