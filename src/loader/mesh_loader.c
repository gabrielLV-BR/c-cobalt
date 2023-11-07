#include "mesh_loader.h"

#include "utils/file.h"
#include "renderer/mesh.h"
#include "structs/vector.h"
#include "math/vec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int v_position_count;
    int v_normal_count;
    int v_uv_count;
} count_result_t;

vec3_t __parse_vec3_t(const char* token) {
    // token should be in this format
    // v( |n|t) %f %f %f\n

    float x, y, z;

    int status = sscanf(token, "%*s %f %f %f", &x, &y, &z);

    printf("Status = %d\n", status);
    printf("X = %f\n Y = %f\n Z = %f\n", x, y, z);

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

mesh_t mesh_loader_load_from_file(const char* path) {

    FILE* f = fopen(path, "r");
    char* line = NULL;
    int status = 0;
    size_t size = 0;

    mesh_t mesh = {0};

    vector_void_t vertex_positions = vector_void_new(50);
    vector_void_t vertex_normals = vector_void_new(50);
    vector_void_t vertex_uvs = vector_void_new(50);

    if(f == NULL) goto EXIT;

    do {
        status = getline(&line, &size, f);        

        printf("Reading line: %s\n", line);

        if(!line) continue;

        switch (line[0])
        {
            case 'v': {
                printf("Is vertex!\n");
                vec3_t buff = __parse_vec3_t(line);
                printf("(%f, %f, %f)\n", buff.x, buff.y, buff.z);
            };
        }
    } while(status != -1);

EXIT:

    if(line) free(line);

    fclose(f);

    return mesh;
}