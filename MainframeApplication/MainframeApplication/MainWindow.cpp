#include "globals.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "videoHelper.h"
#include "utilities.h"

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

	for (int i = 0; i < NUM_ROADS; i++) trackers[i] = new VehicleTracker(0, 50, 0, 0, 0, 0);

	ui->thresholdLowSlider->setValue(lowHueVal);
	ui->thresholdHighSlider->setValue(highHueVal);
	ui->dilateSlider->setValue(dilateVal);
	ui->erodeSlider->setValue(erodeVal);
	ui->MapDisplay->show();

	//For VL Camera
	ui->dilateSliderVL->setValue(dilateValVL);
	ui->erodeSliderVL->setValue(erodeValVL);
	//End VL Camera

	// Set default view to thermal;
	viewType = FALSE;
	viewVal = 0;
	buttonVal = 1;
	cal = false;
}

MainWindow::~MainWindow()
{
	delete ui;
	for (int i = 0; i < NUM_ROADS; i++) {
		(*pCapTh[i]).release();
		(*pCapVl[i]).release();
		free(trackers[i]);
	}
}

void MainWindow::timerEvent(QTimerEvent *Event) {

	if (lastState != viewVal) {
		lastState = viewVal;
		ui->thresholdHighSlider->setSliderPosition(trackers[viewVal]->getHighThVal());
		ui->thresholdLowSlider->setSliderPosition(trackers[viewVal]->getLowThVal());
		ui->erodeSlider->setSliderPosition(trackers[viewVal]->getErosionVal());
		ui->dilateSlider->setSliderPosition(trackers[viewVal]->getDilationVal());
		ui->erodeSliderVL->setSliderPosition(trackers[viewVal]->getErosionValVL());
		ui->dilateSliderVL->setSliderPosition(trackers[viewVal]->getDilationValVL());

	}

	for (int i = 0; i < NUM_ROADS; i++) {
		
		if (!(*pCapTh[i]).read(inputFrames[i])) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		if (!(*pCapVl[i]).read(inputFramesVl[i])) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		//trackers[i]->updatevl(inputFramesVl[i]);
		//trackers[i]->update(inputFrames[i]);
	}

	int v = viewVal;
	if (endCal) {
		cal = endCal = false;
		trackers[v]->updateLaneBounds(viewType, 1, 5, calPoints);
	}
	if (cal) (viewType)? calibrate(inputFramesVl[v]) : calibrate(inputFrames[v]);

	vector<QTableWidgetItem*> cells;
	cells.resize(12);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++) {
			cells[3 * i + j] = new QTableWidgetItem; // add this line 
			int num;
			if (i == 0) num = rand() % 5;
			else if (i == 1) num = rand() % 30;
			else if (i == 2) num = rand() % 3;
			cells[3 * i + j]->setText(QString::number(num));
			ui->OutputTable->setItem(i, j, cells[3 * i + j]);
		}

	if (trackers[v]->isCalibrated(0)) {
		cout << "thermal update" << endl;
		trackers[v]->update(inputFrames[v]);
		if (!viewType) outputFrames[v] = trackers[v]->getTrackedFrame();
	}
	else if (!viewType) outputFrames[v] = inputFrames[v];
	if (trackers[v]->isCalibrated(1)) {
		trackers[v]->updatevl(inputFramesVl[v]);
		if (viewType) outputFrames[v] = trackers[v]->getTrackedFrameVL();
	}
	else if (viewType) outputFrames[v] = inputFramesVl[v];

	//begin switch statement for filters
	outputFrames[v] = (viewType) ? trackers[v]->getTrackedFrameVL() : trackers[v]->getTrackedFrame();
	//trackers[v]->updatevl(inputFramesVl[v]);
	trackers[v]->update(inputFrames[v]);

	switch (buttonVal) {
	case 1: debugFrame = (viewType) ? inputFramesVl[v] : inputFrames[v];
		break;
	case 2: debugFrame = (viewType) ? trackers[v]->getThresholded() : trackers[v]->getThresholded(); // NO VL THRESHOLDING
		break;
	case 3: debugFrame = (viewType) ? trackers[v]->getErodedVL() : trackers[v]->getEroded();
		break;
	case 4: debugFrame = (viewType) ? trackers[v]->getErodedVL() : trackers[v]->getDilated();
		break;
	default: cerr << "switch button value invalid, exiting..." << endl;
		exit(EXIT_FAILURE);
		break;
	}

	// these are the image files associated with the camera views at the intersection
	char* mapTemp = "mapTemplate.png";
	char* mapBR = "mapBottomRight.png";
	char* mapBL = "mapBottomLeft.png";
	char* mapTR = "mapTopRight.png";
	char* mapTL = "mapTopLeft.png";

	char* mapObj;
	char* videoObj;

	switch (viewVal) {
	case 0: 
		mapObj = mapTemp;
		break;
	case 1: 
		mapObj = mapBR;
		break;
	case 2: 
		mapObj = mapBL;
		break;
	case 3: 
		mapObj = mapTR;
		break;
	case 4: 
		mapObj = mapTL;
		break;
	default: cerr << "view button value invalid, exiting..." << endl;
		exit(EXIT_FAILURE);
		break;
	}

	QPixmap pixmapObject(mapObj);

	// Show the image
	ui->topFrameWidget->showImage(outputFrames[v]);
	ui->bottomFrameWidget->showImage(debugFrame);
	ui->MapDisplay->setPixmap(pixmapObject);
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
	//Thermal video declarations
	char* videoTh[NUM_ROADS] = { "thermalSample.mp4", "4th_floor_ball_2-23-2017.mp4", "Alina's apt1.mp4", "thermalSample.mp4" };
	//Visual video declarations
	char* videoVl[NUM_ROADS] = { "visualVid1.mp4", "visualVid1.mp4", "visualVid1.mp4", "visualVid1.mp4" };

	// Other declarations
	char* streetMap = "mapTemplate.png"; // using a direct path works but including a resource file does not

	// Initialize video
	for (int i = 0; i < NUM_ROADS; i++) {
		pCapTh[i] = initializeVideo(videoTh[i]);
		pCapVl[i] = initializeVideo(videoVl[i]);
		trackers[i] = new VehicleTracker(0, 50, 0, 0, 0, 0);
	}

	// Start the timer
	startTimer(50);

	// Set up the map display
	QPixmap pixmapObject(streetMap);
	ui->MapDisplay->setPixmap(pixmapObject);

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

