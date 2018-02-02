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

std::vector<std::vector<Point3f> > & MainWindow::getContours()
{
    return ui->widget->getContours();
}

void MainWindow::updateGL(){
    ui->widget->update();
}
