#include "transform.h"

#include "matrix.h"

mat4_t transform_to_mat(transform_t* transform) {
    //TODO rotate this mf
    return (mat4_t) {
        transform->scale.x, 0, 0, transform->position.x,
        0, transform->scale.y, 0, transform->position.y,
        0, 0, transform->scale.z, transform->position.z,
        0, 0, 0, 1,
    };
}