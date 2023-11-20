#include <stdio.h>
#include <stdint.h>

#include "vertex_map.h"

struct list_node;

struct list_node {
    vertex_t key;
    uint32_t value;
    struct list_node* next;
};

typedef struct list_node linked_list_t;

typedef struct vertex_map_t {
    linked_list_t indices[MAP_DEFAULT_CAPACITY];
} vertex_map_t;

vertex_map_t* vertex_map_new() {
    vertex_map_t* map = calloc(1, sizeof(vertex_map_t));
    return map;
}

void index_linked_list_delete(linked_list_t* ll) {
    while(ll != NULL) {
        linked_list_t* next = ll->next;
        free(ll);
        ll = next;
    }
}

void vertex_map_delete(vertex_map_t* map) {
    for(int i = 0; i < MAP_DEFAULT_CAPACITY; i++) {
        linked_list_t* next = map->indices[i].next;

        if(next != NULL) index_linked_list_delete(next);
    }

    free(map);
}

void map_insert_vertex(vertex_map_t* map, vertex_t key, uint32_t value) {
    size_t index = vertex_hash(key);

    linked_list_t* index_list = &map->indices[index];

    if(vertex_is_zero(index_list->key)) {
        // it's free, baby!
        index_list->key = key;
        index_list->value = value;
        index_list->next = NULL;
    } else {
        // taken, must insert into tail
        while (index_list->next != NULL) 
            index_list = index_list->next;

        index_list->next = malloc(sizeof(linked_list_t));
        index_list = index_list->next;

        index_list->key = key;
        index_list->value = value;
        index_list->next = NULL;
    }
}

uint32_t map_get_vertex(vertex_map_t* map, vertex_t key) {
    size_t index = vertex_hash(key);

    linked_list_t* node = &map->indices[index];

    while(node != NULL && vertex_cmp(node->key, key) == false)
        node = node->next;

    if(node == NULL) {
        return NPOS;
    }

    return node->value;
}

inline uint32_t vertex_hash(vertex_t vec) {
    uint32_t hash = 69;

    hash += 34 * vec3_hash(vec.position);
    hash += 23 * vec3_hash(vec.normal);
    hash += 12 * vec2_hash(vec.uv);

    hash %= MAP_DEFAULT_CAPACITY;

    return hash;
}

inline bool vertex_is_zero(vertex_t v) {
    static vertex_t zero = {0};

    return vertex_cmp(v, zero);
}

inline bool vertex_cmp(vertex_t a, vertex_t b) {    
    return vec3_cmp(a.position, b.position)
        && vec3_cmp(a.normal, b.normal)
        && vec2_cmp(a.uv, b.uv);
}
