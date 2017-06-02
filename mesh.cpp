#include <cmath>
#include <iostream>
#include "mesh.h"

namespace SimpleMesh{

Mesh::Mesh()
{
    vertices = 0;
    triangles = 0;
    num_vertices = 0;
    num_triangles = 0;
    diag = -1.0;
    flag_color = false;
    flag_normals = false;
}

Mesh::~Mesh()
{
    clean_mesh();
}

void Mesh::clean_mesh(){
    if(vertices){
        delete[] vertices;
        vertices = 0;
        num_vertices = 0;
    }

    if(triangles){
        delete[] triangles;
        triangles = 0;
        num_triangles = 0;
    }

    diag = -1.0;
}

float Mesh::get_diagonal(){

    if(diag < 0.0){
        xmin = ymin = zmin = 1.0E30F;
        xmax = ymax = zmax = -1.0E30F;

        for(int i = 0; i < num_vertices; i++){
            if(vertices[i].x() < xmin)
                xmin = vertices[i].x();
            else if(vertices[i].x() > xmax)
                xmax = vertices[i].x();

            if(vertices[i].y() < ymin)
                ymin = vertices[i].y();
            else if(vertices[i].y() > ymax)
                ymax = vertices[i].y();

            if(vertices[i].z() < zmin)
                zmin = vertices[i].z();
            else if(vertices[i].z() > zmax)
                zmax = vertices[i].z();
       }

       diag = sqrt((xmax - xmin)*(xmax - xmin) + (ymax - ymin)*(ymax - ymin) + (zmax - zmin)*(zmax - zmin));
    }

    return diag;
}

float Mesh::get_area(){
    float area = 0.0;

    for(int i = 0; i < num_triangles; i++){
        std::vector<unsigned int> indices = triangles[i].get_vertices();
        float x1 = vertices[indices[0]].x();
        float y1 = vertices[indices[0]].y();
        float z1 = vertices[indices[0]].z();

        float x2 = vertices[indices[1]].x();
        float y2 = vertices[indices[1]].y();
        float z2 = vertices[indices[1]].z();

        float x3 = vertices[indices[2]].x();
        float y3 = vertices[indices[2]].y();
        float z3 = vertices[indices[2]].z();

        float det1 = x1*y2 + x2*y3 + x3*y1 - x3*y2 - x2*y1 - x1*y3;
        float det2 = y1*z2 + y2*z3 + y3*z1 - y3*z2 - y2*z1 - y1*z3;
        float det3 = z1*x2 + z2*x3 + z3*x1 - z3*x2 - z2*x1 - z1*x3;

        area = area + 0.5*sqrt(det1*det1 + det2*det2 + det3*det3);
    }

    return area;
}


void Mesh::compute_normals()
{
    //Compute normals for faces
    if(flag_normals)
        for(unsigned int i = 0; i < num_triangles; i++){
            float nx = 0.0, ny = 0.0, nz = 0.0;
            vector<unsigned int> vert = triangles[i].get_vertices();
            unsigned int ind1 = 2;
            for(unsigned int j = 0; j < 3; j++){
                int ind2 = j;
                nx += (vertices[vert[ind1]].y() - vertices[vert[ind2]].y())*(vertices[vert[ind1]].z() + vertices[vert[ind2]].z());
                ny += (vertices[vert[ind1]].z() - vertices[vert[ind2]].z())*(vertices[vert[ind1]].x() + vertices[vert[ind2]].x());
                nz += (vertices[vert[ind1]].x() - vertices[vert[ind2]].x())*(vertices[vert[ind1]].y() + vertices[vert[ind2]].y());
                ind1 = ind2;
            }

            float magnitude = sqrt(nx*nx + ny*ny + nz*nz);
            if(magnitude > 1.0E-6){
                nx /= magnitude;
                ny /= magnitude;
                nz /= magnitude;
            }
            triangles[i].set_normal(nx, ny, nz);
        }

        //Compute normals for vertices
        for(unsigned int i = 0; i < num_vertices; i++){
            vector<unsigned int> fac = vertices[i].get_triangles();
            float nx = 0.0, ny = 0.0, nz = 0.0;
            for(unsigned int j = 0; j < fac.size(); j++){
                nx += triangles[fac[j]].nx();
                ny += triangles[fac[j]].ny();
                nz += triangles[fac[j]].nz();
            }

            nx /= fac.size();
            ny /= fac.size();
            nz /= fac.size();

            float magnitude = sqrt(nx*nx + ny*ny + nz*nz);
            if(magnitude > 1.0E-6){
                nx /= magnitude;
                ny /= magnitude;
                nz /= magnitude;
            }
//            std::cout << "-" << nx << "," << ny << "," << nz << std::endl;
            vertices[i].set_normal(nx, ny, nz);
        }
}

void Mesh::set_number_vertices(unsigned int nv)
{
    num_vertices = nv;
    cout << "OK" << endl;
    vertices = new Vertex[num_vertices];
    cout << "OK" << endl;
}

void Mesh::set_number_triangles(unsigned int nt)
{
    num_triangles = nt;
    triangles = new Triangle[num_triangles];
}

void Mesh::add_vertex(unsigned int pos, float x, float y, float z)
{
    vertices[pos].set_vertex(x, y, z);
    vertices[pos].set_index(pos);
}

void Mesh::set_vertex(unsigned int pos, float x, float y, float z)
{
    vertices[pos].setX(x);
    vertices[pos].setY(y);
    vertices[pos].setZ(z);
}

//void Mesh::update_normal(unsigned int pos){
//    float x = 0.0;
//    float y = 0.0;
//    float z = 0.0;
//    if (vertices[pos].getFaces().size() > 0){
//        for (unsigned i = 0; i< vertices[pos].getFaces().size(); i++){
//            x += faces[vertices[pos].getFaces()[i]].normal[0];
//            y += faces[vertices[pos].getFaces()[i]].normal[1];
//            z += faces[vertices[pos].getFaces()[i]].normal[2];
//        }
//        x /= (float)vertices[pos].getFaces().size();
//        y /= (float)vertices[pos].getFaces().size();
//        z /= (float)vertices[pos].getFaces().size();
//    }
//    vertices[pos].normal[0] = x;
//    vertices[pos].normal[1] = y;
//    vertices[pos].normal[2] = z;
//}

void Mesh::add_vertex(unsigned int pos, Vertex v)
{
    vertices[pos].set_vertex(v.x(), v.y(), v.z());
    vertices[pos].set_index(pos);
}

void Mesh::add_triangle(unsigned int pos, unsigned int p1, unsigned int p2, unsigned int p3)
{
    triangles[pos].add_vertex(p1);
    triangles[pos].add_vertex(p2);
    triangles[pos].add_vertex(p3);

    vertices[p1].add_triangle(pos);
    vertices[p2].add_triangle(pos);
    vertices[p3].add_triangle(pos);

    vertices[p1].add_vertex(p2);    vertices[p1].add_vertex(p3);
    vertices[p2].add_vertex(p1);    vertices[p2].add_vertex(p3);
    vertices[p3].add_vertex(p1);    vertices[p3].add_vertex(p2);

    vertices[p1].set_num_triangle(pos);     vertices[p2].set_num_triangle(pos);     vertices[p3].set_num_triangle(pos);
    vertices[p1].set_pos_barycentric(0);    vertices[p2].set_pos_barycentric(1);    vertices[p3].set_pos_barycentric(2);

//    triangles[pos].normal[0] = (vertices[p2].y() - vertices[p1].y()) * (vertices[p3].z() - vertices[p1].z()) - (vertices[p2].z() - vertices[p1].z()) * (vertices[p3].y() - vertices[p1].y());
//    triangles[pos].normal[1] = (vertices[p2].z() - vertices[p1].z()) * (vertices[p3].x() - vertices[p1].x()) - (vertices[p2].x() - vertices[p1].x()) * (vertices[p3].z() - vertices[p1].z());
//    triangles[pos].normal[2] = (vertices[p2].x() - vertices[p1].x()) * (vertices[p3].y() - vertices[p1].y()) - (vertices[p2].y() - vertices[p1].y()) * (vertices[p3].x() - vertices[p1].x());
//    update_normal(p1); update_normal(p2); update_normal(p3);
}

void Mesh::add_normal(unsigned int pos, float nx, float ny, float nz)
{
    vertices[pos].set_normal(nx, ny, nz);
}

void Mesh::add_color(unsigned int pos, float r, float g, float b){
    vertices[pos].set_color(r, g, b);
}
}//namespace SimpleMesh
