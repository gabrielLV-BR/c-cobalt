#include "mesh_loader.h"

#include "utils/file.h"
#include "renderer/mesh.h"
#include "structs/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int v_position_count;
    int v_normal_count;
    int v_uv_count;
} count_result_t;

count_result_t __count_vertices_from_source(char* source, long len) {
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

mesh_t mesh_loader_load_from_file(const char* path) {
    char* source;
    mesh_t mesh = {0};
    long len = read_from_file(path, &source);

    if(len == -1) {
        goto EXIT;
    }

    //

    count_result_t count = __count_vertices_from_source(source, len);

    vec3_t* vertex_positions = calloc(count.v_position_count, sizeof(vec3_t));
    vec3_t* vertex_normals = calloc(count.v_normal_count, sizeof(vec3_t));
    vec3_t* vertex_uvs = calloc(count.v_uv_count, sizeof(vec3_t));

    char * token = strtok(source, "\n");

    while( token != NULL ) {

        /*
            There are a few possibilities when it comes to the starting char:
            - #  : that's a comment, can ignore;
            - v  : vertex;
            - vn : vertex normal;
            - vt : vertex texture coordinate;
            - f  : face
            - mtlib : material to load
            - usemat: material to use
            - o  : object's name
        */

        switch (token[0])
        {
        case '#': continue;
        case 'v': {

            if(token[1] == ' ') {
                // vertex

            }

            break;
        };
        }

        token = strtok(NULL, "\n");
    }

EXIT:
    free(source);

    return model;
}