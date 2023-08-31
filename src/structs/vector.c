#include "vector.h"
#include "utils/error.h"

#include <stdio.h>
#include <memory.h>

vec_void_t vec_void_new(int initial_size) {
    void* data = calloc(initial_size, sizeof(void*));

    if(!data) {
        ERROR("When allocating data for void vector");
        data = NULL;
        initial_size = -1;
    }

    return (vec_void_t) {
        .data = data,
        .capacity = initial_size,
        .length = 0
    };
}

void vec_void_append(vec_void_t* vec, void* data) {
    if(vec->capacity < (vec->length + 1)) { 
        vec->data = reallocarray(vec->data, vec->capacity * 2, sizeof(void*));
    }

    vec->data[vec->length++] = data;
}

void vec_void_destroy(vec_void_t* vec) {
    for(int i = 0; i < vec->length; i++)
        free(vec->data[i]);
    
    free(vec->data);
}