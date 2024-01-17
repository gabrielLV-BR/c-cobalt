#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#include "math/matrix.h"
#include "math/camera.h"
#include "renderer/mesh.h"
#include "renderer/model.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/renderer.h"
#include "loader/mesh_loader.h"

#include "utils/error.h"
#include "utils/arr.h"
#include "utils/file.h"

void window_resize_callback(GLFWwindow* window, int width, int height);

int main() {
    int WIDTH = 500,
        HEIGHT = 500;
    
    const char* TITLE = "OpenGL Window";

    if(!glfwInit()) {
        return -1;
    }

    renderer_t renderer = renderer_new(WIDTH, HEIGHT, TITLE);

    if(renderer.window == NULL) {
        return -1;
    }

    glfwSetWindowUserPointer(renderer.window, &renderer);

    glfwSetWindowSizeCallback(renderer.window, window_resize_callback);

    glViewport(0, 0, 500, 500);
    glClearColor(0.2, 0.6, 0.9, 1.0);
    
    //

    camera_t camera;
    camera.fov = 80;
    camera.far_plane = 1000;
    camera.near_plane = 0.1;
    camera.position = (vec3_t){0, 1, 2};
    camera.target = (vec3_t){0, 0, 0};
    camera.projection = mat4_perspective(90.0, (float)WIDTH / (float)HEIGHT, 0.1, 1000.0);

    //

    scene_t scene = scene_new();

    // example model

    // material
    texture_t texture = texture_load_from_file("assets/textures/chessbloody.png");

    material_t textured_material = {
        .color = (vec3_t) {1},
        .map_count = 1,
        .map_handles = to_uint32_t_array(texture.handle)
    };

    material_t colored_material = {
        .color = vec3_new(1.0, 1.0, 1.0),
        .map_count = 0,
        .map_handles = NULL
    };

    uint32_t textured_material_handle = scene_upload_material(&scene, textured_material);
    uint32_t colored_material_handle = scene_upload_material(&scene, colored_material);

    mesh_t mesh = mesh_loader_load_from_file("assets/models/cube.obj");
    mesh.material_handle = colored_material_handle;

    vertex_t vertices[] = {
        { {-0.5, -0.5, 0.0}, vec3_zero(), vec2_zero() },
        { {0.0, 0.5, 0.0},  vec3_zero(), vec2_zero() },
        { {0.5, -0.5, 0.0},  vec3_zero(), vec2_zero() },
    };

    uint32_t indices[] = { 0, 1, 2 };

    mesh_t mesh2 = mesh_new(vertices, 3, indices, 3, colored_material_handle);

    uint32_t mesh_handle = scene_upload_mesh(&scene, mesh);
    uint32_t mesh_handle2 = scene_upload_mesh(&scene, mesh2);

    model_t model = {
        .mesh_handle_count = 1,
        .mesh_handles = &mesh_handle,
        .transform = transform_identity()
    };

    scene_upload_model(&scene, model);
    //

    double now = glfwGetTime();
    double last_time = now;
    double delta = 0.0;

    while(!glfwWindowShouldClose(renderer.window)) {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        glClear(GL_COLOR_BUFFER_BIT);

        renderer_render(
            &renderer,
            &scene,
            &camera
        );

        glfwPollEvents();
        glfwSwapBuffers(renderer.window);
    }

    scene_destroy(scene);
    renderer_destroy(&renderer);

    glfwDestroyWindow(renderer.window);
    glfwTerminate();
    
    return 0;
}

void window_resize_callback(GLFWwindow* window, int width, int height) {
    renderer_t* renderer = (renderer_t*) glfwGetWindowUserPointer(window);
    renderer_update_screen(renderer, width, height);
}
