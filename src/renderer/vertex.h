#ifndef __vertex_h__
#define __vertex_h__

#include <stdbool.h>

#include "math/vec.h"

typedef struct {
    vec3_t position;
    vec3_t normal;
    vec2_t uv;
} vertex_t;

bool vertex_cmp(vertex_t a, vertex_t b);

#endif // __vertex_h__
