#include "scene.h"

#include <stdlib.h>

#define STARTING_ARRAY_COUNT 10

scene_t scene_new() {
    return (scene_t) {
        .meshes     = vector_new_mesh_t(STARTING_ARRAY_COUNT),
        .models     = vector_new_model_t(STARTING_ARRAY_COUNT),
        .materials  = vector_new_material_t(STARTING_ARRAY_COUNT),
    };
}

scene_t scene_load_from_file(const char* path) {

}

uint32_t scene_upload_mesh(scene_t* scene, mesh_t mesh) {
    vector_append_mesh_t(&scene->meshes, mesh);
    return scene->meshes.length - 1;
}

uint32_t scene_upload_material(scene_t* scene, material_t material) {
    vector_append_material_t(&scene->materials, material);
    return scene->materials.length - 1;
}

uint32_t scene_upload_model(scene_t* scene, model_t model) {
    vector_append_model_t(&scene->models, model);
    return scene->models.length - 1;
}

void scene_destroy(scene_t* scene) {
    vector_destroy_mesh_t(&scene->meshes);
    vector_destroy_model_t(&scene->models);
    vector_destroy_material_t(&scene->materials);
}