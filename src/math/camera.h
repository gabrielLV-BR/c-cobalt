#if !defined(CAMERA_H)
#define CAMERA_H

#include "math/vector.h"

enum CAMERA_PROJECTION { PROJECTION_PERSPECTIVE, PROJECTION_ORTHOGRAPHIC };

typedef struct camera_t {
    enum CAMERA_PROJECTION projection;
    vec3_t position, target;
} camera_t;

camera_t camera_new(enum CAMERA_PROJECTION projection, vec3_t position);

void camera_look_at(camera_t* camera, vec3_t point);

mat4_t camera_get_view_matrix(camera_t* camera);

#endif // CAMERA_H
