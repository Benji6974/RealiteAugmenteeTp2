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
    glScalef(0.5,0.5,0);
    glBegin(GL_LINES);
    //std::vector<QVector3D> test = *contours;
    //std::cout<<contours->size()<<std::endl;
    if((*contours).size() != 0){
        for(unsigned int j = 0; j < contours->size() - 1; j++)
        {
            for(unsigned int i = 1; i < (*contours)[j].size() - 1;i++)
            {
    //                std::cout<<"contours : "<<test[i].x()<<std::endl;

                    glVertex3f(2 * ((*contours)[j][i].x() - tx)/tx, 4 * ((*contours)[j][i].y() + ty/2)/ty, (*contours)[j][i].z());
                    glVertex3f(2 * ((*contours)[j][i-1].x() - tx)/tx,4 * ((*contours)[j][i-1].y() + ty/2)/ty, (*contours)[j][i-1].z());


            }
        }
    }
    glEnd();
}

void GLDisplay::resizeGL(int w, int h)

{

    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

void GLDisplay::setContoursPoint(std::vector<std::vector<QVector3D> > * v){
    contours = v;
    update();
}

void GLDisplay::setTxTy(float x, float y)
{
    tx = x;
    ty = y;
}
