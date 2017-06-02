#ifndef OFFWRITER_H
#define OFFWRITER_H

#include "simplemesh_global.h"
#include <string>
#include "mesh.h"

using namespace std;

namespace SimpleMesh{

namespace IO {

class SIMPLEMESH_API OFFWriter
{
    string filename;

public:
    OFFWriter(const char* file);
    void write_mesh(Mesh& mesh);
    void write_colored_mesh(Mesh& mesh);
};

} //namespace IO
} //namespace SimpleMesh

#endif // OFFWRITER_H
