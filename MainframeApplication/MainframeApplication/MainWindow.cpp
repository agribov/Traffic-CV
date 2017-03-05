#include "globals.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "videoHelper.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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

	tracker.update(inputFrame);
	outputFrame = tracker.getTrackedFrame();
	debugFrame = tracker.getEroded();

	// Show the image
	ui->topFrameWidget->showImage(outputFrame);
	ui->topFrameWidget->showImage(debugFrame);

}

void MainWindow::updateFrames(Mat top, Mat bottom) {
	topFrameMat = top;
	bottomFrameMat = bottom;
}

void MainWindow::onStart() {

	char* sampleVideo = "thermalSample.mp4";
	pCap = initializeVideo(sampleVideo); // Defined in videoHelper.cpp

	startTimer(50);

	return;
}
