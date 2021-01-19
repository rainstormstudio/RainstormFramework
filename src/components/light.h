/**
 * @file light.h
 * @author Daniel Hongyu Ding
 * @brief This file defines a light component
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_C_LIGHT_H
#define RS_C_LIGHT_H

#include "../core/OCcore/component.h"
#include "../math/math.h"

class Light : public Component {
    size_t lightID_;

   public:
    glm::vec3 color;

    Light(glm::vec3 color) : lightID_{0}, color{color} {}
    ~Light() override {}

    void initialize() override;
    void update(double deltaTime) override;
    void render(double deltaTime) override {}
};

#endif
