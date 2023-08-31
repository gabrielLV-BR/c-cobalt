#include "glad/glad.h"

#include "renderer.h"
#include "utils/error.h"
#include "structs/vector.h"

static program_t DEFAULT_3D_PROGRAM;

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
    render_pass_t render_pass;

    render_pass.default_program = DEFAULT_3D_PROGRAM;
    render_pass.draw_calls = vector_void_new(5);
    
    glViewport(0, 0, width, height);

    return (renderer_t) {
        .width = width,
        .height = height,
        .is_rendering = 0,
        .render_pass = render_pass
    };
}

void renderer_update_screen(renderer_t* renderer, int width, int height) {
    glViewport(0, 0, width, height);
    renderer->width = width;
    renderer->height = height;
}

void renderer_begin_rendering(renderer_t* renderer, camera_t* camera) {
    renderer->render_pass.view_matrix = camera_get_view_matrix(camera);

    mat4_t projection_matrix;

   if(camera->projection == PROJECTION_PERSPECTIVE) {
        projection_matrix = mat4_perspective(
            camera->fov, ((float)renderer->height/(float)renderer->width),
            camera->near_plane, camera->far_plane
        );
    } else {
        WARNING("When choosing projection mode");
        return;
    }

    renderer->render_pass.projection_matrix = projection_matrix;
}

void renderer_render_model(renderer_t* renderer, model_t* model) {
    
}

void renderer_end_rendering(renderer_t* renderer) {

}