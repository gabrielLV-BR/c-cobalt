#ifndef __shader_h__
#define __shader_h__

#include <stdint.h>

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
void program_set_mvp(program_t program, mat4_t model, mat4_t view, mat4_t proj);

void program_set_texture_unit(program_t program, const char* name, uint32_t unit);

// debug

void debug__program_print_uniforms(program_t program);

#endif // __shader_h__
