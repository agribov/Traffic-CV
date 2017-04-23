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
#include <QtWidgets/QVBoxLayout>
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
    QLabel *mylabel;
    CQtOpenCVViewerGl *bottomFrameWidget;
    CQtOpenCVViewerGl *topFrameWidget;
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
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QPushButton *pushButton;
    QGroupBox *groupBox;
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
        MainWindow->resize(1013, 678);
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
        mylabel = new QLabel(centralwidget);
        mylabel->setObjectName(QStringLiteral("mylabel"));

        gridLayout_2->addWidget(mylabel, 2, 0, 1, 1);

        bottomFrameWidget = new CQtOpenCVViewerGl(centralwidget);
        bottomFrameWidget->setObjectName(QStringLiteral("bottomFrameWidget"));

        gridLayout_2->addWidget(bottomFrameWidget, 1, 0, 1, 1);

        topFrameWidget = new CQtOpenCVViewerGl(centralwidget);
        topFrameWidget->setObjectName(QStringLiteral("topFrameWidget"));

        gridLayout_2->addWidget(topFrameWidget, 0, 0, 1, 1);

        groupParameters = new QGroupBox(centralwidget);
        groupParameters->setObjectName(QStringLiteral("groupParameters"));
        groupParameters->setEnabled(true);
        groupParameters->setCheckable(false);
        layoutWidget = new QWidget(groupParameters);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 27, 281, 254));
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

        gridLayout->addWidget(erodeSlider, 3, 0, 1, 1);

        dilateSlider = new QSlider(layoutWidget);
        dilateSlider->setObjectName(QStringLiteral("dilateSlider"));
        dilateSlider->setOrientation(Qt::Horizontal);
        dilateSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(dilateSlider, 2, 0, 1, 1);

        thresholdHighSlider = new QSlider(layoutWidget);
        thresholdHighSlider->setObjectName(QStringLiteral("thresholdHighSlider"));
        thresholdHighSlider->setOrientation(Qt::Horizontal);
        thresholdHighSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(thresholdHighSlider, 1, 0, 1, 1);

        thresholdLowSlider = new QSlider(layoutWidget);
        thresholdLowSlider->setObjectName(QStringLiteral("thresholdLowSlider"));
        thresholdLowSlider->setOrientation(Qt::Horizontal);
        thresholdLowSlider->setTickPosition(QSlider::TicksBelow);

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

        gridLayout->addWidget(erodeSliderVL, 5, 0, 1, 1);

        dilateSliderVL = new QSlider(layoutWidget);
        dilateSliderVL->setObjectName(QStringLiteral("dilateSliderVL"));
        dilateSliderVL->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(dilateSliderVL, 4, 0, 1, 1);

        radioButton_5 = new QRadioButton(groupParameters);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(20, 280, 131, 17));
        radioButton_6 = new QRadioButton(groupParameters);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(20, 310, 121, 17));
        radioButton_7 = new QRadioButton(groupParameters);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(20, 340, 131, 17));
        radioButton_8 = new QRadioButton(groupParameters);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(20, 370, 101, 17));

        gridLayout_2->addWidget(groupParameters, 0, 1, 2, 2);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout->addWidget(radioButton_4);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        gridLayout_2->addWidget(groupBox_2, 2, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));

        gridLayout_2->addWidget(groupBox, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1013, 21));
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
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(onStart()));
        QObject::connect(dilateSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onDilateValueChanged(int)));
        QObject::connect(erodeSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onErodeValueChanged(int)));
        QObject::connect(thresholdHighSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onHighThValueChanged(int)));
        QObject::connect(thresholdLowSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onLowThValueChanged(int)));
        QObject::connect(radioButton_2, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonThreshold(bool)));
        QObject::connect(radioButton_3, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonErode(bool)));
        QObject::connect(radioButton_4, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonDilate(bool)));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), MainWindow, SLOT(buttonOriginalImage(bool)));
        QObject::connect(mylabel, SIGNAL(linkActivated(QString)), MainWindow, SLOT(onStart()));
        QObject::connect(radioButton_5, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView1(bool)));
        QObject::connect(radioButton_7, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView3(bool)));
        QObject::connect(radioButton_6, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView2(bool)));
        QObject::connect(radioButton_8, SIGNAL(clicked(bool)), MainWindow, SLOT(buttonView4(bool)));
        QObject::connect(menubar, SIGNAL(triggered(QAction*)), MainWindow, SLOT(slotOpen()));
        QObject::connect(dilateSliderVL, SIGNAL(valueChanged(int)), MainWindow, SLOT(onErodeValueChangedVL(int)));
        QObject::connect(erodeSliderVL, SIGNAL(valueChanged(int)), MainWindow, SLOT(onDilateValueChangedVL(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionStream->setText(QApplication::translate("MainWindow", "Stream", Q_NULLPTR));
        actionFile->setText(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        actionDebug_Layout->setText(QApplication::translate("MainWindow", "Debug Layout", Q_NULLPTR));
        actionRelease_Layout->setText(QApplication::translate("MainWindow", "Release Layout", Q_NULLPTR));
        mylabel->setText(QString());
        groupParameters->setTitle(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        lowThLabel->setText(QApplication::translate("MainWindow", "Threshold Low", Q_NULLPTR));
        highThLabel->setText(QApplication::translate("MainWindow", "Threshold High", Q_NULLPTR));
        erodeLabel->setText(QApplication::translate("MainWindow", "Erode", Q_NULLPTR));
        dilateLabel->setText(QApplication::translate("MainWindow", "Dilate", Q_NULLPTR));
        erodeLabelVL->setText(QApplication::translate("MainWindow", "VL Erode", Q_NULLPTR));
        dilateLabelVL->setText(QApplication::translate("MainWindow", "VL Dilate", Q_NULLPTR));
        radioButton_5->setText(QApplication::translate("MainWindow", "View 1 (Bottom Right)", Q_NULLPTR));
        radioButton_6->setText(QApplication::translate("MainWindow", "View 2 (Bottom Left)", Q_NULLPTR));
        radioButton_7->setText(QApplication::translate("MainWindow", "View 3 (Top Right)", Q_NULLPTR));
        radioButton_8->setText(QApplication::translate("MainWindow", "View 4 (Top Left)", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Debug Output", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MainWindow", "Original Image", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MainWindow", "Thresholded Image", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("MainWindow", "Eroded Image", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("MainWindow", "Dilated Image", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Output Values", Q_NULLPTR));
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
