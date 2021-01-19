/**
 * @file graphics.h
 * @author Daniel Hongyu Ding
 * @brief graphics interface
 * @version 0.1
 * @date 2021-01-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_GRAPHICS_H
#define RS_GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../error/error.h"
#include "../../math/math.h"
#include "../../utilities/includes.h"

namespace graphics {

extern uint32_t screenWidth_;
extern uint32_t screenHeight_;

Error initialize();

enum CursorMode { NORMAL, HIDDEN, DISABLED };
void setCursorMode(CursorMode mode);

void destroy();

void clearBuffer();

void update(double deltaTime);

void renderBuffer();

bool windowShouldClose();

GLFWwindow* getWindow();

uint32_t screenWidth();
uint32_t screenHeight();

void useShader(size_t index = 0);
void unbindShader();

void applyModel(glm::mat4 model);
void applyProjection(glm::mat4 projection);
void applyView(glm::mat4 view);

};  // namespace graphics

#endif
