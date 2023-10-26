#if !defined(SCENE_H)
#define SCENE_H

#include "renderer/mesh.h"
#include "renderer/model.h"
#include "renderer/material.h"

#include <stdint.h>

typedef struct scene_t {
    mesh_t* meshes;
    uint32_t mesh_count;

    material_t* materials;
    uint32_t material_count;

    model_t* models;
    uint32_t model_count;
};

#endif // SCENE_H
