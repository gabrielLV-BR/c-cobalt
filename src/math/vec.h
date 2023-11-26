#ifndef __vec_h__
#define __vec_h__

#include <stdint.h>
#include <stdbool.h>

#include "structs/vector.h"

typedef struct {
    float x, y, z;

    union {
        float data[3];
    };
} vec3_t;

typedef struct {
    float x, y;

    union {
        float data[2];
    };
} vec2_t;

// vec 3
vec3_t vec3_new(float x, float y, float z);
vec3_t vec3_zero();
vec3_t vec3_one();

float vec3_magnitude(vec3_t vec);
float vec3_dot(vec3_t a, vec3_t b);

vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);

vec3_t vec3_normalize(vec3_t vec);
vec3_t vec3_scaled(vec3_t vec, float scalar);
vec3_t vec3_cross(vec3_t a, vec3_t b);

bool vec3_cmp(vec3_t a, vec3_t b);
uint32_t vec3_hash(vec3_t vec);

VECTOR_DEFINE(vec3_t)

// vec 2

vec2_t vec2_new(float x, float y);
vec2_t vec2_zero();
vec2_t vec2_one();

float vec2_magnitude(vec2_t vec);

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);

vec2_t vec2_normalize(vec2_t vec);
vec2_t vec2_scaled(vec2_t vec, float scalar);

vec2_t vec2_perpendicular_clockwise(vec2_t vec);
vec2_t vec2_perpendicular_counter_clockwise(vec2_t vec);

bool vec2_cmp(vec2_t a, vec2_t b);
uint32_t vec2_hash(vec2_t vec);

VECTOR_DEFINE(vec2_t)

#endif // __vec_h__
