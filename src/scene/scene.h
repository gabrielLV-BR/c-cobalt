#ifndef __scene_h__
#define __scene_h__

#include "renderer/mesh.h"
#include "renderer/model.h"
#include "renderer/texture.h"
#include "renderer/material.h"

#include "structs/vector.h"

#include <stdint.h>

typedef struct {
    vector_mesh_t       meshes;
    vector_material_t   materials;
    vector_model_t      models;
} scene_t;

scene_t scene_new();
scene_t scene_load_from_file(const char* path);

uint32_t scene_upload_mesh(scene_t* scene, mesh_t mesh);
uint32_t scene_upload_model(scene_t* scene, model_t model);
uint32_t scene_upload_material(scene_t* scene, material_t material);

mesh_t* scene_get_mesh(scene_t scene, uint32_t handle);
model_t* scene_get_model(scene_t scene, uint32_t handle);
material_t* scene_get_material(scene_t scene, uint32_t handle);

void scene_destroy(scene_t scene);

#endif // __scene_h__
