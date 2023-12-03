#include <stdio.h>

#include "vertex_map.h"

typedef struct linked_list_t {
    bool used;
    vertex_t key;
    uint32_t value;
    struct linked_list_t* next;
} linked_list_t;

typedef struct vertex_map_t {
    linked_list_t indices[MAP_DEFAULT_CAPACITY];
} vertex_map_t;

// forward decl

inline uint32_t __vertex_hash(vertex_t vec);
inline bool __vertex_is_zero(vertex_t v);
inline bool __vertex_cmp(vertex_t a, vertex_t b);

void __linked_list_delete(linked_list_t* ll);
void __linked_list_append(linked_list_t* ll, vertex_t key, uint32_t value);

//

vertex_map_t* vertex_map_new() {
    vertex_map_t* map = calloc(1, sizeof(vertex_map_t));
    return map;
}

void vertex_map_delete(vertex_map_t* map) {
    for(int i = 0; i < MAP_DEFAULT_CAPACITY; i++) {
        linked_list_t* next = map->indices[i].next;

        if(next != NULL) __linked_list_delete(next);
    }

    free(map);
}

void vertex_map_insert(vertex_map_t* map, vertex_t key, uint32_t value) {
    uint32_t index = __vertex_hash(key);

    linked_list_t* index_list = &map->indices[index];

    if(index_list->used == false) {
        // it's free, baby!
        index_list->used = true;
        index_list->key = key;
        index_list->value = value;
        index_list->next = NULL;
    } else {
        // taken, must insert into tail
        __linked_list_append(index_list, key, value);
    }
}

uint32_t vertex_map_get(vertex_map_t* map, vertex_t key) {
    uint32_t index = __vertex_hash(key);

    for(linked_list_t* node = &map->indices[index]; node != NULL; node = node->next) {
        if(__vertex_cmp(node->key, key) == true) {
            return node->value;
        }
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

    printf("Hash = %u\n", hash);

    return hash;
}

inline bool __vertex_is_zero(vertex_t v) {
    static vertex_t zero = {0};

    return __vertex_cmp(v, zero);
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

void __linked_list_append(linked_list_t* ll, vertex_t key, uint32_t value) {
    while (ll->next != NULL) 
        ll = ll->next;

    ll->next = malloc(sizeof(linked_list_t));
    ll = ll->next;

    ll->key = key;
    ll->value = value;
    ll->next = NULL;
}