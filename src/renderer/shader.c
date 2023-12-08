#include "shader.h"

#include "glad/gl.h"
#include "utils/error.h"
#include "utils/file.h"

#include <stdio.h>
#include <stdlib.h>

int shader_check_for_errors(uint32_t shader, uint32_t shader_type) {
    int compile_status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    if(compile_status == GL_FALSE) {
        int len;
        
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

        char* info_log = (char*) malloc(sizeof(char) * len);

        glGetShaderInfoLog(shader, len, NULL, info_log);
        fprintf(stderr, "Error compiling %s shader: %s\n", 
            (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment"), 
            info_log
        );

        free(info_log);

        return -1;
    }
    return 0;
}

int __program_check_for_errors(uint32_t program) {
    int link_status;

    glGetProgramiv(program, GL_LINK_STATUS, &link_status);

    if(link_status == GL_FALSE) {
        int len;
        
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        char* info_log = (char*) malloc(sizeof(char) * len);

        glGetProgramInfoLog(program, len, NULL, info_log);
        fprintf(stderr, "Error linking program: %s\n", info_log);

        ERROR("When linking program");

        free(info_log);

        return -1;
    }
    return 0;
}


shader_t shader_new(const char* source, uint32_t shader_type) {
    uint32_t shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    if(shader_check_for_errors(shader, shader_type)) {
        ERROR("When compiling shader");
    }

    return (shader_t) {.handle = shader};
}

shader_t shader_read_from_file(const char* path, uint32_t shader_type) {
    char* source;

    read_from_file(path, &source);

    shader_t shader = shader_new(source, shader_type);

    free(source);

    return shader;
}

program_t program_new(shader_t vertex, shader_t fragment) {
    uint32_t program = glCreateProgram();

    glAttachShader(program, vertex.handle);
    glAttachShader(program, fragment.handle);
    glLinkProgram(program);

    if(__program_check_for_errors(program)) {
        ERROR("When linking program");
        //TODO don't
        exit(-1);
    }

    glDeleteShader(vertex.handle);
    glDeleteShader(fragment.handle);

    return (program_t) {.handle = program};
}

void program_set_vec3(program_t program, const char* name, vec3_t vec) {
    //TODO cache

    int location = glGetUniformLocation(program.handle, name);

    if(location == -1) {
        ERROR("When setting uniforms");
        return;
    }

    glUniform3f(location, vec.x, vec.y, vec.z);
}

void program_set_matrix(program_t program, const char* name, mat4_t matrix) {
    //TODO cache

    int location = glGetUniformLocation(program.handle, name);

    if(location == -1) {
        ERROR("When setting uniforms");
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data);
}

void program_set_mvp(program_t program, mat4_t model, mat4_t view, mat4_t proj) {
    static const char* MODEL = "uModel";
    static const char* VIEW = "uView";
    static const char* PROJ = "uProjection";

    program_set_matrix(program, MODEL, model);
    program_set_matrix(program, VIEW, view);
    program_set_matrix(program, PROJ, proj);
}

void program_set_texture_unit(program_t program, const char* name, uint32_t unit) {
    int location = glGetUniformLocation(program.handle, name);

    if(location == -1) {
        ERROR("When setting uniforms");
        return;
    }

    glUniform1i(location, unit);
}

void program_destroy(program_t program) {
    glDeleteProgram(program.handle);
}

const char* __get_name_for_type(GLenum type) {
    switch (type)
    {
        case GL_FLOAT:
            return "FLOAT";
            break;
        case GL_FLOAT_MAT4:
            return "MAT4";
            break;
        case GL_INT:
            return "INT";
            break;
        case GL_SAMPLER_2D:
            return "SAMPLER2D";
            break;
        case GL_FLOAT_VEC3:
            return "VECTOR3";
            break;
        default:
            return "UNKNOWN";
    }
}

void debug__program_print_uniforms(program_t program) {
    int count;
    glGetProgramiv(program.handle, GL_ACTIVE_ATTRIBUTES, &count);

    int buffer_size = 16;
    char name[buffer_size];
    int size, length;
    GLenum type;

    printf("---\nATTRIBUTES\n");

    for(int i = 0; i < count; i++) {
        glGetActiveAttrib(program.handle, i, buffer_size, &length, &size, &type, name);

        printf("Attribute #%d: %s (%s)\n", i, name, __get_name_for_type(type));
    }

    glGetProgramiv(program.handle, GL_ACTIVE_UNIFORMS, &count);
    
    printf("---\nUNIFORMS\n");

    for (int i = 0; i < count; i++)
    {
        glGetActiveUniform(program.handle, i, buffer_size, &length, &size, &type, name);

        printf("Attribute #%d: %s (%s)\n", i, name, __get_name_for_type(type));
    }
}