#include "vector.h"

#include <math.h>

vec3_t vec3_new(float x, float y, float z) {
    return (vec3_t) {
        .x = x,
        .y = y,
        .z = z
    };
}

vec3_t vec3_zero() {
    return (vec3_t) {0};
}

vec3_t vec3_one() {
    return (vec3_t) { 1.0, 1.0, 1.0 };
}

//

vec3_t vec3_add(vec3_t a, vec3_t b) {
    return (vec3_t) { a.x + b.x, a.y + b.y, a.z + b.z };
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
    return (vec3_t) { a.x - b.x, a.y - b.y, a.z - b.z };
}

float vec3_magnitude(vec3_t vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

vec3_t vec3_normalize(vec3_t vec) {
    float mag = vec3_magnitude(vec);

    if(mag == 0.0f) return vec;

    return vec3_scaled(vec, 1.0f / mag);
}

vec3_t vec3_scaled(vec3_t vec, float scalar) {
    return (vec3_t) {
        .x = vec.x * scalar,
        .y = vec.y * scalar,
        .z = vec.z * scalar,
    };
}

float vec3_dot(vec3_t a, vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
    vec3_t cross = {0};

    cross.x = a.y * b.z + a.z * b.y;
    cross.y = a.x * b.z + a.z * b.x;
    cross.z = a.x * b.y + a.y * b.x;

    return cross;
}