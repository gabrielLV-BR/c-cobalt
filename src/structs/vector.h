#ifndef ____vector_h__
#define __vector_h__

#define __VECTOR_DEFINE_STRUCT(type)                                \
    typedef struct type##_vector_t {                                \
        type##* data;                                               \
        int capacity, length;                                       \
    } type##_vector_t;

#define __VECTOR_DEFINE_FUNCS(type)                                 \
    type##_vector_t type##_vector_new(int initial_size);            \
    void type##_vector_append(type##_vector_t* vec, void* data);    \
    void type##_vector_destroy(type##_vector_t* vec);               \
    void type##_vector_fit(type##_vector_t* vec);

#define VECTOR_DEFINE(type)                                         \
    __VECTOR_DEFINE_STRUCT(type)                                    \
    __VECTOR_DEFINE_FUNCS(type)

#endif // __vector_h__
