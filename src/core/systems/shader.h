/**
 * @file shader.h
 * @author Daniel Hongyu Ding
 * @brief This file defines a shader
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_SHADER_H
#define RS_SHADER_H

#include <GL/glew.h>

#include "../../utilities/includes.h"

class Shader {
    GLuint shaderID_;

    void compileShader(const char* vCode, const char* fCode);
    void addShader(GLuint program, const char* code, GLenum shaderType);

   public:
    Shader();
    ~Shader();

    void createFromString(const char* vCode, const char* fCode);
    void createFromFiles(const char* vCodePath, const char* fCodePath);

    void use();
    void destroy();

   public:
    GLuint getUniform(const std::string& name);
};

#endif
