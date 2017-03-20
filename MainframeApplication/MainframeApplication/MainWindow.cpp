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
	ui->mylabel->show();

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
	
	//begin switch statement for filters
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
	default: cerr << "switch button value invalid, exiting..." << endl;
		exit(EXIT_FAILURE);
		break;
	}

	//set up local files so show to display temporarily
	//these need to be used as resource files but I'm having troubles
	char* mapTemp = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapTemplate.png";
	char* mapBR = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapBottomRight.png";
	char* mapBL = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapBottomLeft.png";
	char* mapTR = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapTopRight.png";
	char* mapTL = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapTopLeft.png";

	char* sampleVideo1 = "thermalSample.mp4";
	char* sampleVideo2 = "4th_floor_ball_2-23-2017.mp4";

	char* mapObj;
	char* videoObj;

	int vVal = getViewVal();
	switch (vVal) {
	case 0: mapObj = mapTemp;
		//videoObj = sampleVideo1;	
		break;
	case 1: mapObj = mapBR;
	//	videoObj = sampleVideo1;
		break;
	case 2: mapObj = mapBL;
	//	videoObj = sampleVideo2;
		break;
	case 3: mapObj = mapTR; 
	//	videoObj = sampleVideo1;
		break;
	case 4: mapObj = mapTL;
	//	videoObj = sampleVideo2;
		break;
	default: cerr << "view button value invalid, exiting..." << endl;
		exit(EXIT_FAILURE);
		break;
	}

	QPixmap pixmapObject(mapObj);
	//pCap = initializeVideo(videoObj);
	
	// Show the image
	ui->topFrameWidget->showImage(outputFrame);
	ui->bottomFrameWidget->showImage(debugFrame);
	ui->mylabel->setPixmap(pixmapObject);

}

void MainWindow::updateFrames(Mat top, Mat bottom) {
	topFrameMat = top;
	bottomFrameMat = bottom;
}

// Slot function definitions

void MainWindow::onStart() {

	char* sampleVideo1 = "thermalSample.mp4";
	char* sampleVideo2 = "4th_floor_ball_2-23-2017.mp4";
	char* mapTemp = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapTemplate.png";
	char* mapBR = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapBottomRight.png";
	char* mapBL = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapBottomLeft.png";
	char* mapTR = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapTopRight.png";
	char* mapTL = "C:/Users/Shawn/Documents/Molly's Stuff/School/Capstone/mapTopLeft.png";
	char* rsTemp = "mapTemplate.png";// using a direct path works but including a resource file does not
	
	pCap = initializeVideo(sampleVideo1);

	startTimer(50);

	QPixmap pixmapObject(mapTemp);
	ui->mylabel->setPixmap(pixmapObject);
	
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
// Setting up buttons to change views in debug

void MainWindow::buttonView1(bool val) {
	if (val == TRUE)
		setViewVal(1);
}
void MainWindow::buttonView2(bool val) {
	if (val == TRUE)
		setViewVal(2);
}
void MainWindow::buttonView3(bool val) {
	if (val == TRUE)
		setViewVal(3);
}
void MainWindow::buttonView4(bool val) {
	if (val == TRUE)
		setViewVal(4);
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
void MainWindow::setButtonVal(int val){
	buttonVal = val;
}

int MainWindow::getButtonVal() {
	return buttonVal;
}

void MainWindow::setViewVal(int val) {
	viewVal = val;
}

int MainWindow::getViewVal() {
	return viewVal;
}