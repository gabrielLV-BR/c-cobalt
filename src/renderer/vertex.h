#ifndef __vertex_h__
#define __vertex_h__

#include <stdbool.h>

#include "math/vec.h"
#include "structs/vector.h"

typedef struct {
    vec3_t position;
    vec3_t normal;
    vec2_t uv;
} vertex_t;

bool vertex_cmp(vertex_t a, vertex_t b);

VECTOR_DEFINE(vertex_t)

#endif // __vertex_h__
