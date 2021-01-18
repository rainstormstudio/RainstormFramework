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

    moveSpeed = 5.0f;
    turnSpeed = 0.05f;
}

Camera::Camera(glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed,
               GLfloat turnSpeed, Perspective perspective)
    : worldUp{worldUp},
      yaw{yaw},
      pitch{pitch},
      moveSpeed{moveSpeed},
      turnSpeed{turnSpeed},
      perspective{perspective} {
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    update(0.0f);
}

void Camera::update(double deltaTime) {
    DEBUG_MSG_INDENT("camera component update", 1);
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
    DEBUG_MSG_INDENT("camera component render", 1);
    graphics::applyProjection(getProjection());
    graphics::applyView(getView());
}
