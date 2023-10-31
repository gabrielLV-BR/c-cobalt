#ifndef __texture_h__
#define __texture_h__

#include <stdint.h>

#include "renderer/material.h"

typedef struct {
    uint32_t handle;
    const char* path;
    int width, height, channels;
} texture_t;

texture_t texture_load_from_file(const char* path);
uint32_t texture_upload(int width, int height, int channels, unsigned char* data);

void texture_destroy(texture_t* texture);
void texture_bind(texture_t* texture, texture_unit_t unit);
void texture_unbind(texture_t* texture);

const char* texture_unit_name(texture_unit_t index);

#endif // __texture_h__
