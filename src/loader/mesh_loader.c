#include "mesh_loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math/vec.h"
#include "utils/file.h"
#include "renderer/mesh.h"
#include "renderer/vertex.h"
#include "structs/base.h"
#include "structs/vector.h"
#include "structs/vertex_map.h"

#define DEFAULT_VECTOR_SIZE 100

typedef struct {
    int v_position_count;
    int v_normal_count;
    int v_uv_count;
} count_result_t;

typedef struct {
    size_t v_position[3];
    size_t v_normal[3];
    size_t v_uv[3];
} face_t;

// fd decl

void parse_vertex(
    const char* line, 
    vector_vec3_t* positions,
    vector_vec3_t* normals,
    vector_vec2_t* uvs
);

void insert_vertex(
    vertex_t vertex,
    vertex_map_t* map,
    vector_vertex_t* vertices,
    vector_uint32_t* indices
);

vec3_t  __parse_vec3_t(const char* token);
vec2_t  __parse_vec2_t(const char* token);
face_t  __parse_face_t(const char* token);

//

mesh_t mesh_loader_load_from_file(const char* path) {

    FILE* f = fopen(path, "r");
    char* line = NULL;
    int status = 0;
    size_t size = 0;

    mesh_t mesh = {0};

    vector_vec3_t positions = vector_new_vec3_t(DEFAULT_VECTOR_SIZE);
    vector_vec3_t normals   = vector_new_vec3_t(DEFAULT_VECTOR_SIZE);
    vector_vec2_t uvs       = vector_new_vec2_t(DEFAULT_VECTOR_SIZE);

    vector_vertex_t vertices = vector_new_vertex_t(DEFAULT_VECTOR_SIZE);
    vector_uint32_t indices  = vector_new_uint32_t(DEFAULT_VECTOR_SIZE);

    vertex_map_t* map = vertex_map_new();

    if (f == NULL) goto EXIT;

    do {
        status = getline(&line, &size, f);        

        if (!line) continue;

        char token = line[0];

        if(token == 'v') {
            parse_vertex(line, &positions, &normals, &uvs);
        
        } else if (token == 'f') {

            face_t face = __parse_face_t(line);

            for(int i = 0; i < 3; i ++) {
                size_t position_index = face.v_position[i] - 1;
                size_t normal_index = face.v_normal[i] - 1;
                size_t uv_index = face.v_uv[i] - 1;

                vertex_t vertex = {
                    positions.data[position_index],
                    normals.data[normal_index],
                    uvs.data[uv_index]
                };

                insert_vertex(
                    vertex,
                    map,
                    &vertices,
                    &indices
                );
            }
        }
    } while(status != -1);

    mesh = mesh_new(
        positions.data, positions.length,
        indices.data, indices.length,
        0
    );

EXIT:

    if(line) free(line);

    fclose(f);

    return mesh;
}

void parse_vertex(const char* line, vector_vec3_t* positions, vector_vec3_t* normals, vector_vec2_t* uvs) {

    // type:
    // - ' ' : position
    // - 'n' : normal
    // - 't' : uv

    char type = line[1];

    if(type == ' ') {
        vec3_t position = __parse_vec3_t(line);
        vector_append_vec3_t(positions, position);
    } 
    else if(type == 'n') {
        vec3_t normal = __parse_vec3_t(line);
        vector_append_vec3_t(normals, normal);
    }
    else if(type == 't') {
        vec2_t uv = __parse_vec2_t(line);
        vector_append_vec2_t(uvs, uv);
    }
}

void insert_vertex(
    vertex_t vertex,
    vertex_map_t* map,
    vector_vertex_t* vertices,
    vector_uint32_t* indices
) {
    uint32_t index = 0;
    uint32_t maybe_index = vertex_map_get(map, vertex);
    
    if(maybe_index != NOT_FOUND) {
        // not found, must insert
        vertex_map_insert(map, vertex, index);
        vector_append_vertex_t(vertices, vertex);
        vector_append_uint32_t(indices, index++);
    } else {
        // found, use as is
        vector_append_uint32_t(indices, maybe_index);
    }
}

// utility

vec3_t __parse_vec3_t(const char* token) {
    // token should be in this format
    // v( |n|t) %f %f %f\n

    float x, y, z;

    sscanf(token, "%*s %f %f %f", &x, &y, &z);

    return (vec3_t) { x, y, z };
}

vec2_t  __parse_vec2_t(const char* token) {
    // token should be in this format
    // v( |n|t) %f %f \n

    float x, y;

    sscanf(token, "%*s %f %f", &x, &y);

    return (vec2_t) { x, y };
}

face_t __parse_face_t(const char* token) {
    face_t face;

    sscanf(
        token, 
        "%*s %ld/%ld/%ld %ld/%ld/%ld %ld/%ld/%ld", 
        &face.v_position[0], &face.v_normal[0], &face.v_uv[0],
        &face.v_position[1], &face.v_normal[1], &face.v_uv[1],
        &face.v_position[2], &face.v_normal[2], &face.v_uv[2]
    );

    return face;
}
