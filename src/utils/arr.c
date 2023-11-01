#include "arr.h"

#include <stdlib.h>
#include <stdarg.h>

uint32_t* to_uint32_t_array(int num, ...) {
    va_list args;
    va_start(args, num);

    uint32_t* data = malloc(num * sizeof(uint32_t));

    for(int i = 0; i < num; i++)
        data[i] = va_arg(args, uint32_t);

    va_end(args);

    return data;
}
