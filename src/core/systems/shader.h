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

class Shader {
    GLuint shaderID_;
    GLuint uniformProjection_;
    GLuint uniformModel_;
    GLuint uniformView_;

    void compileShader(const char* vCode, const char* fCode);
    void addShader(GLuint program, const char* code, GLenum shaderType);

   public:
    Shader();
    ~Shader();

    void createFromString(const char* vCode, const char* fCode);
    void createFromFiles(const char* vCodePath, const char* fCodePath);

    GLuint uniformProjection();
    GLuint uniformModel();
    GLuint uniformView();

    void use();
    void destroy();
};

#endif
