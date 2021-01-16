/**
 * @file componentManager.h
 * @author Daniel Hongyu Ding
 * @brief This file defines components behavior
 * @version 0.1
 * @date 2021-01-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RS_COMPONENT_MANAGER_H
#define RS_COMPONENT_MANAGER_H

#include "entity.h"
#include "../../debug/debug.h"

namespace ECS {
    template<typename C>    // C for Component
    class ComponentManager {
        std::vector<Entity> entities;
        std::vector<C> components;
        std::unordered_map<Entity, size_t> map; // maps entity to component

    public:
        ComponentManager() {
            entities = std::vector<Entity>();
            components = std::vector<C>();
            map = std::unordered_map<Entity, size_t>();
        }

        inline C& create(Entity entity) {
            ASSERT(entity != INVALID_ENTITY);
            ASSERT(map.find(entity) == map.end());

            map[entity] = components.size();
            components.emplace_back();
            entities.push_back(entity);
            return components.back();
        }

        inline void destroy(Entity entity) {
            auto it = map.find(entity);
            if (it != map.end()) {
                const size_t index = it->second;
                const Entity entity = entities[index];
                if (index < components.size() - 1) {
                    components[index] = std::move(components.back());   // swap out the unwanted component
                    entities[index] = entities.back();
                    map[entities[index]] = index;
                }
                components.pop_back();
                entities.pop_back();
                map.erase(entity);
            }
        }

        inline bool hasComponent(Entity entity) const {
            return map.find(entity) != map.end();
        }

        inline C* getComponent(Entity entity) {
            auto it = map.find(entity);
            if (it != map.end()) {
                return &components[it->second];
            }
            return nullptr;
        }

        inline const C* getComponent(Entity entity) const {
            const auto it = map.find(entity);
            if (it != map.end()) {
                return &components[it->second];
            }
            return nullptr;
        }

        inline size_t getSize() const {
            return components.size();
        }

        inline C& operator[](size_t index) {
            ASSERT(0 <= index && index < components.size());
            return components[index];
        }

        inline const C& operator[](size_t index) const {
            ASSERT(0 <= index && index < components.size());
            return components[index];
        }
    };
}

#endif
