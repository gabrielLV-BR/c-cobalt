#include "model.h"
#include "utils/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

model_t model_new(mesh_t* meshes, int num_meshes, transform_t transform) {
}

model_t model_load_from_file(const char* path) {
    
}

void model_destroy(model_t* model) {
    free(model->mesh_handles);
}