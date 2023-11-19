#include <stdio.h>
#include <stdint.h>

#include "vec3_map.h"

#define ISZERO(v) (v.x == 0 && v.y == 0 && v.z == 0)

struct list_node;

struct list_node {
    vec3_t key;
    uint32_t value;
    struct list_node* next;
};

typedef struct list_node linked_list_t;

typedef struct vec3_map_t {
    linked_list_t indices[MAP_DEFAULT_CAPACITY];
} vec3_map_t;

vec3_map_t* vec3_map_new() {
    vec3_map_t* map = calloc(1, sizeof(vec3_map_t));
    return map;
}

void index_linked_list_delete(linked_list_t* ll) {
    while(ll != NULL) {
        linked_list_t* next = ll->next;
        free(ll);
        ll = next;
    }
}

void vec3_map_delete(vec3_map_t* map) {
    for(int i = 0; i < MAP_DEFAULT_CAPACITY; i++) {
        linked_list_t* next = map->indices[i].next;

        if(next != NULL) index_linked_list_delete(next);
    }

    free(map);
}

void map_insert_vec3(vec3_map_t* map, vec3_t key, uint32_t value) {
    size_t index = vec3_hash(key);

    linked_list_t* index_list = &map->indices[index];

    if(ISZERO(index_list->key)) {
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

uint32_t map_get_vec3(vec3_map_t* map, vec3_t key) {
    size_t index = vec3_hash(key);

    linked_list_t* node = &map->indices[index];

    while(node != NULL && vec3_cmp(node->key, key) == false)
        node = node->next;

    if(node == NULL) {
        return NPOS;
    }

    return node->value;
}

inline uint32_t vec3_hash(vec3_t vec) {
    // naive hash algorithm for vec
    // provided by yours truly, ChatGPT
    uint32_t x = *((uint32_t*) &vec.x);
    uint32_t y = *((uint32_t*) &vec.y);
    uint32_t z = *((uint32_t*) &vec.z);

    uint32_t hash = 17;

    hash = 31 * hash + x;
    hash = 31 * hash + y;
    hash = 31 * hash + z;

    hash %= MAP_DEFAULT_CAPACITY;

    printf("HASH = {%ld}\n", hash);

    return hash;
}

inline bool vec3_cmp(vec3_t a, vec3_t b) {
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}
