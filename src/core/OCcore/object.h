/**
 * @file entity.h
 * @author Daniel Hongyu Ding
 * @brief This file defines object
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_ENTITY_H
#define RS_ENTITY_H

#include "../../utilities/includes.h"

class Component;
class OCManager;

class Object {
    bool isActive_;
    std::map<const std::type_info*, Component*> componentTypes;

   public:
    OCManager* manager;

    std::vector<Component*> components;
    std::string name;
    uint8_t layer;

    Object(OCManager* manager, std::string name, uint8_t layer);

    ~Object();

    void initialize();
    void update(double deltaTime);
    void render(double deltaTime);

    bool isActive() const;
    void destroy();

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... args) {
        T* component = new T(std::forward<TArgs>(args)...);
        component->owner = this;
        components.emplace_back(component);
        componentTypes[&typeid(*component)] = component;
        // component->initialize();
        return *component;
    }

    template <typename T>
    bool hasComponent() const {
        return static_cast<bool>(componentTypes.count(&typeid(T)));
    }

    template <typename T>
    T* getComponent() {
        return static_cast<T*>(componentTypes[&typeid(T)]);
    }
};

#endif
