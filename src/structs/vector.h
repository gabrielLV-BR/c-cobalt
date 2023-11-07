#if !defined(VECTOR_H)
#define VECTOR_H

typedef struct vector_void_t {
    void** data;
    int capacity, length;
} vector_void_t;

vector_void_t vector_void_new(int initial_size);
void vector_void_append(vector_void_t* vec, void* data);
void vector_void_destroy(vector_void_t* vec);
void vector_void_fit(vector_void_t* vec);

#endif // VECTOR_H
