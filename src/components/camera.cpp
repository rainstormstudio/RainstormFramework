#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/OCcore/object.h"
#include "../core/systems/graphics.h"
#include "../debug/debug.h"
#include "transform.h"

Camera::Camera() {
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;

    perspective = {
        45.0f, (float)graphics::screenWidth() / (float)graphics::screenHeight(),
        0.1f, 100.0f};

    turnSpeed = 0.05f;
}

Camera::Camera(glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat turnSpeed,
               Perspective perspective)
    : worldUp{worldUp},
      yaw{yaw},
      pitch{pitch},
      turnSpeed{turnSpeed},
      perspective{perspective} {
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    update(0.0f);
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getView() {
    Transform* transform = owner->getComponent<Transform>();
    return glm::lookAt(transform->transform, transform->transform + front, up);
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(perspective.fov, perspective.aspect,
                            perspective.zNear, perspective.zFar);
}

void Camera::render(double deltaTime) {
    graphics::applyProjection(getProjection());
    graphics::applyView(getView());
}

void Camera::addYaw(GLfloat delta) {
    yaw += delta;
    if (yaw > 360.0f) {
        yaw -= 360.0f;
    }
    if (yaw < 0.0f) {
        yaw += 360.0f;
    }
}

void Camera::addPitch(GLfloat delta) {
    pitch += delta;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}
