#include "mesh.h"

#include "../core/OCcore/object.h"
#include "../core/systems/graphics.h"
#include "../debug/debug.h"
#include "transform.h"

Mesh::Mesh(Shape shape, size_t shaderIndex) : shaderIndex{shaderIndex} {
    vao = 0;
    vbo = 0;
    ibo = 0;
    indexCount = 0;

    switch (shape) {
        case Shape::NONE: {
            break;
        }
        case Shape::PLANE: {
            GLuint nPlaneIndices = 6;
            GLuint planeIndices[6] = {0, 1, 2, 2, 3, 0};
            GLuint nPlaneVertices = 12;
            GLfloat planeVertices[12] = {-1.0f, 1.0f,  0.0f,  1.0f,
                                         1.0f,  0.0f,  1.0f,  -1.0f,
                                         0.0f,  -1.0f, -1.0f, 0.0f};
            createMesh(planeVertices, planeIndices, nPlaneVertices,
                       nPlaneIndices);
            break;
        }
        case Shape::CUBE: {
            // cube
            GLuint nCubeIndices = 36;
            GLuint cubeIndices[36] = {0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1,
                                      7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4,
                                      4, 5, 1, 1, 0, 4, 3, 2, 6, 6, 7, 3};
            GLuint nCubeVertices = 24;
            GLfloat cubeVertices[24] = {-1.0, -1.0, 1.0,  1.0,  -1.0, 1.0,
                                        1.0,  1.0,  1.0,  -1.0, 1.0,  1.0,
                                        -1.0, -1.0, -1.0, 1.0,  -1.0, -1.0,
                                        1.0,  1.0,  -1.0, -1.0, 1.0,  -1.0};
            createMesh(cubeVertices, cubeIndices, nCubeVertices, nCubeIndices);
            break;
        }
    }
}

void Mesh::createMesh(GLfloat *vertices, GLuint *indices, GLuint nVertices,
                      GLuint nIndices) {
    indexCount = nIndices;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * nIndices,
                 indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * nVertices, vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render(double deltaTime) {
    DEBUG_MSG_INDENT("mesh component render", 1);

    Transform *transform = owner->getComponent<Transform>();
    graphics::applyModel(transform->getModel());

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::destroy() {
    if (ibo) {
        glDeleteBuffers(1, &ibo);
        ibo = 0;
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }
    if (vao) {
        glDeleteBuffers(1, &vao);
        vao = 0;
    }
    indexCount = 0;
}
