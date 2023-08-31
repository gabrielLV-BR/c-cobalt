#if !defined(RENDERER_H)
#define RENDERER_H

#include "math/camera.h"
#include "math/transform.h"

#include "mesh.h"
#include "model.h"
#include "shader.h"

#include "structs/vector.h"

typedef struct draw_call_t {
    enum draw_mode { DRAW_CALL_MODE_2D, DRAW_CALL_MODE_3D } mode;

    struct {
        union {
            // not ours to free
            const model_t* model;
        };

        //TODO put in data for 2D mode 
    };
} draw_call_t;

typedef struct render_pass_t {
    program_t default_program;
    mat4_t projection_matrix, view_matrix;
    vector_void_t draw_calls;
} render_pass_t;

//

typedef struct renderer_t {
    int is_rendering;
    int width, height;
    render_pass_t render_pass;
} renderer_t;

renderer_t renderer_new(int width, int height);
void renderer_update_screen(renderer_t* renderer, int width, int height);

void renderer_begin_rendering(renderer_t* renderer, camera_t* camera);
void renderer_render_model(renderer_t* renderer, model_t* model);
void renderer_end_rendering(renderer_t* renderer);

#endif // RENDERER_H
