#ifndef __material_h__
#define __material_h__

#include "renderer/shader.h"

#include "math/vec.h"

typedef enum {
    TEXTURE_UNIT_DIFFUSE = 0,
    TEXTURE_UNIT_NORMAL = 1
} texture_unit_t;

typedef struct {
    vec3_t color;
    uint32_t* maps;
    int map_count;
} material_t;

material_t material_load_from_file(const char* path);
void material_bind(program_t* program, material_t* material);
void material_destroy(material_t material);

#endif // __material_h__
