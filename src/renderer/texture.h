#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <stdint.h>

enum TEXTURE_UNIT {
    TEXTURE_UNIT_DIFFUSE = 0,
    TEXTURE_UNIT_NORMAL = 1
};

typedef struct texture_t {
    uint32_t handle;
    const char* path;
    int width, height, channels;
} texture_t;

texture_t texture_load_from_file(const char* path);
uint32_t texture_upload(int width, int height, int channels, unsigned char* data);

void texture_destroy(texture_t* texture);
void texture_bind(texture_t* texture, enum TEXTURE_UNIT unit);
void texture_unbind(texture_t* texture);

#endif // TEXTURE_H
