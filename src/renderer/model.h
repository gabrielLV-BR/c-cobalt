#ifndef __model_h__
#define __model_h__

#include <stdint.h>

#include "mesh.h"
#include "material.h"
#include "math/matrix.h"
#include "math/transform.h"

#include "structs/vector.h"

typedef struct model_t {
    uint32_t* mesh_handles;
    uint32_t mesh_handle_count;
    transform_t transform;

    int __dirty;
    mat4_t __model_matrix;
} model_t;

model_t model_new(uint32_t* mesh_handles, int mesh_handle_count, transform_t transform);
model_t model_load_from_file(const char* path);

void model_destroy(model_t* mesh);

VECTOR_DEFINE(model_t)

#endif // __model_h__
