#include "texture.h"

#include "../../debug/debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../thirdParty/stb_image/stb_image.h"

Texture::Texture() {
    textureID_ = 0;
    width_ = 0;
    height_ = 0;
    bitDepth_ = 0;
    filePath_ = "";
}

Texture::Texture(const char* filePath) : filePath_{filePath} {
    textureID_ = 0;
    width_ = 0;
    height_ = 0;
    bitDepth_ = 0;
}

Texture::~Texture() { destroy(); }

bool Texture::loadTexture() {
    unsigned char* texData =
        stbi_load(filePath_, &width_, &height_, &bitDepth_, 0);
    if (!texData) {
        DEBUG_ERROR("Failed to load image: " + std::string(filePath_));
        return false;
    }

    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);

    return true;
}

bool Texture::loadTextureAlpha() {
    unsigned char* texData =
        stbi_load(filePath_, &width_, &height_, &bitDepth_, 0);
    if (!texData) {
        DEBUG_ERROR("Failed to load image: " + std::string(filePath_));
        return false;
    }

    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);

    return true;
}

void Texture::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_);
}

void Texture::destroy() {
    glDeleteTextures(1, &textureID_);
    textureID_ = 0;
    width_ = 0;
    height_ = 0;
    bitDepth_ = 0;
    filePath_ = "";
}
