#include "camera.h"

#include "math/vector.h"
#include "math/matrix.h"

camera_t camera_new(enum CAMERA_PROJECTION projection, vec3_t position) {
    return (camera_t) {
        .projection = projection,
        .position = position,
        .target = vec3_zero(),
    };
}

void camera_look_at(camera_t* camera, vec3_t point) {
    // look at
    camera->target = point;
}

mat4_t camera_get_view_matrix(camera_t* camera) {
    // calculate up vector
    vec3_t up = {0, 1, 0};
    vec3_t direction = vec3_normalize(vec3_sub(camera->target, camera->position));
    vec3_t right = vec3_cross(up, direction);
    up = vec3_cross(direction, right);

    mat4_t view = mat4_look_at(&direction, &up, &right, &camera->target);

    return view;
}