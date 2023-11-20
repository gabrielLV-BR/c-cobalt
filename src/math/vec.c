#include "vec.h"

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

bool vec3_cmp(vec3_t a, vec3_t b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

uint32_t vec3_hash(vec3_t vec) {
    // naive hash algorithm for vec
    // provided by yours truly, ChatGPT
    uint32_t x = *((uint32_t*) &vec.x);
    uint32_t y = *((uint32_t*) &vec.y);
    uint32_t z = *((uint32_t*) &vec.z);

    uint32_t hash = 17;

    hash = 31 * hash + x;
    hash = 31 * hash + y;
    hash = 31 * hash + z;

    return hash;
}

// vec 2

vec2_t vec2_new(float x, float y) {
    return (vec2_t) { x, y };
}

vec2_t vec2_zero() {
    return (vec2_t) { 0 };
}

vec2_t vec2_one() {
    return (vec2_t) { 1, 1 };
}

float vec2_magnitude(vec2_t vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

vec2_t vec2_add(vec2_t a, vec2_t b) {
    return (vec2_t) { a.x + b.x, a.y + b.y };
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
    return (vec2_t) { a.x - b.x, a.y - b.y };
}

vec2_t vec2_normalize(vec2_t vec) {
    float mag = vec2_magnitude(vec);

    if(mag != 0.0) {
        return vec2_scaled(vec, 1.0 / mag);
    }

    return vec;
}

vec2_t vec2_scaled(vec2_t vec, float scalar) {
    return (vec2_t) { vec.x * scalar, vec.y * scalar };
}

vec2_t vec2_perpendicular_clockwise(vec2_t vec) {
    return (vec2_t) { vec.y, -vec.x };
}

vec2_t vec2_perpendicular_counter_clockwise(vec2_t vec) {
    return (vec2_t) { -vec.y, vec.x };
}

bool vec2_cmp(vec2_t a, vec2_t b) {
    return a.x == b.x && a.y == b.y;
}

uint32_t vec2_hash(vec2_t vec) {
    // naive hash algorithm for vec
    // provided by yours truly, ChatGPT
    uint32_t x = *((uint32_t*) &vec.x);
    uint32_t y = *((uint32_t*) &vec.y);

    uint32_t hash = 17;

    hash = 31 * hash + x;
    hash = 31 * hash + y;

    return hash;
}