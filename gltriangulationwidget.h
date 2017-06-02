#ifndef GLTRIANGULATIONWIDGET
#define GLTRIANGULATIONWIDGET

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "shape.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLTriangulationWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLTriangulationWidget(QWidget *parent = 0);
    ~GLTriangulationWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public Q_SLOTS:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

Q_SIGNALS:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void setupVertexAttribs();
    void setupInverseVertexAttribs();

    bool m_core;
    int m_xRot;
    int m_yRot;
    int m_zRot;
    QPoint m_lastPos;
    Shape m_shape;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_shapeVbo;
    QOpenGLShaderProgram *m_program;
    QOpenGLBuffer m_inverseVbo;
    QOpenGLShaderProgram *m_inverseProgram;
    QOpenGLBuffer m_interestVbo;
    QOpenGLShaderProgram *m_interestProgram;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    bool m_transparent;
};

#endif
