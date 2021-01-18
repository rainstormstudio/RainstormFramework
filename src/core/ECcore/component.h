/**
 * @file component.h
 * @author your name (you@domain.com)
 * @brief This file defines component
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_COMPONENT_H
#define RS_COMPONENT_H

class Entity;

class Component {
   public:
    Entity* owner;

    virtual void initialize() = 0;
    virtual void update(double deltaTime) = 0;
    virtual void render(double deltaTime) = 0;

    virtual ~Component() {}
};

#endif