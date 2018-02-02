#include "gldisplay.h"

GLDisplay::GLDisplay(QWidget *parent) :

    QGLWidget(parent)

{


     glLoadIdentity();

}

void GLDisplay::initializeGL()

{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0,1.0,0.0);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    if(contours.size() != 0){
        for(unsigned int i = 0; i < contours.size() - 1;i++)
        {
            for(unsigned int j = 1; j < contours[i].size() - 1; j++)
            {
                glBegin(GL_LINES);
                glVertex3f(contours[i][j].x, contours[i][j].y, contours[i][j].z);
                glVertex3f(contours[i][j-1].x, contours[i][j-1].y, contours[i][j-1].z);
                glEnd();
            }
        }
    }
}

void GLDisplay::resizeGL(int w, int h)

{

    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

//void GLDisplay::setContoursPoint(std::vector<std::vector<cv::Point> > * v){
//    contours = v;
//    update();
//}

std::vector<std::vector<Point3f> > & GLDisplay::getContours()
{
    return contours;
}

