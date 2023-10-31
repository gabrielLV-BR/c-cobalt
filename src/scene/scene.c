#include "scene.h"

#include <stdlib.h>

#define STARTING_ARRAY_COUNT 10

scene_t scene_new() {
    return (scene_t) {
        .meshes = vector_void_new(STARTING_ARRAY_COUNT),
        .models = vector_void_new(STARTING_ARRAY_COUNT),
        .materials = vector_void_new(STARTING_ARRAY_COUNT),
    };
}

scene_t scene_load_from_file(const char* path) {

}

uint32_t scene_load_mesh(scene_t* scene, mesh_t* mesh) {
    vector_void_append(&scene->meshes, (void*)mesh);
    return scene->meshes.length - 1;
}

uint32_t scene_load_material(scene_t* scene, material_t* material) {
    vector_void_append(&scene->materials, (void*)material);
    return scene->materials.length - 1;
}

uint32_t scene_add_model(scene_t* scene, model_t* model) {
    vector_void_append(&scene->models, (void*)model);
    return scene->models.length - 1;
}