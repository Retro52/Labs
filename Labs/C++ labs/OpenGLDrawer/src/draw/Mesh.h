//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <cstdlib>

class Mesh
{
private:
    unsigned int vao, vbo, id;
    size_t vertices, vertexSize;
public:
    Mesh(const float *buffer, size_t vertices, const int *attrs, unsigned int meshID);
    ~Mesh();

    void reload(const float* buffer, size_t verts);
    void draw(unsigned int primitive) const;
};


#endif //GRAPHICS_MESH_H
