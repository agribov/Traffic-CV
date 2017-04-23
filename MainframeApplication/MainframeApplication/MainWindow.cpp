#include "globals.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "videoHelper.h"
#include "utilities.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->thresholdLowSlider->setMinimum(0);
	ui->thresholdLowSlider->setMaximum(100);
	ui->thresholdHighSlider->setMinimum(0);
	ui->thresholdHighSlider->setMaximum(100);
	ui->dilateSlider->setMinimum(0);
	ui->dilateSlider->setMaximum(75);
	ui->erodeSlider->setMinimum(0);
	ui->erodeSlider->setMaximum(30);
	//For VL Camera
	ui->dilateSliderVL->setMinimum(0);
	ui->dilateSliderVL->setMaximum(75);
	ui->erodeSliderVL->setMinimum(0);
	ui->erodeSliderVL->setMaximum(30);
	//End VL Camera


	lowHueVal = 0;
	highHueVal = 50;
	dilateVal = 0;
	erodeVal = 0;
	//For VL Camera
	dilateValVL = 50;
	erodeValVL = 10;
	//End VL Camera

	for (int i = 0; i < NUM_ROADS; i++) trackers[i] = new VehicleTracker(0, 50, 0, 0, 17, 50);

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
		if (started) {
			(*pCapTh[i]).release();
			(*pCapVl[i]).release();
		}
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
		Mat vlFrame[NUM_ROADS];
		while (!(*pCapTh[i]).read(inputFrames[i])) {
			//cerr << "Unable to read next frame." << endl;
			//cerr << "Exiting..." << endl;
			//exit(EXIT_FAILURE);
			releaseVideo(pCapTh[i]);
			pCapTh[i] = initializeVideo(videoTh[i]);
		}

		while (!(*pCapVl[i]).read(vlFrame[i])) {
			//cerr << "Unable to read next frame." << endl;
			//cerr << "Exiting..." << endl;
			//exit(EXIT_FAILURE);
			releaseVideo(pCapVl[i]);
			pCapVl[i] = initializeVideo(videoVl[i]);
		}
		flip(vlFrame[i], inputFramesVl[i], 0);


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
		//cout << "thermal update" << endl;
		if (!viewType) {
			trackers[v]->update(inputFrames[v]);
			outputFrames[v] = trackers[v]->getTrackedFrame();
		}
	}
	else if (!viewType) outputFrames[v] = inputFrames[v];
	if (trackers[v]->isCalibrated(1)) {
		if (viewType) {
			trackers[v]->updatevl(inputFramesVl[v]);
			outputFrames[v] = trackers[v]->getTrackedFrameVL();
		}
	}
	else if (viewType) outputFrames[v] = inputFramesVl[v];

	//begin switch statement for filters
	//outputFrames[v] = (viewType) ? trackers[v]->getTrackedFrameVL() : trackers[v]->getTrackedFrame();
	//trackers[v]->updatevl(inputFramesVl[v]);
	//trackers[v]->update(inputFrames[v]);

	switch (buttonVal) {
	case 1: debugFrame = (viewType) ? inputFramesVl[v] : inputFrames[v];
		cout << "Original" << endl;
		break;
	case 2: debugFrame = (viewType) ? trackers[v]->getBgSub() : trackers[v]->getThresholded(); // NO VL THRESHOLDING
		cout << "MOG" << endl;
		break;
	case 3: debugFrame = (viewType) ? trackers[v]->getErodedVL() : trackers[v]->getEroded();
		cout << "Erode" << endl;
		break;
	case 4: debugFrame = (viewType) ? trackers[v]->getDilatedVL() : trackers[v]->getDilated();
		cout << "Dilate" << endl;
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
		mapObj = mapBR;
		break;
	case 1: 
		mapObj = mapBL;
		break;
	case 2: 
		mapObj = mapTR;
		break;
	case 3: 
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
	//Filenames initialized as members in the .h file
	started = true;
	char* streetMap = "mapTemplate.png"; // using a direct path works but including a resource file does not

	// Initialize video
	for (int i = 0; i < NUM_ROADS; i++) {
		pCapTh[i] = initializeVideo(videoTh[i]);
		pCapVl[i] = initializeVideo(videoVl[i]);
		//trackers[i] = new VehicleTracker(0, 50, 0, 0, 17, 50);
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
void MainWindow::buttonOriginalImage(bool val){
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
	cout << "New Value: " << val << endl;
}
void MainWindow::onHighThValueChanged(int val) {
	highHueVal = val;
	trackers[viewVal]->setHighThVal(val);
	cout << "New Value: " << val << endl;
}

void MainWindow::onDilateValueChanged(int val) {
	dilateVal = val;
	trackers[viewVal]->setDilationVal(val);
	cout << "New Value: " << val << endl;
}

void MainWindow::onErodeValueChanged(int val) {
	erodeVal = val;
	trackers[viewVal]->setErosionVal(val);
	cout << "New Value: " << val << endl;
}

void MainWindow::onDilateValueChangedVL(int val) {
	dilateValVL = val;
	trackers[viewVal]->setDilationValVL(val);
	cout << "New Value: " << val << endl;
}

void MainWindow::onErodeValueChangedVL(int val) {
	erodeValVL = val;
	trackers[viewVal]->setErosionValVL(val);
	cout << "New Value: " << val << endl;

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