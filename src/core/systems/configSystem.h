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

#include "../../utilities/includes.h"
#include "../../error/error.h"

namespace config {
    extern std::string configFilePath;

    extern uint32_t screenWidth;
    extern uint32_t screenHeight;

    Error initialize();

    void destroy();
}

#endif