#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::renderOpenCV()
{

}

void MainWindow::setContours(std::vector<QVector3D> * v)
{
    ui->widget->setContoursPoint(v);
}

void MainWindow::updateGL(){
    ui->widget->update();
}
