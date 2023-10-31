#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "texture.h"
#include "shader.h"

#include "math/vec.h"

typedef enum {
    TEXTURE_INDEX_DIFFUSE = 0,
    TEXTURE_INDEX_NORMAL = 1
} MATERIAL_TEXTURE_INDEX;

typedef struct material_t {
    vec3_t color;
    texture_t* maps;
    int map_count;
} material_t;

material_t material_load_from_file(const char* path);
void material_bind(program_t* program, material_t* material);
void material_destroy(material_t material);

#endif // MATERIAL_H
