/**
 * @file transform.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the transform component
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_C_TRANSFORM_H
#define RS_C_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "../core/ECcore/component.h"

class Transform : public Component {
    const float toRadians = 3.1415926f / 180.0f;

   public:
    glm::vec3 transform;
    glm::vec3 scale;
    glm::vec3 rotate;  // {angleX, angleY, angleZ} in degrees

    Transform() {
        transform = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    Transform(glm::vec3 transform) : transform{transform} {
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    Transform(glm::vec3 transform, glm::vec3 scale)
        : transform{transform}, scale{scale} {
        rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    Transform(glm::vec3 transform, glm::vec3 scale, glm::vec3 rotate)
        : transform{transform}, scale{scale}, rotate{rotate} {}

    void initialize() override {}
    void update(double deltaTime) override {}
    void render(double deltaTime) override {}

    glm::mat4 getModel() {
        glm::mat4 model(1.0);
        model = glm::translate(model, transform);
        model = glm::rotate(model, rotate.x * toRadians,
                            glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotate.y * toRadians,
                            glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotate.z * toRadians,
                            glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        return model;
    }

    ~Transform() override {}
};

#endif
