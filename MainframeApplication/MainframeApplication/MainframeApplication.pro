# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = MainframeApplication
DESTDIR = ../Debug
QT += core widgets gui
CONFIG += debug console
DEFINES += _CONSOLE
INCLUDEPATH += ../../../../../../../../Program Files/OpenCV 3-1/opencv/build/include \
    $(NOINHERIT)
LIBS += -L"../../../../../../../../Program Files/OpenCV 3-1/opencv/build/x64/vc14/lib" \
    -L"$(NOINHERIT)" \
    -lopencv_world310d
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(MainframeApplication.pri)
