#include "mesh.h"

#include "../core/OCcore/object.h"
#include "../core/OCcore/ocManager.h"
#include "../core/systems/graphics.h"
#include "../debug/debug.h"
#include "camera.h"
#include "light.h"
#include "material.h"
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
            // plane
            GLuint nPlaneIndices = 6;
            GLuint planeIndices[6] = {0, 1, 2,

                                      0, 2, 3};
            GLuint nPlaneVertices = 32;
            GLfloat planeVertices[32] = {
                // x y z,           u v,        nx ny nz
                -1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0f,  0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

            calculateNormals(planeVertices, planeIndices, nPlaneVertices,
                             nPlaneIndices);
            createMesh(planeVertices, planeIndices, nPlaneVertices,
                       nPlaneIndices);
            break;
        }
        case Shape::CUBE: {
            // cube
            GLuint nCubeIndices = 36;
            GLuint cubeIndices[36] = {2,  1,  0,

                                      3,  1,  2,

                                      5,  7,  6,

                                      6,  4,  5,

                                      11, 15, 9,

                                      15, 13, 9,

                                      14, 10, 8,

                                      12, 14, 8,

                                      16, 17, 20,

                                      17, 21, 20,

                                      22, 23, 19,

                                      18, 22, 19};
            GLuint nCubeVertices = 192;
            GLfloat cubeVertices[192] = {
                // x y z,         u v,        nx ny nz
                -1.0, -1.0, 1.0,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0, 1.0,  1.0,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0,  -1.0, 1.0,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                1.0,  1.0,  1.0,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                -1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0, 1.0,  -1.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0,  -1.0, -1.0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                1.0,  1.0,  -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                -1.0, -1.0, 1.0,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                -1.0, 1.0,  1.0,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                1.0,  -1.0, 1.0,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0,  1.0,  1.0,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0, -1.0, -1.0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0, 1.0,  -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0,  -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                1.0,  1.0,  -1.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                -1.0, -1.0, 1.0,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0, 1.0,  1.0,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0,  -1.0, 1.0,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                1.0,  1.0,  1.0,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                -1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                -1.0, 1.0,  -1.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0,  -1.0, -1.0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                1.0,  1.0,  -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
            calculateNormals(cubeVertices, cubeIndices, nCubeVertices,
                             nCubeIndices);
            createMesh(cubeVertices, cubeIndices, nCubeVertices, nCubeIndices);
            break;
        }
    }
}

void Mesh::calculateNormals(GLfloat *vertices, GLuint *indices,
                            GLuint nVertices, GLuint nIndices) {
    GLuint verticesGroupSize = 8;
    GLuint normalOffset = 5;
    for (size_t i = 0; i < nIndices; i += 3) {
        unsigned int in0 = indices[i + 0] * verticesGroupSize;
        unsigned int in1 = indices[i + 1] * verticesGroupSize;
        unsigned int in2 = indices[i + 2] * verticesGroupSize;
        glm::vec3 v1(vertices[in1 + 0] - vertices[in0 + 0],
                     vertices[in1 + 1] - vertices[in0 + 1],
                     vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2 + 0] - vertices[in0 + 0],
                     vertices[in2 + 1] - vertices[in0 + 1],
                     vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;
        vertices[in0 + 0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;
        vertices[in1 + 0] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;
        vertices[in2 + 0] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
    }
    for (size_t i = 0; i < nVertices / verticesGroupSize; i++) {
        unsigned int nOffset = i * verticesGroupSize + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1],
                      vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset + 0] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
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

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
    glEnableVertexAttribArray(0);
    // texCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                          (void *)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    // normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
                          (void *)(sizeof(vertices[0]) * 5));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render(double deltaTime) {
    graphics::useShader(shaderIndex);

    Transform *transform = owner->getComponent<Transform>();

    Material *material = nullptr;
    if (owner->hasComponent<Material>()) {
        material = owner->getComponent<Material>();
    }

    Light *light = nullptr;
    if (owner->hasComponent<Light>()) {
        light = owner->getComponent<Light>();
    }

    Object *cameraObject = owner->manager->getObjectByName("mainCamera");
    Camera *camera = cameraObject->getComponent<Camera>();

    graphics::applyUniform("model", transform->getModel());
    graphics::applyUniform("projection", camera->getProjection());
    graphics::applyUniform("view", camera->getView());

    if (material) {
        material->applyUniforms();
        graphics::applyUniform("viewPosition", camera->getViewPosition());
        graphics::applyLightUniforms();
    } else if (light) {
        graphics::applyUniform("lightColor", light->color);
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    graphics::unbindShader();
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
