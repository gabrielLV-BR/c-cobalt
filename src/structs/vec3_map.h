#ifndef __vec3_map_h__
#define __vec3_map_h__

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "math/vec.h"

#define NPOS UINT32_MAX
#define MAP_DEFAULT_CAPACITY 50

typedef struct vec3_map_t vec3_map_t;

vec3_map_t* vec3_map_new();
void vec3_map_delete(vec3_map_t* map);

void map_insert_vec3(vec3_map_t* map, vec3_t key, uint32_t value);
uint32_t map_get_vec3(vec3_map_t* map, vec3_t key);
uint32_t vec3_hash(vec3_t vec);
bool vec3_cmp(vec3_t a, vec3_t b);

#endif // __vec3_map_h__
