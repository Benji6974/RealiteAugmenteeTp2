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
    //std::vector<QVector3D> test = *contours;
    //std::cout<<contours->size()<<std::endl;
    if(contours->size() != 0){
        for(int i = 1; i < contours->size() - 1;i++)
        {
//                std::cout<<"contours : "<<test[i].x()<<std::endl;
                glBegin(GL_LINES);
                glVertex3f((*contours)[i].x()/1000, (*contours)[i].y()/1000, (*contours)[i].z()/1000);
                glVertex3f((*contours)[i-1].x()/1000,(*contours)[i-1].y()/1000, (*contours)[i-1].z()/1000);
                glEnd();

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

