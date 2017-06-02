#ifndef SHAPE
#define SHAPE

#include "mesh.h"
#include "triangle.h"
#include "vertex.h"
#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class Shape
{
public:
    Shape();
    static SimpleMesh::Mesh * mesh;
    const GLfloat *constData() const { return m_data.constData(); }
    const GLfloat *constInvData() const { return m_inv_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

private:
    void render(SimpleMesh::Triangle f);
    void add(SimpleMesh::Vertex &vertex, float * normal);

    QVector<GLfloat> m_data;
    QVector<GLfloat> m_inv_data;
    int m_count;
};

#endif // SHAPE
