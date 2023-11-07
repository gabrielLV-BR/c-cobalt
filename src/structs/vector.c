#include "vector.h"
#include "utils/error.h"

#include <stdlib.h>
#include <memory.h>

vector_void_t vector_void_new(int initial_size) {
    void* data = calloc(initial_size, sizeof(void*));

    if(!data) {
        ERROR("When allocating data for void vector");
        data = NULL;
        initial_size = -1;
    }

    return (vector_void_t) {
        .data = data,
        .capacity = initial_size,
        .length = 0
    };
}

void vector_void_append(vector_void_t* vec, void* data) {
    if(vec->capacity < (vec->length + 1)) { 
        vec->data = realloc(vec->data, vec->capacity * 2 * sizeof(void*));
    }

    if(!vec->data) {
        ERROR("When resizing void vector");
    } else {
        vec->data[vec->length++] = data;
    }
}

void vector_void_destroy(vector_void_t* vec) {
    for(int i = 0; i < vec->length; i++)
        free(vec->data[i]);
    
    free(vec->data);
}

void vector_void_fit(vector_void_t* vec) {
    // essentially trim
    realloc(vec->data, vec->length * sizeof(void*));
}