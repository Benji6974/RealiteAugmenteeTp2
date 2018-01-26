#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "opencvwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void renderOpenCV();

private:
    Ui::MainWindow *ui;
    OpenCVwindow opencvW;
};

#endif // MAINWINDOW_H
