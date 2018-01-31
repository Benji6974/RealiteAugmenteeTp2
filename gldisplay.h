#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/glut.h>
#include <OpenNI.h>

#include "opencvwindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <OpenNI.h>
#include<list>

using namespace openni;


class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);
    virtual void paintGL();
    void initializeGL();
    void resizeGL(int w, int h);
    Device device;        // Software object for the physical device i.e.

                             // PrimeSense Device Class

   VideoStream ir;       // IR VideoStream Class Object

   VideoFrameRef irf;    //IR VideoFrame Class Object

   VideoMode vmode;      // VideoMode Object

   Status rc;

   Mat frame;     // OpenCV Matrix Object, also used to store images
   Mat frame2;
   int h, w;               // Height and Width of the IR VideoFrame

   std::list<uint16_t*> images;





protected:

private:
    OpenCVwindow cvWindow;

    //cv::Mat frame;
    cv::VideoCapture vid;
};

#endif // GLDISPLAY_H
