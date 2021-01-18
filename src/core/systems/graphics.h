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

Error initialize();

void destroy();

void clearBuffer();

void renderBuffer();

bool windowShouldClose();

};  // namespace graphics

#endif
