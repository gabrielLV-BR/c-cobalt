#include "renderer/material.h"
#include "renderer/texture.h"

#include "glad/glad.h"
#include "utils/error.h"
#include "utils/file.h"
#include "math/functions.h"

#include <stdlib.h>
#include <string.h>

void material_bind(program_t* program, material_t* material) {
    for(int i = 0; i < material->map_count; i++) {
        program_set_texture_unit(*program, texture_unit_name(i), i);
    }
}

material_t material_load_from_file(const char* path) {
    material_t material;

    char* root_path;
    int root_path_len;

    char* source;
    long source_size = read_from_file(path, &source);

    if(source_size == -1) {
        goto EXIT;
    }

    // extract dir in path

    root_path_len = get_file_dir(path, &root_path);

    // leave some space for the necessary maps
    texture_t textures[5];
    int texture_count = 0;

    //TODO load other textures
    char* map_Kd = strstr(source, "map_Kd");
    
    if(map_Kd != NULL) {
        // load diffuse map
        char* diffuse_map_path;
        char* start = map_Kd + 7;
        
        int diffuse_map_len = 0;
        
        while(start[diffuse_map_len] != '\n' && start[diffuse_map_len] != '\0') 
            diffuse_map_len++;

        diffuse_map_path = calloc(sizeof (char), root_path_len + diffuse_map_len);

        strcat(diffuse_map_path, root_path);
        strncat(diffuse_map_path, start, diffuse_map_len);

        textures[texture_count++] = texture_load_from_file(diffuse_map_path);

        free(diffuse_map_path);
    }

    // TODO read color from material
    material.color = (vec3_t){0, 0, 0};
    material.map_count = texture_count;
    material.map_handles = calloc(sizeof(material_t), texture_count);

    // for(int i = 0; i < texture_count; i++)
    //     material.maps[i] = textures[i];

EXIT:

    free(source);
    free(root_path);

    return material;
}

void material_destroy(material_t material) {
    free(material.map_handles);
}

VECTOR_IMPLEMENT(material_t)