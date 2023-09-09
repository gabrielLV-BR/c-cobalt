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

    float rotation_mag = vec3_magnitude(transform->rotation);
    vec3_t norm_rotation = vec3_normalize(transform->rotation);

    matrix = mat4_rotate(matrix, norm_rotation, rotation_mag);

    matrix = mat4_scale(matrix, transform->scale);
    matrix = mat4_translate(matrix, transform->position);

    return matrix;
}