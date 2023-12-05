#include <stdio.h>
#include "vertex_map.h"

inline uint32_t __vertex_hash(vertex_t vec);
inline bool __vertex_cmp(vertex_t a, vertex_t b);

void __linked_list_delete(linked_list_t* ll);
void __linked_list_append(linked_list_t* ll, vertex_t key, uint32_t value);

//

vertex_map_t vertex_map_new() {
    vertex_map_t map;
    map.indices = calloc(MAP_DEFAULT_CAPACITY, sizeof(linked_list_t*));
    return map;
}

void vertex_map_delete(vertex_map_t map) {
    for(int i = 0; i < MAP_DEFAULT_CAPACITY; i++) {
        linked_list_t* node = map.indices[i];

        if(node != NULL) __linked_list_delete(node);
    }
}

void vertex_map_insert(vertex_map_t* map, vertex_t key, uint32_t value) {
    uint32_t index = __vertex_hash(key);

    linked_list_t* node = malloc(sizeof(linked_list_t));
    node->key = key;
    node->value = value;
    node->next = NULL;

    if(map->indices[index] == NULL) {
        map->indices[index] = node;
    } else {
        node->next = map->indices[index];
        map->indices[index] = node;
    }
}

uint32_t vertex_map_get(vertex_map_t* map, vertex_t key) {
    uint32_t index = __vertex_hash(key);

    linked_list_t* node = map->indices[index];
    while(node != NULL) {
        if(__vertex_cmp(node->key, key) == true) {
            return node->value;
        }
        node = node->next;
    }

    return NOT_FOUND;
}

// vertex funcs

inline uint32_t __vertex_hash(vertex_t vec) {
    // hehe nice
    uint32_t hash = 69;

    hash += 34 + vec3_hash(vec.position) * hash;
    hash += 23 + vec3_hash(vec.normal) * hash;
    hash += 12 + vec2_hash(vec.uv) * hash;

    hash %= MAP_DEFAULT_CAPACITY;

    return hash;
}

inline bool __vertex_cmp(vertex_t a, vertex_t b) {    
    return vec3_cmp(a.position, b.position)
        && vec3_cmp(a.normal, b.normal)
        && vec2_cmp(a.uv, b.uv);
}

// linked list
//TODO put this into its own file, will be useful in future

void __linked_list_delete(linked_list_t* ll) {
    while(ll != NULL) {
        linked_list_t* next = ll->next;
        free(ll);
        ll = next;
    }
}