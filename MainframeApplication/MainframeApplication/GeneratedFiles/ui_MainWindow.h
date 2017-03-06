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
    QAction *actionStart_Stream;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupParameters;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSlider *thresholdLowSlider;
    QSlider *erodeSlider;
    QLabel *lowThLabel;
    QSlider *thresholdHighSlider;
    QLabel *erodeLabel;
    QSlider *dilateSlider;
    QLabel *highThLabel;
    QLabel *dilateLabel;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QPushButton *pushButton;
    CQtOpenCVViewerGl *bottomFrameWidget;
    CQtOpenCVViewerGl *topFrameWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(809, 593);
        MainWindow->setAcceptDrops(false);
        MainWindow->setDocumentMode(false);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionStart_Stream = new QAction(MainWindow);
        actionStart_Stream->setObjectName(QStringLiteral("actionStart_Stream"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupParameters = new QGroupBox(centralwidget);
        groupParameters->setObjectName(QStringLiteral("groupParameters"));
        groupParameters->setEnabled(true);
        groupParameters->setCheckable(false);
        widget = new QWidget(groupParameters);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 27, 281, 161));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        thresholdLowSlider = new QSlider(widget);
        thresholdLowSlider->setObjectName(QStringLiteral("thresholdLowSlider"));
        thresholdLowSlider->setOrientation(Qt::Horizontal);
        thresholdLowSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(thresholdLowSlider, 0, 0, 1, 1);

        erodeSlider = new QSlider(widget);
        erodeSlider->setObjectName(QStringLiteral("erodeSlider"));
        erodeSlider->setTracking(true);
        erodeSlider->setOrientation(Qt::Horizontal);
        erodeSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(erodeSlider, 3, 0, 1, 1);

        lowThLabel = new QLabel(widget);
        lowThLabel->setObjectName(QStringLiteral("lowThLabel"));

        gridLayout->addWidget(lowThLabel, 0, 1, 1, 1);

        thresholdHighSlider = new QSlider(widget);
        thresholdHighSlider->setObjectName(QStringLiteral("thresholdHighSlider"));
        thresholdHighSlider->setOrientation(Qt::Horizontal);
        thresholdHighSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(thresholdHighSlider, 1, 0, 1, 1);

        erodeLabel = new QLabel(widget);
        erodeLabel->setObjectName(QStringLiteral("erodeLabel"));

        gridLayout->addWidget(erodeLabel, 3, 1, 1, 1);

        dilateSlider = new QSlider(widget);
        dilateSlider->setObjectName(QStringLiteral("dilateSlider"));
        dilateSlider->setOrientation(Qt::Horizontal);
        dilateSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(dilateSlider, 2, 0, 1, 1);

        highThLabel = new QLabel(widget);
        highThLabel->setObjectName(QStringLiteral("highThLabel"));

        gridLayout->addWidget(highThLabel, 1, 1, 1, 1);

        dilateLabel = new QLabel(widget);
        dilateLabel->setObjectName(QStringLiteral("dilateLabel"));

        gridLayout->addWidget(dilateLabel, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupParameters, 0, 1, 1, 2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));

        gridLayout_2->addWidget(groupBox, 1, 2, 1, 1);

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


        gridLayout_2->addWidget(groupBox_2, 1, 1, 1, 1);

        bottomFrameWidget = new CQtOpenCVViewerGl(centralwidget);
        bottomFrameWidget->setObjectName(QStringLiteral("bottomFrameWidget"));

        gridLayout_2->addWidget(bottomFrameWidget, 1, 0, 1, 1);

        topFrameWidget = new CQtOpenCVViewerGl(centralwidget);
        topFrameWidget->setObjectName(QStringLiteral("topFrameWidget"));

        gridLayout_2->addWidget(topFrameWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 809, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionStart_Stream);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(onStart()));
        QObject::connect(dilateSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onDilateValueChanged(int)));
        QObject::connect(erodeSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onErodeValueChanged(int)));
        QObject::connect(thresholdHighSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onHighThValueChanged(int)));
        QObject::connect(thresholdLowSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onLowThValueChanged(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionStart_Stream->setText(QApplication::translate("MainWindow", "Start Stream", Q_NULLPTR));
        groupParameters->setTitle(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        lowThLabel->setText(QApplication::translate("MainWindow", "Threshold Low", Q_NULLPTR));
        erodeLabel->setText(QApplication::translate("MainWindow", "Erode", Q_NULLPTR));
        highThLabel->setText(QApplication::translate("MainWindow", "Threshold High", Q_NULLPTR));
        dilateLabel->setText(QApplication::translate("MainWindow", "Dilate", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Output Values", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "GroupBox", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MainWindow", "Original Image", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MainWindow", "Thresholded Image", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("MainWindow", "Eroded Image", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("MainWindow", "Dilated Image", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
