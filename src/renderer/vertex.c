#include "vertex.h"

bool vertex_cmp(vertex_t a, vertex_t b) {
    return vec3_cmp(a.position, b.position) &&
        vec3_cmp(a.normal, b.normal) &&
        vec2_cmp(a.uv, b.uv);
}

VECTOR_IMPLEMENT(vertex_t)