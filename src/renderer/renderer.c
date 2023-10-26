#include "glad/glad.h"

#include "renderer.h"

#include "utils/error.h"

int rendering_init(GLFWwindow* window) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    return 0;
}

renderer_t renderer_new(int width, int height) {
    glViewport(0, 0, width, height);

    return (renderer_t) {
        .width = width,
        .height = height,
    };
}

void renderer_update_screen(renderer_t* renderer, int width, int height) {
    glViewport(0, 0, width, height);
    renderer->width = width;
    renderer->height = height;
}

void renderer_render(renderer_t* renderer, scene_t* scene, camera_t* camera) {

}