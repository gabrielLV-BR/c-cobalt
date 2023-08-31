#include "matrix.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265f
#define TO_RAD(x) (x * 180.0f / PI)

mat4_t mat4_identity() {
    return (mat4_t) {
        .data = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }
    };
}

void mat4_multiply(mat4_t* a, mat4_t* b, mat4_t* out) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            float total = 0;

            for(int k = 0; k < 4; k++) 
                total += b->data[i + k * 4] * a->data[k + j * 4];

            out->data[i + j * 4] = total;
        }
    }
}

void mat4_print(mat4_t* mat) {
    printf("Matrix:\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%.1f ", mat->data[i + j * 4]);
        }
        printf("\n");
    }
    printf("---");
}

// rotations

mat4_t mat4_perspective(float fov, float aspect, float near, float far) {
    float anglediv = 1.0f / tan(fov / 2);
    float zdiv = far / (far - near);

    mat4_t perspective_matrix = {
        aspect * anglediv, 0, 0, 0,
        0, anglediv, 0, 0,
        0, 0, zdiv, -zdiv * near,
        0, 0, 1, 0
    };

    return perspective_matrix;
}

void mat4_rotate(mat4_t* mat, vec3_t* direction, float ammount, mat4_t* out) {
    printf("[mat4_rotate] Not implemented!\m");
}

void mat4_translate(mat4_t* mat, vec3_t* velocity) {
    mat->data[4] += velocity->x;
    mat->data[8] += velocity->y;
    mat->data[12] += velocity->z;
}

void mat4_rotate_x(mat4_t* mat, float deg, mat4_t* out) {
    /*
        1 0 0 0
        0 cos -sen 0
        0 sen cos 0
        0 0 0 1
    */

    float c = (float)cos(TO_RAD(deg));
    float s = (float)sin(TO_RAD(deg));

    mat4_t rotation_matrix = {
        1, 0, 0, 0, 
        0, c, -s, 0, 
        0, s, c, 0, 
        0, 0, 0, 1, 
    };

    return mat4_multiply(&rotation_matrix, mat, out);
}

void mat4_rotate_y(mat4_t* mat, float deg, mat4_t* out) {
    /*
        cos  0  sen  0
        0    1  0    0
        -sen 0  cos  0
        0    0  0    1
    */

    float c = (float)cos(TO_RAD(deg));
    float s = (float)sin(TO_RAD(deg));

    mat4_t rotation_matrix = {
        c, 0, s, 0, 
        0, 1, 0, 0, 
        -s, 0, c, 0, 
        0, 0, 0, 1, 
    };

    return mat4_multiply(&rotation_matrix, mat, out);
}

void mat4_rotate_z(mat4_t* mat, float deg, mat4_t* out) {     
    /*   cos  sin  0  0
        -sin  cos  0  0
         0    0    1  0
         0    0    0  1
    */

    float c = (float)cos(TO_RAD(deg));
    float s = (float)sin(TO_RAD(deg));

    mat4_t rotation_matrix = {
        c, -s, 0, 0, 
        s, c, 0, 0, 
        0, 0, 1, 0, 
        0, 0, 0, 1, 
    };

    return mat4_multiply(&rotation_matrix, mat, out);
}