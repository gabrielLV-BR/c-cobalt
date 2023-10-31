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
    renderer->program_count = 1;

    renderer->programs = calloc(renderer->program_count, sizeof(program_t));

    // 0: diffuse

    static const char* diff_shader_sources[] = {
        "assets/shaders/basic.vert.glsl",
        "assets/shaders/basic.frag.glsl",
    };

    {
        shader_t vert_shader = shader_read_from_file(diff_shader_sources[0], GL_VERTEX_SHADER);
        shader_t frag_shader = shader_read_from_file(diff_shader_sources[1], GL_FRAGMENT_SHADER);
        program_t program = program_new(vert_shader, frag_shader);

        renderer->programs[0] = program;
    }
}

renderer_t renderer_new(int width, int height, const char* title) {

    renderer_t renderer = {0};
    
    GLFWwindow* window = __renderer_init_window(width, height, title);
    
    if(window == NULL) {
        ERROR("When creating GLFW window");
        goto END;
    }

    if(!__renderer_init_opengl(window)) {
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

void __renderer_bind_material(renderer_t* renderer, material_t* material) {
    uint32_t material_program = material->map_count - 1;

    if(material_program > renderer->program_count) {
        ERROR("When binding material to program on renderer");
        return;
    }

    program_t program = renderer->programs[material_program];

    for(int i = 0; i < material->map_count; i++) {
        program_set_texture_unit(program, texture_unit_name(i), i);
    }
}

void renderer_render(renderer_t* renderer, scene_t* scene, camera_t* camera) {
    for(int i = 0; i < scene->models.length; i++) {
        model_t* model = scene->models.data[i];

        for(int j = 0; j < model->mesh_handle_count; j++) {
            mesh_t* mesh = model->mesh_handles[j];

            __renderer_bind_material(renderer, &mesh->material);

            glBindVertexArray(mesh->vao);

            glDrawElements(
                GL_TRIANGLES,
                mesh->index_count,
                GL_UNSIGNED_INT,
                0
            );
        }
    }
}