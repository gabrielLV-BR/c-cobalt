#if !defined(MESH_H)
#define MESH_H

#include "material.h"
#include "math/vec.h"

#include "renderer/vertex.h"
#include "structs/vector.h"

#include <stdint.h>

typedef struct mesh_t {
    uint32_t vao, vbo, ebo;

    vertex_t* vertices;
    int vertex_count;

    int index_count;
    uint32_t* indices;

    uint32_t material_handle;
} mesh_t;

mesh_t mesh_new(
    vertex_t* vertices, 
    int vertex_count, 
    uint32_t* indices, 
    int index_count, 
    uint32_t material_handle
);

void mesh_destroy(mesh_t* mesh);

VECTOR_DEFINE(mesh_t)

#endif // MESH_H
