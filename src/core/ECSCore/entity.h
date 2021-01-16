/**
 * @file entity.h
 * @author Daniel Hongyu Ding
 * @brief This file defines entity
 * @version 0.1
 * @date 2021-01-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RS_ENTITY_H
#define RS_ENTITY_H

#include "../utilities/includes.h"
#include <atomic>

namespace ECS {

    using Entity = uint32_t;
    static const Entity INVALID_ENTITY = 0;

    inline Entity createEntity() {
        static std::atomic<Entity> entity{INVALID_ENTITY + 1};
        return entity.fetch_add(1);
    }

}

#endif
