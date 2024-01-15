#ifndef ____vector_h__
#define __vector_h__

#include "utils/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// DEFINITIONS

#define __VECTOR_DEFINE_STRUCT(type)                                \
    typedef struct vector_##type {                                  \
        type *data;                                                 \
        size_t capacity, length;                                    \
    } vector_##type;

#define __VECTOR_DEFINE_FUNCS(type)                                 \
    vector_##type vector_new_##type(int initial_size);              \
    void vector_append_##type(vector_##type* vec, type data);       \
    void vector_destroy_##type(vector_##type* vec);                 \
    void vector_recursive_destroy_##type(vector_##type* vec);       \
    void vector_fit_##type(vector_##type* vec);

// IMPLEMENTATIONS

#define __VECTOR_IMPLEMENT_NEW(type)                                \
    vector_##type vector_new_##type(int initial_size) {             \
        type *data = calloc(initial_size, sizeof(type));            \
                                                                    \
        if(!data) {                                                 \
            ERROR("When creating vector");                          \
            data = NULL;                                            \
            initial_size = -1;                                      \
        }                                                           \
                                                                    \
        return (vector_##type) {                                    \
            .data = data,                                           \
            .capacity = initial_size,                               \
            .length = 0                                             \
        };                                                          \
    }

#define __VECTOR_IMPLEMENT_APPEND(type)                             \
    void vector_append_##type(vector_##type* vec, type data) {   \
        if(vec->capacity < (vec->length + 1)) {                     \
            vec->capacity *= 2;                                     \
            int next_size = vec->capacity * sizeof(type);           \
            vec->data = realloc(vec->data, next_size);              \
        }                                                           \
                                                                    \
        if(!vec->data) {                                            \
            ERROR("When appending to vector");                      \
        } else {                                                    \
            vec->data[vec->length++] = data;                        \
        }                                                           \
    }

#define __VECTOR_IMPLEMENT_DESTROY(type)                            \
    void vector_destroy_##type(vector_##type* vec) {                \
        free(vec->data);                                            \
    }

#define __VECTOR_IMPLEMENT_RECURSIVE_DESTROY(type)                  \
    void vector_recursive_destroy_##type(vector_##type* vec) {      \
        for(int i = 0; i < vec->length; i++)                        \
            free(vec->data[i]);                                     \
        free(vec->data);                                            \
    }

#define __VECTOR_IMPLEMENT_FIT(type)                                \
    void vector_fit_##type(vector_##type* vec) {                    \
        vec->data = realloc(vec->data, vec->length * sizeof(type)); \
    }

// USE THESE

#define VECTOR_DEFINE(type)                                         \
    __VECTOR_DEFINE_STRUCT(type)                                    \
    __VECTOR_DEFINE_FUNCS(type)

#define VECTOR_IMPLEMENT(type)                                      \
    __VECTOR_IMPLEMENT_NEW(type)                                    \
    __VECTOR_IMPLEMENT_APPEND(type)                                 \
    __VECTOR_IMPLEMENT_DESTROY(type)                                \
    __VECTOR_IMPLEMENT_FIT(type)     

#endif // __vector_h__
