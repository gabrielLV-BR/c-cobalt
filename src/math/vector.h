#if !defined(VECTOR_H)
#define VECTOR_H

typedef struct vec3_t {
    float x, y, z;

    union {
        float data[3];
    };
} vec3_t;

vec3_t vec3_new(float x, float y, float z);

float vec3_magnitude(vec3_t vec);

vec3_t vec3_normalized(vec3_t vec);

vec3_t vec3_scaled(vec3_t vec, float scalar);

float vec3_dot(vec3_t a, vec3_t b);
vec3_t vec3_cross(vec3_t a, vec3_t b);

#endif // VECTOR_H
