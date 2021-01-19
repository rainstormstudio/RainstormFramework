/**
 * @file mesh.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the mesh component
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_C_MESH_H
#define RS_C_MESH_H

#include <GL/glew.h>

#include "../core/OCcore/component.h"

class Mesh : public Component {
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLsizei indexCount;

    size_t shaderIndex;

    void calculateNormals(GLfloat *vertices, GLuint *indices, GLuint nVertices,
                          GLuint nIndices);
    void createMesh(GLfloat *vertices, GLuint *indices, GLuint nVertices,
                    GLuint nIndices);

    void destroy();

   public:
    enum Shape { NONE, PLANE, CUBE, SPHERE, CUSTOM };

    Mesh(Shape shape = NONE, size_t shaderIndex = 0);
    ~Mesh() override { destroy(); }

    void initialize() override {}
    void update(double deltaTime) override {}
    void render(double deltaTime) override;
};

#endif
