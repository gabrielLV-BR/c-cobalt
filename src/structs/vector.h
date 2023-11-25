#ifndef ____vector_h__
#define __vector_h__

#include "utils/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// DEFINITIONS

#define __VECTOR_DEFINE_STRUCT(type)                                \
    typedef struct type##_vector_t {                                \
        type *data;                                                 \
        int capacity, length;                                       \
    } type##_vector_t;

#define __VECTOR_DEFINE_FUNCS(type)                                 \
    type##_vector_t type##_vector_new(int initial_size);            \
    void type##_vector_append(type##_vector_t* vec, void* data);    \
    void type##_vector_destroy(type##_vector_t* vec);               \
    void type##_vector_fit(type##_vector_t* vec);

// IMPLEMENTATIONS

#define __VECTOR_IMPLEMENT_NEW(type)                                \
    type##_vector_t type##_vector_new(int initial_size) {           \
        type *data = calloc(initial_size, sizeof(type));            \
                                                                    \
        if(!data) {                                                 \
            ERROR("When allocating data for "type" vector");        \
            data = NULL;                                            \
            initial_size = -1;                                      \
        }                                                           \
                                                                    \
        return (vector_void_t) {                                    \
            .data = data,                                           \
            .capacity = initial_size,                               \
            .length = 0                                             \
        };                                                          \
    }

#define __VECTOR_IMPLEMENT_APPEND(type)                             \
    void type##_vector_append(type##_vector_t* vec, type data) {   \
        if(vec->capacity < (vec->length + 1)) {                     \
            int new_capacity = vec->capacity * 2;                   \
            vec->capacity = new_capacity;                           \
                                                                    \
            int next_size = vec->capacity * sizeof(type);           \
            vec->data = realloc(vec->data, next_size);              \
        }                                                           \
                                                                    \
        if(!vec->data) {                                            \
            ERROR("When appending to "type" vector");               \
        } else {                                                    \
            vec->data[vec->length++] = data;                        \
        }                                                           \
    }

#define __VECTOR_IMPLEMENT_DESTROY(type)                            \
    void type##_vector_destroy(type##_vector_t* vec) {              \
        for(int i = 0; i < vec->length; i++)                        \
            free(vec->data[i]);                                     \
        free(vec->data);                                            \
    }

#define __VECTOR_IMPLEMENT_FIT(type)                                \
    void type##_vector_fit(type##_vector_t* vec) {                  \
        realloc(vec->data, vec->length * sizeof(typedef));          \
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
