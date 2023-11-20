#ifndef __vertex_map_h__
#define __vertex_map_h__

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "math/vec.h"
#include "renderer/vertex.h"

#define NPOS UINT32_MAX
#define MAP_DEFAULT_CAPACITY 50

typedef struct vertex_map_t vertex_map_t;

vertex_map_t* vertex_map_new();
void vertex_map_delete(vertex_map_t* map);

void map_insert_vertex(vertex_map_t* map, vertex_t key, uint32_t value);
uint32_t map_get_vertex(vertex_map_t* map, vertex_t key);

uint32_t vertex_hash(vertex_t vec);

inline bool vertex_is_zero(vertex_t v);
inline bool vertex_cmp(vertex_t a, vertex_t b);

#endif // __vertex_map_h__
