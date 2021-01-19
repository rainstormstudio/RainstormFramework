#include "control.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/OCcore/object.h"
#include "../core/systems/inputManager.h"
#include "camera.h"
#include "transform.h"

void Control::update(double deltaTime) {
    Transform* transform = owner->getComponent<Transform>();
    Camera* camera = owner->getComponent<Camera>();
    if (inputManager::getKeyState(KEY_W) == inputManager::PRESS) {
        transform->transform += camera->front * moveSpeed * (GLfloat)deltaTime;
    }
    if (inputManager::getKeyState(KEY_S) == inputManager::PRESS) {
        transform->transform -= camera->front * moveSpeed * (GLfloat)deltaTime;
    }
    if (inputManager::getKeyState(KEY_A) == inputManager::PRESS) {
        transform->transform -= camera->right * moveSpeed * (GLfloat)deltaTime;
    }
    if (inputManager::getKeyState(KEY_D) == inputManager::PRESS) {
        transform->transform += camera->right * moveSpeed * (GLfloat)deltaTime;
    }
    if (inputManager::getKeyState(KEY_LEFT_CONTROL) == inputManager::PRESS) {
        transform->transform -=
            camera->worldUp * moveSpeed * (GLfloat)deltaTime;
    }
    if (inputManager::getKeyState(KEY_SPACE) == inputManager::PRESS) {
        transform->transform +=
            camera->worldUp * moveSpeed * (GLfloat)deltaTime;
    }

    camera->addYaw(inputManager::mouseXChange() * camera->turnSpeed);
    camera->addPitch(inputManager::mouseYChange() * camera->turnSpeed);

    camera->update();
}
