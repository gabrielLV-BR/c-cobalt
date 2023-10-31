#ifndef __scene_h__
#define __scene_h__

#include "renderer/mesh.h"
#include "renderer/model.h"
#include "renderer/texture.h"
#include "renderer/material.h"

#include "structs/vector.h"

#include <stdint.h>

typedef struct {
    vector_void_t meshes;
    vector_void_t materials;
    vector_void_t models;
} scene_t;

scene_t scene_new();
scene_t scene_load_from_file(const char* path);

uint32_t scene_load_mesh(scene_t* scene, mesh_t* mesh);
uint32_t scene_load_material(scene_t* scene, material_t* texture);

uint32_t scene_add_model(scene_t* scene, model_t* model);

void scene_destroy(scene_t* scene);

#endif // __scene_h__
