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
//    void setContoursPoint(std::vector<std::vector<cv::Point> > * v);
    std::vector<std::vector<Point3f> > & getContours();



protected:

private:

    std::vector<std::vector<Point3f> > contours;

};

#endif // GLDISPLAY_H
