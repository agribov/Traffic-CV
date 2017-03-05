/********************************************************************************
** Form generated from reading UI file 'QtGui.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI_H
#define UI_QTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGui
{
public:

    void setupUi(QWidget *QtGui)
    {
        if (QtGui->objectName().isEmpty())
            QtGui->setObjectName(QStringLiteral("QtGui"));
        QtGui->resize(400, 300);

        retranslateUi(QtGui);

        QMetaObject::connectSlotsByName(QtGui);
    } // setupUi

    void retranslateUi(QWidget *QtGui)
    {
        QtGui->setWindowTitle(QApplication::translate("QtGui", "QtGui", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGui: public Ui_QtGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_H
