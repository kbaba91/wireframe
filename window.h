#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QOpenGLWidget>

class QSlider;
class QPushButton;

class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(MainWindow *mw, QOpenGLWidget * widget);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void changeMesh();

private:
    QSlider *createSlider();
    QOpenGLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QPushButton *dockBtn;
    MainWindow *mainWindow;
};

#endif
