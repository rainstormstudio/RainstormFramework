/**
 * @file configSystem.h
 * @author Daniel Hongyu Ding
 * @brief This file defines a system for engine configurations
 * @version 0.1
 * @date 2021-01-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef CONFIG_SYSTEM_H
#define CONFIG_SYSTEM_H

#include "../../error/error.h"
#include "../../utilities/includes.h"

namespace config {

extern std::string configFilePath;
extern std::string vShaderPath;
extern std::string fShaderPath;

extern uint32_t screenWidth;
extern uint32_t screenHeight;
extern bool showFPS;

Error initialize();

void destroy();

}  // namespace config

#endif