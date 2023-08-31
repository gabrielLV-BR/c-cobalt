#if !defined(MODEL_H)
#define MODEL_H

#include "math/transform.h"
#include "mesh.h"

typedef struct model_t {
    mesh_t* meshes;
    int num_meshes;

    transform_t transform;
} model_t;

model_t model_new(mesh_t* meshes, int num_meshes, transform_t transform);

#endif // MODEL_H
