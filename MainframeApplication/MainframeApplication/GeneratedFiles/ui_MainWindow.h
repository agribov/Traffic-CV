/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "cqtopencvviewergl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStream;
    QAction *actionFile;
    QAction *actionDebug_Layout;
    QAction *actionRelease_Layout;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    CQtOpenCVViewerGl *topFrameWidget;
    QLabel *MapDisplay;
    CQtOpenCVViewerGl *bottomFrameWidget;
    QGroupBox *groupParameters;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lowThLabel;
    QLabel *highThLabel;
    QLabel *erodeLabel;
    QLabel *dilateLabel;
    QSlider *erodeSlider;
    QSlider *dilateSlider;
    QSlider *thresholdHighSlider;
    QSlider *thresholdLowSlider;
    QLabel *erodeLabelVL;
    QLabel *dilateLabelVL;
    QSlider *erodeSliderVL;
    QSlider *dilateSliderVL;
    QGroupBox *groupBox_5;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton;
    QRadioButton *radioButton_10;
    QRadioButton *radioButton_9;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_4;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton;
    QGroupBox *groupBox;
    QTableWidget *OutputTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuOpen;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1178, 975);
        MainWindow->setAcceptDrops(false);
        MainWindow->setDocumentMode(false);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionStream = new QAction(MainWindow);
        actionStream->setObjectName(QStringLiteral("actionStream"));
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        actionDebug_Layout = new QAction(MainWindow);
        actionDebug_Layout->setObjectName(QStringLiteral("actionDebug_Layout"));
        actionDebug_Layout->setCheckable(false);
        actionDebug_Layout->setChecked(false);
        actionRelease_Layout = new QAction(MainWindow);
        actionRelease_Layout->setObjectName(QStringLiteral("actionRelease_Layout"));
        actionRelease_Layout->setCheckable(false);
        actionRelease_Layout->setMenuRole(QAction::ApplicationSpecificRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        topFrameWidget = new CQtOpenCVViewerGl(centralwidget);
        topFrameWidget->setObjectName(QStringLiteral("topFrameWidget"));
        topFrameWidget->setMinimumSize(QSize(380, 240));

        gridLayout_2->addWidget(topFrameWidget, 0, 0, 1, 1);

        MapDisplay = new QLabel(centralwidget);
        MapDisplay->setObjectName(QStringLiteral("MapDisplay"));
        MapDisplay->setMinimumSize(QSize(380, 280));
        MapDisplay->setScaledContents(true);

        gridLayout_2->addWidget(MapDisplay, 2, 0, 1, 1);

        bottomFrameWidget = new CQtOpenCVViewerGl(centralwidget);
        bottomFrameWidget->setObjectName(QStringLiteral("bottomFrameWidget"));
        bottomFrameWidget->setMinimumSize(QSize(380, 240));

        gridLayout_2->addWidget(bottomFrameWidget, 1, 0, 1, 1);

        groupParameters = new QGroupBox(centralwidget);
        groupParameters->setObjectName(QStringLiteral("groupParameters"));
        groupParameters->setEnabled(true);
        groupParameters->setMinimumSize(QSize(750, 240));
        groupParameters->setCheckable(false);
        layoutWidget = new QWidget(groupParameters);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 28, 721, 224));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lowThLabel = new QLabel(layoutWidget);
        lowThLabel->setObjectName(QStringLiteral("lowThLabel"));

        gridLayout->addWidget(lowThLabel, 0, 1, 1, 1);

        highThLabel = new QLabel(layoutWidget);
        highThLabel->setObjectName(QStringLiteral("highThLabel"));

        gridLayout->addWidget(highThLabel, 1, 1, 1, 1);

        erodeLabel = new QLabel(layoutWidget);
        erodeLabel->setObjectName(QStringLiteral("erodeLabel"));

        gridLayout->addWidget(erodeLabel, 3, 1, 1, 1);

        dilateLabel = new QLabel(layoutWidget);
        dilateLabel->setObjectName(QStringLiteral("dilateLabel"));

        gridLayout->addWidget(dilateLabel, 2, 1, 1, 1);

        erodeSlider = new QSlider(layoutWidget);
        erodeSlider->setObjectName(QStringLiteral("erodeSlider"));
        erodeSlider->setTracking(true);
        erodeSlider->setOrientation(Qt::Horizontal);
        erodeSlider->setTickPosition(QSlider::TicksBelow);
        erodeSlider->setTickInterval(10);

        gridLayout->addWidget(erodeSlider, 3, 0, 1, 1);

        dilateSlider = new QSlider(layoutWidget);
        dilateSlider->setObjectName(QStringLiteral("dilateSlider"));
        dilateSlider->setOrientation(Qt::Horizontal);
        dilateSlider->setTickPosition(QSlider::TicksBelow);
        dilateSlider->setTickInterval(10);

        gridLayout->addWidget(dilateSlider, 2, 0, 1, 1);

        thresholdHighSlider = new QSlider(layoutWidget);
        thresholdHighSlider->setObjectName(QStringLiteral("thresholdHighSlider"));
        thresholdHighSlider->setOrientation(Qt::Horizontal);
        thresholdHighSlider->setTickPosition(QSlider::TicksBelow);
        thresholdHighSlider->setTickInterval(10);

        gridLayout->addWidget(thresholdHighSlider, 1, 0, 1, 1);

        thresholdLowSlider = new QSlider(layoutWidget);
        thresholdLowSlider->setObjectName(QStringLiteral("thresholdLowSlider"));
        thresholdLowSlider->setOrientation(Qt::Horizontal);
        thresholdLowSlider->setTickPosition(QSlider::TicksBelow);
        thresholdLowSlider->setTickInterval(10);

        gridLayout->addWidget(thresholdLowSlider, 0, 0, 1, 1);

        erodeLabelVL = new QLabel(layoutWidget);
        erodeLabelVL->setObjectName(QStringLiteral("erodeLabelVL"));

        gridLayout->addWidget(erodeLabelVL, 5, 1, 1, 1);

        dilateLabelVL = new QLabel(layoutWidget);
        dilateLabelVL->setObjectName(QStringLiteral("dilateLabelVL"));

        gridLayout->addWidget(dilateLabelVL, 4, 1, 1, 1);

        erodeSliderVL = new QSlider(layoutWidget);
        erodeSliderVL->setObjectName(QStringLiteral("erodeSliderVL"));
        erodeSliderVL->setOrientation(Qt::Horizontal);
        erodeSliderVL->setTickPosition(QSlider::TicksBelow);
        erodeSliderVL->setTickInterval(10);

        gridLayout->addWidget(erodeSliderVL, 5, 0, 1, 1);

        dilateSliderVL = new QSlider(layoutWidget);
        dilateSliderVL->setObjectName(QStringLiteral("dilateSliderVL"));
        dilateSliderVL->setOrientation(Qt::Horizontal);
        dilateSliderVL->setTickPosition(QSlider::TicksBelow);
        dilateSliderVL->setTickInterval(10);

        gridLayout->addWidget(dilateSliderVL, 4, 0, 1, 1);


        gridLayout_2->addWidget(groupParameters, 0, 2, 1, 2);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(750, 0));
        groupBox_4 = new QGroupBox(groupBox_5);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(540, 40, 201, 201));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 40, 181, 130));
        gridLayout_5 = new QGridLayout(layoutWidget1);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_5->addWidget(pushButton, 2, 0, 1, 1);

        radioButton_10 = new QRadioButton(layoutWidget1);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));

        gridLayout_5->addWidget(radioButton_10, 1, 0, 1, 1);

        radioButton_9 = new QRadioButton(layoutWidget1);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));

        gridLayout_5->addWidget(radioButton_9, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 40, 271, 201));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 30, 253, 154));
        gridLayout_3 = new QGridLayout(layoutWidget2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        radioButton_5 = new QRadioButton(layoutWidget2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(20, 280, 131, 17));
        radioButton_5->setAutoFillBackground(true);
        radioButton_5->setAutoRepeat(true);
        radioButton_6 = new QRadioButton(groupParameters);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(20, 310, 121, 17));
        radioButton_6->setAutoFillBackground(true);
        radioButton_6->setAutoRepeat(true);
        radioButton_7 = new QRadioButton(groupParameters);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(20, 340, 131, 17));
        radioButton_7->setAutoFillBackground(true);
        radioButton_7->setAutoRepeat(true);
        radioButton_8 = new QRadioButton(groupParameters);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(20, 370, 101, 17));
        radioButton_8->setAutoFillBackground(true);
        radioButton_8->setAutoRepeat(true);

        gridLayout_3->addWidget(radioButton_7, 2, 0, 1, 1);

        radioButton_8 = new QRadioButton(layoutWidget2);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));

        gridLayout_3->addWidget(radioButton_8, 3, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(290, 40, 251, 201));
        layoutWidget3 = new QWidget(groupBox_3);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 30, 226, 154));
        gridLayout_4 = new QGridLayout(layoutWidget3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        radioButton_2 = new QRadioButton(layoutWidget3);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout_4->addWidget(radioButton_2, 1, 0, 1, 1);

        radioButton_4 = new QRadioButton(layoutWidget3);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        gridLayout_4->addWidget(radioButton_4, 3, 0, 1, 1);

        radioButton_3 = new QRadioButton(layoutWidget3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        gridLayout_4->addWidget(radioButton_3, 2, 0, 1, 1);

        radioButton = new QRadioButton(layoutWidget3);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout_4->addWidget(radioButton, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_5, 1, 2, 1, 2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMouseTracking(false);
        OutputTable = new QTableWidget(groupBox);
        if (OutputTable->columnCount() < 4)
            OutputTable->setColumnCount(4);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        OutputTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        OutputTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        OutputTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        OutputTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (OutputTable->rowCount() < 3)
            OutputTable->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        OutputTable->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        OutputTable->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        OutputTable->setVerticalHeaderItem(2, __qtablewidgetitem6);
        OutputTable->setObjectName(QStringLiteral("OutputTable"));
        OutputTable->setGeometry(QRect(20, 30, 681, 231));
        OutputTable->setShowGrid(true);
        OutputTable->setGridStyle(Qt::SolidLine);
        OutputTable->setSortingEnabled(false);
        OutputTable->setWordWrap(true);
        OutputTable->setCornerButtonEnabled(true);
        OutputTable->horizontalHeader()->setVisible(true);
        OutputTable->horizontalHeader()->setCascadingSectionResizes(false);
        OutputTable->horizontalHeader()->setDefaultSectionSize(120);
        OutputTable->horizontalHeader()->setHighlightSections(true);
        OutputTable->horizontalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(groupBox, 2, 2, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1178, 38));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOpen = new QMenu(menuFile);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(menuOpen->menuAction());
        menuOpen->addAction(actionStream);
        menuOpen->addAction(actionFile);
        menuView->addAction(actionDebug_Layout);
        menuView->addAction(actionRelease_Layout);

        retranslateUi(MainWindow);
        QObject::connect(dilateSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onDilateValueChanged(int)));
        QObject::connect(erodeSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onErodeValueChanged(int)));
        QObject::connect(thresholdHighSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onHighThValueChanged(int)));
        QObject::connect(thresholdLowSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onLowThValueChanged(int)));
        QObject::connect(MapDisplay, SIGNAL(linkActivated(QString)), MainWindow, SLOT(onStart()));
        QObject::connect(menubar, SIGNAL(triggered(QAction*)), MainWindow, SLOT(slotOpen()));
        QObject::connect(dilateSliderVL, SIGNAL(valueChanged(int)), MainWindow, SLOT(onErodeValueChangedVL(int)));
        QObject::connect(erodeSliderVL, SIGNAL(valueChanged(int)), MainWindow, SLOT(onDilateValueChangedVL(int)));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(onStart()));
        QObject::connect(radioButton_2, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonThreshold(bool)));
        QObject::connect(radioButton_3, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonErode(bool)));
        QObject::connect(radioButton_4, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonDilate(bool)));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonOriginalImage(bool)));
        QObject::connect(radioButton_8, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView4(bool)));
        QObject::connect(radioButton_7, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView3(bool)));
        QObject::connect(radioButton_5, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView1(bool)));
        QObject::connect(radioButton_6, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView2(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionStream->setText(QApplication::translate("MainWindow", "Stream", Q_NULLPTR));
        actionFile->setText(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        actionDebug_Layout->setText(QApplication::translate("MainWindow", "Debug Layout", Q_NULLPTR));
        actionRelease_Layout->setText(QApplication::translate("MainWindow", "Release Layout", Q_NULLPTR));
        MapDisplay->setText(QString());
        groupParameters->setTitle(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        lowThLabel->setText(QApplication::translate("MainWindow", "Threshold Low", Q_NULLPTR));
        highThLabel->setText(QApplication::translate("MainWindow", "Threshold High", Q_NULLPTR));
        erodeLabel->setText(QApplication::translate("MainWindow", "Erode", Q_NULLPTR));
        dilateLabel->setText(QApplication::translate("MainWindow", "Dilate", Q_NULLPTR));
        erodeLabelVL->setText(QApplication::translate("MainWindow", "VL Erode", Q_NULLPTR));
        dilateLabelVL->setText(QApplication::translate("MainWindow", "VL Dilate", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Options", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        radioButton_10->setText(QApplication::translate("MainWindow", "Thermal", Q_NULLPTR));
        radioButton_9->setText(QApplication::translate("MainWindow", "Visual Image", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "View Selection", Q_NULLPTR));
        radioButton_5->setText(QApplication::translate("MainWindow", "Lane 1", Q_NULLPTR));
        radioButton_6->setText(QApplication::translate("MainWindow", "Lane 2", Q_NULLPTR));
        radioButton_7->setText(QApplication::translate("MainWindow", "Lane 3", Q_NULLPTR));
        radioButton_8->setText(QApplication::translate("MainWindow", "Lane 4", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Process Frame", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MainWindow", "Thresholded Image", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("MainWindow", "Dilated Image", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("MainWindow", "Eroded Image", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MainWindow", "Original Image", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Output Values", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = OutputTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Lane 1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = OutputTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Lane 2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = OutputTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Lane 3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = OutputTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Lane 4", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = OutputTable->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Number of Cars", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = OutputTable->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Average Speed", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = OutputTable->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Time Stopped", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
