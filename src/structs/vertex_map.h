#ifndef __vertex_map_h__
#define __vertex_map_h__

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "math/vec.h"
#include "renderer/vertex.h"

#define NOT_FOUND UINT32_MAX
#define MAP_DEFAULT_CAPACITY 50

typedef struct linked_list_t {
    vertex_t key;
    uint32_t value;
    struct linked_list_t* next;
} linked_list_t;

typedef struct vertex_map_t {
    linked_list_t** indices;
} vertex_map_t;

vertex_map_t vertex_map_new();
void vertex_map_delete(vertex_map_t* map);

void vertex_map_insert(vertex_map_t* map, vertex_t key, uint32_t value);
uint32_t vertex_map_get(vertex_map_t* map, vertex_t key);

// debug

void debug__vertex_map_print(vertex_map_t* map);

#endif // __vertex_map_h__