void MainWindow::buttonVisual(bool val) {
	if (val) viewType = TRUE;
}

void MainWindow::buttonThermal(bool val) {
	if (val) viewType = FALSE;
}
// Setting up buttons to change views in debug

void MainWindow::buttonView1(bool val) {
	if (val == TRUE) {
		lastState = viewVal;
		viewVal = 0;
	}
}
void MainWindow::buttonView2(bool val) {
	if (val == TRUE) {
		lastState = viewVal;
		viewVal = 1;
	}
}
void MainWindow::buttonView3(bool val) {
	if (val == TRUE) {
		lastState = viewVal;
		viewVal = 2;
	}
}
void MainWindow::buttonView4(bool val) {
	if (val == TRUE) {
		lastState = viewVal;
		viewVal = 3;
	}
}

// trackbar ui 
void MainWindow::onLowThValueChanged(int val) {
	lowHueVal = val;
	trackers[viewVal]->setLowThVal(val);
}
void MainWindow::onHighThValueChanged(int val) {
	highHueVal = val;
	trackers[viewVal]->setHighThVal(val);
}

void MainWindow::onDilateValueChanged(int val) {
	dilateVal = val;
	trackers[viewVal]->setDilationVal(val);
}

void MainWindow::onErodeValueChanged(int val) {
	erodeVal = val;
	trackers[viewVal]->setErosionVal(val);
}
//switch statement setters and getters
void MainWindow::setButtonVal(int val){
	buttonVal = val;
}

// functions made for detecting changes in the current view of the UI

void MainWindow::setLastState(int val) {
	lastState = val;
}

// The following code details my attempt at opening a new window in
// qt from the menu bar in the main window.

void MainWindow::slotOpen() {
	QWidget  *wgt = new QWidget(this);
	wgt->show();
}

void MainWindow::buttonCalibrate() {
	cal = true;
}


//For VL Camera
void MainWindow::onDilateValueChangedVL(int val) {
	erodeValVL = val;
	trackers[viewVal]->setDilationValVL(val);
}

void MainWindow::onErodeValueChangedVL(int val) {
	dilateValVL = val;
	trackers[viewVal]->setErosionValVL(val);
}
//End VL Camera