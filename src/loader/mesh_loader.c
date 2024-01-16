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

// internal data types

typedef struct {
    size_t v_position[3];
    size_t v_normal[3];
    size_t v_uv[3];
} face_t;

VECTOR_DEFINE(face_t)
VECTOR_IMPLEMENT(face_t)

typedef struct {
    vector_vec3_t positions;
    vector_vec3_t normals;
    vector_vec2_t uvs;
    vector_face_t faces;
} obj_data_t;

// fd decl

obj_data_t parse_object_data(char* source);

vec3_t  __parse_vec3_t(const char* token);
vec2_t  __parse_vec2_t(const char* token);
face_t  __parse_face_t(const char* token);

bool __void_vertex_cmp(const void* v1, const void* v2);

//

mesh_t mesh_loader_load_from_file(const char* path) {
    char* file_contents;
    long bytes_read;

    bytes_read = read_from_file(path, &file_contents);

    if (bytes_read == -1) {
        ERROR("When reading source from obj file");
        goto EXIT;
    }

    obj_data_t obj_data = parse_object_data(file_contents);

    // generate vertices
    
    vector_vertex_t vertices = vector_new_vertex_t(10);

    for(int i = 0; i < obj_data.faces.length; i++) {
        face_t* face = &obj_data.faces.data[i];

        for(int j = 0; j < 3; j++) {
            size_t position_index = face->v_position[j] - 1;
            size_t normal_index = face->v_normal[j] - 1;
            size_t uv_index = face->v_uv[j] - 1;

            vec3_t position = obj_data.positions.data[position_index];
            vec3_t normal   = obj_data.normals.data[normal_index];
            vec2_t uv       = obj_data.uvs.data[uv_index];

            vertex_t vertex = {
                .position = position,
                .normal = normal,
                .uv = uv
            };

            vector_append_vertex_t(&vertices, vertex);
        }
    }

    // index vertices

    vector_uint32_t indices = vector_new_uint32_t(vertices.length);

    qsort(vertices.data, vertices.length, sizeof(vertex_t), __void_vertex_cmp);

    uint32_t unique_index  = 0;

    for(int i = 0; i < vertices.length; /* custom incremental logic*/) {

        vector_append_uint32_t(&indices, unique_index++);

        do {
            i++;
        } while(i < vertices.length && vertex_cmp(vertices.data[i], vertices.data[i - 1]));
    }

    // we have optimized indices now
    // we must remove vertex duplicates, now

    uint32_t head = 1;
    uint32_t tail = 0;

    // sanity check
    if(vertices.length == 2 && vertex_cmp(vertices.data[0], vertices.data[1])) {
        vector_resize_vertex_t(&vertices, 1);
    } else {
        while(tail < vertices.length) {
            vertex_t a = vertices.data[head];
            vertex_t b = vertices.data[tail];

            if (!vertex_cmp(a, b)) {
                tail++;

                if(tail < vertices.length && (head - tail) > 0) {
                    vertices.data[tail] = a;
                }
            }

            head++;
        }

        vector_resize_vertex_t(&vertices, tail + 1);
    }

    vector_fit_uint32_t(&indices);

    //
    
    mesh_t mesh = {};

    mesh = mesh_new(
        vertices.data, vertices.length, 
        indices.data, indices.length, 
        0
    );

    /*
        We don't free vertices and indices because we "moved" them into mesh.
        Now mesh is responsible for the pointer's lifetime, and since the
        `vector` does not contain any other pointer, we can skip freeing it.

        Were we not to skip it, we should set its data pointer to null.

        vertices.data = NULL;
        indices.data = NULL;
    */

    // freeing

    vector_destroy_vec3_t(&obj_data.positions);
    vector_destroy_vec3_t(&obj_data.normals);
    vector_destroy_vec2_t(&obj_data.uvs);
    vector_destroy_face_t(&obj_data.faces);

EXIT:

    free(file_contents);

    return mesh;
}

obj_data_t parse_object_data(char* source) {
    obj_data_t obj_data = {};
    obj_data.positions  = vector_new_vec3_t(DEFAULT_VECTOR_SIZE);
    obj_data.normals    = vector_new_vec3_t(DEFAULT_VECTOR_SIZE);
    obj_data.uvs        = vector_new_vec2_t(DEFAULT_VECTOR_SIZE);
    obj_data.faces      = vector_new_face_t(DEFAULT_VECTOR_SIZE);

    char* token = strtok(source, NEW_LINE);

    do {

        char first_char = token[0];
        char second_char = token[1];

        if(first_char == 'v') {
            if(second_char == 't') {
                // vec 2
                vec2_t vertex = __parse_vec2_t(token);

                vector_append_vec2_t(&obj_data.uvs, vertex);

            } else {
                // vec 3
                vec3_t vertex = __parse_vec3_t(token);

                switch (second_char) {
                    case ' ':
                        vector_append_vec3_t(&obj_data.positions, vertex);
                        break;
                    case 'n':
                        vector_append_vec3_t(&obj_data.normals, vertex);
                        break;
                }
            }
        } else if (first_char == 'f') {
            // face
            face_t face = __parse_face_t(token);

            vector_append_face_t(&obj_data.faces, face);
        }

    } while(token = strtok(NULL, NEW_LINE));

    return obj_data;
}

// utility

bool __void_vertex_cmp(const void* v1, const void* v2) {
    return memcmp(v1, v2, sizeof(vertex_t));
}

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
        &face.v_position[0], &face.v_uv[0], &face.v_normal[0],
        &face.v_position[1], &face.v_uv[1], &face.v_normal[1],
        &face.v_position[2], &face.v_uv[2], &face.v_normal[2]
    );

    return face;
}
