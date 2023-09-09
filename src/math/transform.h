#if !defined(TRANSFORM_H)
#define TRANSFORM_H

#include "vec.h"
#include "matrix.h"

typedef struct transform_t {
    vec3_t position, rotation, scale;
} transform_t;


transform_t transform_identity();
mat4_t transform_get_model_matrix(transform_t* transform);

#endif // TRANSFORM_H
