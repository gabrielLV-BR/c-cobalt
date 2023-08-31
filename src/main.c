#include <stdio.h>
#include <stdint.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "math/matrix.h"
#include "renderer/mesh.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/renderer.h"

#include "utils/error.h"

void window_resize_callback(GLFWwindow* window, int width, int height);

int main(void) {
    int WIDTH = 500,
        HEIGHT = 500;
    
    const char* TITLE = "Hello";

    if(!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if(!rendering_init(window)) {
        ERROR("When initializing rendering");
    }

    renderer_t renderer = renderer_new(WIDTH, HEIGHT);

    glfwSetWindowUserPointer(window, &renderer);

    glfwSetWindowSizeCallback(window, window_resize_callback);

    shader_t vertex = shader_read_from_file(
        "assets/shaders/basic.vert.glsl", GL_VERTEX_SHADER
    );

    shader_t fragment = shader_read_from_file(
        "assets/shaders/basic.frag.glsl", GL_FRAGMENT_SHADER
    );

    program_t program = program_new(vertex, fragment);

    float vertices[] = {
        // positions         // texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left 
    };

    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glCullFace(GL_BACK);

    mesh_t mesh = mesh_new(vertices, sizeof vertices / sizeof(float), indices, sizeof indices / sizeof(uint32_t));

    texture_t texture = texture_load_from_file("assets/textures/chessbloody.png");

    glViewport(0, 0, 500, 500);
    glClearColor(0.2, 0.6, 0.9, 1.0);
    
    //

    mat4_t model_matrix = mat4_identity();
    mat4_t view_matrix = mat4_identity();
    mat4_t projection_matrix = mat4_identity();

    double now = glfwGetTime();
    double last_time = now;
    double delta = 0.0;

    double accum = 0.0;

    while(!glfwWindowShouldClose(window)) {

        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        accum += delta;

        // printf("%lf\n", delta);

        model_matrix = mat4_rotate_x(model_matrix, delta / 100.0);

        glClear(GL_COLOR_BUFFER_BIT);

        program_print_uniforms(program);

        glUseProgram(program.handle);

        texture_bind(&texture, TEXTURE_UNIT_DIFFUSE);

        program_set_texture_unit(program, "texture1", TEXTURE_UNIT_DIFFUSE);
        program_set_matrix(program, "uModel", model_matrix);
        program_set_matrix(program, "uView", view_matrix);
        program_set_matrix(program, "uProjection", projection_matrix);

        glBindVertexArray(mesh.vao);

        glDrawElements(
            GL_TRIANGLES,
            mesh.index_count,
            GL_UNSIGNED_INT,
            mesh.indices
        );

        texture_unbind(&texture);
        glUseProgram(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    mesh_destroy(&mesh);
    texture_destroy(&texture);
    program_destroy(program);

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

void window_resize_callback(GLFWwindow* window, int width, int height) {
    renderer_t* renderer = (renderer_t*) glfwGetWindowUserPointer(window);
    renderer_update_screen(renderer, width, height);
}