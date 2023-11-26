#include "mesh_loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math/vec.h"
#include "utils/file.h"
#include "renderer/mesh.h"
#include "renderer/vertex.h"
#include "structs/vector.h"

typedef struct {
    int v_position_count;
    int v_normal_count;
    int v_uv_count;
} count_result_t;

typedef struct {
    uint32_t v_position[3];
    uint32_t v_normal[3];
    size_t v_uv[3];
} face_t;

// fd decl

vec3_t          __parse_vec3_t(const char* token);
face_t          __parse_face_t(const char* token);
count_result_t  __count_vertices_from_source(const char* source, long len) ;

void            __insert_vertex();

//

mesh_t mesh_loader_load_from_file(const char* path) {

    FILE* f = fopen(path, "r");
    char* line = NULL;
    int status = 0;
    size_t size = 0;

    mesh_t mesh = {0};

    vector_vec3_t positions = vector_new_vec3_t(50);
    vector_vec3_t normals = vector_new_vec3_t(50);
    vector_vec3_t uvs = vector_new_vec3_t(50);

    vector_vertex_t indices = vector_new_vertex_t(50);

    if(f == NULL) goto EXIT;

    do {
        status = getline(&line, &size, f);        

        printf("Reading line: %s\n", line);

        if(!line) continue;

        switch (line[0])
        {
            case 'v': {
                printf("Is vertex!\n");
                vec3_t data = __parse_vec3_t(line);

                switch (line[1])
                {
                    case ' ':
                        vector_append_vec3_t(&positions, data);
                        break;
                    case 'n':
                        vector_append_vec3_t(&normals, data);
                        break;
                    case 't':
                        vector_append_vec3_t(&uvs, data);
                        break;
                }

                break;
            }
            case 'f': {
                face_t face = __parse_face_t(line);
                //TODO build vertex
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

// private

vec3_t __parse_vec3_t(const char* token) {
    // token should be in this format
    // v( |n|t) %f %f %f\n

    float x, y, z;

    int status = sscanf(token, "%*s %f %f %f", &x, &y, &z);

    printf("Status = %d\n", status);
    printf("X = %f\n Y = %f\n Z = %f\n", x, y, z);

    return (vec3_t) { x, y, z };
}

count_result_t __count_vertices_from_source(const char* source, long len) {
    count_result_t count = {0};

    int in_comment = 0;

    for(long i = 0; i < len; i++) {
        char c = source[i];

        if(c == '#') {
            in_comment = 1;
        } else if(c == '\n') {
            in_comment = 0;
        }

        if(in_comment == 1) continue;

        if(c == 'v') {
            switch(source[i + 1]) {
                case ' ': {
                    count.v_position_count++;
                    break;
                }
                case 'n' : {
                    count.v_normal_count++;
                    break;
                }
                case 't': {
                    count.v_uv_count++;
                    break;
                }
            }
        }
    }

    return count;
}

face_t __parse_face_t(const char* token) {
    face_t face;

    int status = sscanf(
        token, 
        "%*s %d/%d/%d %d/%d/%d %d/%d/%d", 
        &face.v_position[0], &face.v_normal[0], &face.v_uv[0],
        &face.v_position[1], &face.v_normal[1], &face.v_uv[1],
        &face.v_position[2], &face.v_normal[2], &face.v_uv[2]
    );

    printf("Status = %d\n", status);

    return face;
}

void __insert_vertex() {}
