#if !defined(SHADER_H)
#define SHADER_H

#include <stdint.h>

#include "renderer/texture.h"
#include "math/matrix.h"

typedef struct shader_t {
    uint32_t handle;
} shader_t;

typedef struct program_t {
    uint32_t handle;
} program_t;

shader_t shader_new(const char* source, uint32_t shader_type);
shader_t shader_read_from_file(const char* path, uint32_t shader_type);

//

program_t program_new(shader_t vertex, shader_t fragment);
void program_destroy(program_t program);

void program_set_matrix(program_t program, const char* name, mat4_t matrix);
void program_set_texture_unit(program_t program, const char* name, enum TEXTURE_UNIT unit);

// debug

void program_print_uniforms(program_t program);

#endif // SHADER_H
