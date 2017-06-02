#include "shape.h"
#include "mesh.h"
#include "vertex.h"
#include "triangle.h"
#include <qmath.h>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <qmath.h>
#include <qopengl.h>
#include <QVector>
#include <QVector3D>

using namespace std;

SimpleMesh::Mesh * Shape::mesh;

Shape::Shape()
    : m_count(0)
{
    //Draw faces
    m_data.resize((*mesh).get_number_triangles() * 3 * 6);
    for(int i = 0; i<(*mesh).get_number_triangles(); i++){
        render((*mesh).get_triangles()[i]);
    }
}

void Shape::add(SimpleMesh::Vertex & vertex, float * normal)
{
    //Add regular faces
    GLfloat *p = m_data.data() + m_count;
    *p++ = (vertex.x() / (*mesh).get_diagonal());
    *p++ = (vertex.y() / (*mesh).get_diagonal());
    *p++ = (vertex.z() / (*mesh).get_diagonal());
    *p++ = normal[0];
    *p++ = normal[1];
    *p++ = normal[2];

    /*
    //Add inverse faces
    p = m_inv_data.data() + m_count;
    *p++ = (vertex.x() / (*mesh).get_diagonal());
    *p++ = (vertex.y() / (*mesh).get_diagonal());
    *p++ = (vertex.z() / (*mesh).get_diagonal());
    *p++ = -normal[0];
    *p++ = -normal[1];
    *p++ = -normal[2];
    */

    m_count += 6;
}

void Shape::render(SimpleMesh::Triangle f)
{
    //Add vertices
    add((*mesh).get_vertices()[f.get_vertex_at(0)],f.get_normal());
    add((*mesh).get_vertices()[f.get_vertex_at(1)],f.get_normal());
    add((*mesh).get_vertices()[f.get_vertex_at(2)],f.get_normal());
}
