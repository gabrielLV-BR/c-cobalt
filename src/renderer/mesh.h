#if !defined(MESH_H)
#define MESH_H

#include <stdint.h>

typedef struct mesh_t {
    uint32_t vao, vbo, ebo;
    float* vertices;
    uint32_t* indices;

    int vertex_count;
    int index_count;
} mesh_t;

mesh_t mesh_new(float* vertices, int vertex_count, uint32_t* indices, int index_count);
void mesh_destroy(mesh_t* mesh);

#endif // MESH_H
