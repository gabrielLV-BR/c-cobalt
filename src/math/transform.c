#include "transform.h"

#include "matrix.h"

transform_t transform_identity() {
    return (transform_t) {
        .position = vec3_zero(),
        .scale = vec3_one(),
        .rotation = vec3_zero()
    };
}

mat4_t transform_get_model_matrix(transform_t* transform) {
    //TODO rotate this mf
    mat4_t matrix = mat4_identity();
    
    matrix = mat4_scale(matrix, transform->scale);
    matrix = mat4_translate(matrix, transform->position);

    return matrix;
}