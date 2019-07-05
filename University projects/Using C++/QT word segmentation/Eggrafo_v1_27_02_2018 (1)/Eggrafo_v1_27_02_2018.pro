#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T11:38:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= app_bundle

TARGET = Eggrafo_v1_27_02_2018
TEMPLATE = app

INCLUDEPATH += C:\OpenCV\opencv\release\install\include

LIBS += C:\OpenCV\opencv\release\bin\libopencv_core320.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_highgui320.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_imgcodecs320.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_imgproc320.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_calib3d320.dll


SOURCES += main.cpp\
        mainwindow.cpp \
    Util.cpp

HEADERS  += mainwindow.h \
    Util.h

FORMS    += mainwindow.ui
