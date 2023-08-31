#include "model.h"

model_t model_new(mesh_t* meshes, int num_meshes, transform_t transform) {
    return (model_t) {
        .meshes = meshes,
        .num_meshes = num_meshes,
        .transform = transform
    };
}