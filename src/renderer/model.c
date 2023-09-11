#include "model.h"
#include "utils/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

model_t model_new(mesh_t* meshes, int num_meshes, transform_t transform) {
    return (model_t) {
        .meshes = meshes,
        .num_meshes = num_meshes,
        .transform = transform
    };
}

model_t model_load_from_file(const char* path) {
    char* source;
    model_t model = {0};

    long status = read_from_file(path, &source);

    if(status == -1) {
        goto EXIT;
    }

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

void model_destroy(model_t* model) {
    free(model->meshes);
}