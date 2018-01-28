#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T09:31:25
#
#-------------------------------------------------

QT       += core gui opengl

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += OpenNI-Linux-x64-2.2/Include/
LIBS += -L/usr/local/lib -lglut -lGLU -lGL -lopencv_features2d -lopencv_calib3d -lopencv_videoio -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_video
LIBS += -L /OpenNI-Linux-x64-2.2/Redist/ -lOpenNI2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RealiteAugmenteTp1
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    opencvwindow.cpp \
    mainwindow.cpp \
    gldisplay.cpp \
    mesh.cpp

HEADERS  += \
    opencvwindow.h \
    mainwindow.h \
    gldisplay.h \
    mesh.h

FORMS += \
    mainwindow.ui

