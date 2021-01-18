/**
 * @file camera.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the camera component
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_C_CAMERA_H
#define RS_C_CAMERA_H

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../core/ECcore/component.h"

class Camera : public Component {
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat moveSpeed;
    GLfloat turnSpeed;

   public:
    struct Perspective {
        float fov;
        float aspect;
        float zNear;
        float zFar;
    };
    Perspective perspective;

    Camera();
    Camera(glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed,
           GLfloat turnSpeed, Perspective perspective);
    ~Camera() override {}

    void initialize() override {}
    void update(double deltaTime) override;
    void render(double deltaTime) override;

    glm::mat4 getView();
    glm::mat4 getProjection();
};

#endif
