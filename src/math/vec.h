#if !defined(VEC_H)
#define VEC_H

typedef struct vec3_t {
    float x, y, z;

    union {
        float data[3];
    };
} vec3_t;

// constructors
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

#endif // VEC_H
