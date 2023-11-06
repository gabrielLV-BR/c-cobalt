#include "model.h"
#include "utils/file.h"
#include "scene/scene.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

model_t model_new(
    uint32_t* mesh_handles,
    int mesh_handle_count,
    transform_t transform
) {    
    return (model_t) {
        .mesh_handles = mesh_handles,
        .mesh_handle_count = mesh_handle_count,
        .transform = transform,
        .__dirty = 0,
        .__model_matrix = {0}
    };
}

model_t model_load_from_file(const char* path) {

}

void model_destroy(model_t* model) {
    free(model->mesh_handles);
}