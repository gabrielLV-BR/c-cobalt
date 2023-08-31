#if !defined(VECTOR_H)
#define VECTOR_H

typedef struct vec_void_t {
    void** data;
    int capacity, length;
} vec_void_t;

vec_void_t vec_void_new(int initial_size);
void vec_void_append(vec_void_t* vec, void* data);
void vec_void_destroy(vec_void_t* vec);

#endif // VECTOR_H
