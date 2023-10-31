#include "renderer/texture.h"
#include "renderer/material.h"
#include "utils/error.h"

#include "stb/stb_image.h"
#include "glad/glad.h"

texture_t texture_load_from_file(const char* path) {
    int width, height, channels;

    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

    texture_t texture = {
        .handle = texture_upload(width, height, channels, data),
        .path = path,
        .width = width,
        .height = height,
        .channels = channels
    };

    stbi_image_free(data);

    return texture;
}

uint32_t texture_upload(int width, int height, int channels, unsigned char* data) {
    if(!data) {
        ERROR("When uploading texture");
        return 0;
    }

    uint32_t handle;

    static const uint32_t CHANNELS_TO_ENUM[] = {
        0, // padding
        GL_R8,
        GL_RG,
        GL_RGB,
        GL_RGBA
    };

    if(channels > 4) {
        WARNING("When setting texture channels");
        channels = 4;
    }

    glGenTextures(1, &handle);
    
    glBindTexture(GL_TEXTURE_2D, handle);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 
        0, CHANNELS_TO_ENUM[channels], GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    return handle;
}

void texture_destroy(texture_t* texture) {
    glDeleteTextures(1, &texture->handle);
}

void texture_bind(texture_t* texture, texture_unit_t unit) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void texture_unbind(texture_t* texture) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

const char* texture_unit_name(texture_unit_t index) {
    switch(index) {
        case 0:
            return "uDiffuseTexture";
        case 1:
            return "uNormalTexture";
        default: 
            ERROR("When getting texture name");
    }

    return NULL;
}