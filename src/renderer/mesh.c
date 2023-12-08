#include "mesh.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "glad/gl.h"

mesh_t mesh_new(
    vertex_t* vertices, 
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertex_count, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * index_count, indices, GL_STATIC_DRAW);

    //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*) offsetof(vertex_t, position));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*) offsetof(vertex_t, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*) offsetof(vertex_t, uv));
    glEnableVertexAttribArray(2);
    //

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

VECTOR_IMPLEMENT(mesh_t)