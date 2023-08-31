#if !defined(TRANSFORM_H)
#define TRANSFORM_H

#include "vector.h"
#include "matrix.h"

typedef struct transform_t {
    vec3_t position, rotation, scale;
} transform_t;


mat4_t transform_get_model_matrix(transform_t* transform);

#endif // TRANSFORM_H
