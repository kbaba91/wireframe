#include "glwidget.h"
#include "gltriangulationwidget.h"
#include "window.h"
#include "mainwindow.h"
#include "offreader.h"
#include "mesh.h"
#include "shape.h"
#include <iostream>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>

Window::Window(MainWindow *mw, QOpenGLWidget *widget = 0)
    : mainWindow(mw)
{
    cout << "OK" << endl;
    if (widget){
        glWidget = widget;
    }
    else{
        glWidget = new GLWidget();
    }
    cout << "OK" << endl;
    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    cout << "OK" << endl;
    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));
    cout << "OK" << endl;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);
    container->addWidget(xSlider);
    container->addWidget(ySlider);
    container->addWidget(zSlider);
    cout << "OK3" << endl;
    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    dockBtn = new QPushButton(tr("Change Mesh"), this);
    connect(dockBtn, SIGNAL(clicked()), this, SLOT(changeMesh()));
    mainLayout->addWidget(dockBtn);

    setLayout(mainLayout);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);
    cout << "OK4" << endl;
    setWindowTitle(tr("Mesh Viewer"));
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::changeMesh()
{
    QString offFilename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Object Files (*.off *.obj)"));
    QFile file(offFilename);
    int canOpen = file.open(QIODevice::ReadOnly);
    file.close();
    if (!canOpen){
        QMessageBox::information(0, "error", file.errorString());
    }
    else {
        //Set the central widget
        SimpleMesh::IO::OFFReader reader(offFilename.toUtf8().constData());
        Shape::mesh = new SimpleMesh::Mesh();
        reader.read_mesh(*Shape::mesh);
        glWidget = new GLTriangulationWidget();
        Window * window = new Window(mainWindow, glWidget);
        cout << "OK5" << endl;
        mainWindow->setCentralWidget(window);
        cout << "OK6" << endl;
        setParent(0);
    }

    /*
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
    */
}

