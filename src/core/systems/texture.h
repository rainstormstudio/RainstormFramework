/**
 * @file texture.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the texture
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_TEXTURE_H
#define RS_TEXTURE_H

#include <GL/glew.h>

class Texture {
    GLuint textureID_;
    int width_;
    int height_;
    int bitDepth_;
    const char* filePath_;

   public:
    Texture();
    Texture(const char* filePath);
    ~Texture();

    bool loadTexture();
    bool loadTextureAlpha();
    void use();
    void destroy();
};

#endif
