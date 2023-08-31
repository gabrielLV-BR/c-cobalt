#if !defined(MATRIX_H)
#define MATRIX_H

#include "vec.h"

typedef struct mat4_t {
    float data[16];
} mat4_t;

// creators 

mat4_t mat4_identity();
mat4_t mat4_perspective(float fov, float aspect, float near, float far);

// operations 

mat4_t mat4_translate(mat4_t mat, vec3_t velocity);
mat4_t mat4_rotate(mat4_t mat, vec3_t direction, float ammount);

mat4_t mat4_rotate_x(mat4_t mat, float deg);
mat4_t mat4_rotate_y(mat4_t mat, float deg);
mat4_t mat4_rotate_z(mat4_t mat, float deg);

mat4_t mat4_multiply(mat4_t a, mat4_t b);

mat4_t mat4_look_at(const vec3_t* direction, const vec3_t* up, const vec3_t* right, const vec3_t* point);

// debug

void mat4_print(mat4_t mat);

#endif // MATRIX_H
