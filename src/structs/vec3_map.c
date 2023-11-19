#include "vec3_map.h"

#define ISZERO(v) (v.x == 0 && v.y == 0 && v.z == 0)

typedef struct {
    vec3_t key;
    uint32_t value;
    index_linked_list_t* next;
} index_linked_list_t;

typedef struct {
    index_linked_list_t indices[MAP_DEFAULT_CAPACITY];
} vec3_map_t;

vec3_map_t* vec3_map_new() {
    vec3_map_t* map = calloc(1, sizeof(vec3_map_t));
    return map;
}

void index_linked_list_delete(index_linked_list_t* ll) {
    while(ll != NULL) {
        index_linked_list_t* next = ll->next;
        free(ll);
        ll = next;
    }
}

void vec3_map_delete(vec3_map_t* map) {
    for(int i = 0; i < MAP_DEFAULT_CAPACITY; i++) {
        index_linked_list_t* next = map->indices[i].next;

        if(next != NULL) index_linked_list_delete(next);
    }

    free(map);
}

void map_insert_vec3(vec3_map_t* map, vec3_t key, uint32_t value) {
    size_t index = vec3_hash(key);

    index_linked_list_t* index_list = &map->indices[index];

    if(ISZERO(index_list->key)) {
        // it's free, baby!
        index_list->key = key;
        index_list->value = value;
        index_list->next = NULL;
    } else {
        // taken, must insert into tail

        while (index_list->next == NULL) 
            index_list = index_list->next;

        index_list->next = malloc(sizeof(index_linked_list_t));
        index_list = index_list->next;

        index_list->key = key;
        index_list->value = value;
        index_list->next = NULL;
    }

}

uint32_t map_get_vec3(vec3_map_t* map, vec3_t key) {
    size_t index = vec3_hash(key);

    index_linked_list_t* node = &map->indices[index];

    while(node != NULL && vec3_cmp(node->key, key) == false)
        node = node->next;

    if(node == NULL) {
        return NPOS;
    }

    return node->value;
}

size_t vec3_hash(vec3_t vec) {
    // naive hash algorithm for vec
    // provided by yours truly, ChatGPT
    size_t _x = *((size_t*) &vec.x);
    size_t _y = *((size_t*) &vec.y);
    size_t _z = *((size_t*) &vec.z);

    return (_x ^ _y ^ _z) % MAP_DEFAULT_CAPACITY;
}

bool vec3_cmp(vec3_t a, vec3_t b) {
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}
