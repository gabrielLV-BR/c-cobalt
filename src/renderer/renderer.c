#include "glad/glad.h"

#include "renderer.h"

#include "utils/error.h"

renderer_t renderer_new(int width, int height, const char* title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, 0, 0);

    if(window == NULL) {
        ERROR("When creating GLFW window");
        goto END;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ERROR("When loading OpenGL");

        window = NULL;

        goto END;
    }

    glViewport(0, 0, width, height);

END:

    return (renderer_t) {
        .width = width,
        .height = height,
        .window = window
    };
}

void renderer_update_screen(renderer_t* renderer, int width, int height) {
    glViewport(0, 0, width, height);
    renderer->width = width;
    renderer->height = height;
}

void renderer_render(renderer_t* renderer, scene_t* scene, camera_t* camera) {

}