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
    //std::cout<<contours->size()<<std::endl;
    if(contours->size() != 0){
        for(int i = 1; i < contours->size() - 1;i++)
        {
                std::cout<<"contours : "<<contours[i].x()<<std::endl;
//                glBegin(GL_LINES);
//                glVertex3f(contours[i].x(), contours[i].y(), contours[i].z());
//                glVertex3f(contours[i-1].x(), contours[i-1].y(), contours[i-1].z());
//                glEnd();

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

void GLDisplay::setContoursPoint(std::vector<QVector3D> * v){
    contours = v;
    update();
}

