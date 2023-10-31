#if !defined(RENDERER_H)
#define RENDERER_H

#include "mesh.h"
#include "model.h"

#include "math/camera.h"
#include "scene/scene.h"

#include <GLFW/glfw3.h>

typedef struct renderer_t {
    GLFWwindow* window;
    int width, height;
} renderer_t;

renderer_t renderer_new(int width, int height, const char* title);
void renderer_update_screen(renderer_t* renderer, int width, int height);

void renderer_render(renderer_t* renderer, scene_t* scene, camera_t* camera);

#endif // RENDERER_H
