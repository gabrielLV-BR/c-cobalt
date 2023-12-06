#include <stdlib.h>

#include "glad/glad.h"

#include "shader.h"
#include "renderer.h"

#include "utils/error.h"

GLFWwindow* __renderer_init_window(int width, int height, const char* title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, 0, 0);

    return window;
}

int __renderer_init_opengl(GLFWwindow* window) {
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    int width, height;

    glfwGetWindowSize(window, &width, &height);

    glViewport(0, 0, width, height);

    return 0;
}

void __renderer_load_default_programs(renderer_t* renderer) {
    // the order matters here
    // it should follow the texture_unit_t enum order

    // change manually 
    renderer->program_count = 2;

    renderer->programs = calloc(renderer->program_count, sizeof(program_t));

    // 0: solid color

    const char* color_shader_sources[] = {
        "assets/shaders/color.vert.glsl",
        "assets/shaders/color.frag.glsl",
    };

    {
        shader_t vert_shader = shader_read_from_file(color_shader_sources[0], GL_VERTEX_SHADER);
        shader_t frag_shader = shader_read_from_file(color_shader_sources[1], GL_FRAGMENT_SHADER);
        program_t program = program_new(vert_shader, frag_shader);

        renderer->programs[0] = program;
    }

    // 1: diffuse

    const char* diff_shader_sources[] = {
        "assets/shaders/diffuse.vert.glsl",
        "assets/shaders/diffuse.frag.glsl",
    };

    {
        shader_t vert_shader = shader_read_from_file(diff_shader_sources[0], GL_VERTEX_SHADER);
        shader_t frag_shader = shader_read_from_file(diff_shader_sources[1], GL_FRAGMENT_SHADER);
        program_t program = program_new(vert_shader, frag_shader);

        renderer->programs[1] = program;
    }
}

renderer_t renderer_new(int width, int height, const char* title) {
    renderer_t renderer = {0};
    
    GLFWwindow* window = __renderer_init_window(width, height, title);
    
    if(window == NULL) {
        ERROR("When creating GLFW window");
        goto END;
    }

    if(__renderer_init_opengl(window) != 0) {
        ERROR("When loading OpenGL");
        goto END;
    }

    __renderer_load_default_programs(&renderer);

    renderer.width = width;
    renderer.height = height;
    renderer.window = window;

END:

    return renderer;
}

void renderer_update_screen(renderer_t* renderer, int width, int height) {
    glViewport(0, 0, width, height);
    renderer->width = width;
    renderer->height = height;
}

void __renderer_bind_material(renderer_t* renderer, program_t program, material_t* material) {
    glUseProgram(program.handle);

    program_set_vec3(program, "uColor", material->color);

    for(int i = 0; i < material->map_count; i++) {
        program_set_texture_unit(program, texture_unit_name(i), i);
    }
}

void renderer_render(renderer_t* renderer, scene_t* scene, camera_t* camera) {
    mat4_t view_matrix = camera_get_view_matrix(camera);
    mat4_t perspective_matrix = mat4_identity();
    mat4_t model_matrix;

    for(int model_index = 0; model_index < scene->models.length; model_index++) {
        model_t* model = &scene->models.data[model_index];

        for(int mesh_index = 0; mesh_index < model->mesh_handle_count; mesh_index++) {
            uint32_t mesh_handle = model->mesh_handles[mesh_index];
            mesh_t* mesh = &scene->meshes.data[mesh_handle];

            uint32_t material_handle = mesh->material_handle;
            material_t* material = &scene->materials.data[material_handle];

            program_t program = renderer->programs[material->map_count];

            __renderer_bind_material(renderer, program, material);

            model_matrix = transform_get_model_matrix(&model->transform);
            program_set_mvp(
                program, 
                model_matrix, 
                view_matrix, 
                perspective_matrix
            );

            glBindVertexArray(mesh->vao);

            glDrawElements(
                GL_TRIANGLES,
                mesh->index_count,
                GL_UNSIGNED_INT,
                NULL
            );
        }
    }

    glUseProgram(0);
    glBindVertexArray(0);
}

void renderer_destroy(renderer_t* renderer) {
    for(int i = 0; i < renderer->program_count; i++) {
        program_destroy(renderer->programs[i]);
    }
}