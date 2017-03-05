#pragma once

#include <QWidget>
#include "ui_QtGui.h"

class QtGui : public QWidget
{
	Q_OBJECT

public:
	QtGui(QWidget *parent = Q_NULLPTR);
	~QtGui();

private:
	Ui::QtGui ui;
};
