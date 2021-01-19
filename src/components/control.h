/**
 * @file control.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the control component
 * @version 0.1
 * @date 2021-01-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_C_CONTROL_H
#define RRS_C_CONTROL_H

#include <GL/glew.h>

#include "../core/OCcore/component.h"

class Control : public Component {
    GLfloat moveSpeed;

   public:
    Control(GLfloat moveSpeed) : moveSpeed{moveSpeed} {}
    ~Control() override {}

    void initialize() override {}
    void update(double deltaTime) override;
    void render(double deltaTime) override {}
};

#endif
