#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "window.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    if (!centralWidget())
        setCentralWidget(new Window(this, 0));
    else
        QMessageBox::information(0, tr("Cannot add new window"), tr("Already occupied. Undock first."));

}

MainWindow::~MainWindow()
{
    delete ui;
}
