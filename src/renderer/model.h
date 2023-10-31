#if !defined(MODEL_H)
#define MODEL_H

#include <stdint.h>

#include "mesh.h"
#include "material.h"
#include "math/transform.h"

typedef struct model_t {
    uint32_t* mesh_handles;
    uint32_t mesh_handle_count;
    transform_t transform;
} model_t;

model_t model_new(mesh_t* meshes, int num_meshes, transform_t transform);
model_t model_load_from_file(const char* path);
void model_destroy(model_t* mesh);

#endif // MODEL_H
