#include "mesh.h"

#include <stdint.h>
#include <stdlib.h>

#include "glad/glad.h"

mesh_t mesh_new(
    vec3_t* vertices, 
    int vertex_count, 
    uint32_t* indices, 
    int index_count, 
    uint32_t material_handle
) {
    uint32_t vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3_t) * vertex_count, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * index_count, indices, GL_STATIC_DRAW);

    int vertex_offset = 0;
    int uv_offset = 3 * sizeof (float);
    int stride = 5 * sizeof (float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)&vertex_offset);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)&uv_offset);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return (mesh_t) {
        .vao = vao,
        .vbo = vbo,
        .ebo = ebo,
        .vertices = vertices,
        .vertex_count = vertex_count,
        .indices = indices,
        .index_count = index_count,
        .material_handle = material_handle
    };
    
}

void mesh_destroy(mesh_t* mesh) {
    free(mesh->vertices);
    free(mesh->indices);

    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    glDeleteVertexArrays(1, &mesh->vao);
}
