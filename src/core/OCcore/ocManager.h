/**
 * @file entityManager.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the object component manager
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_EC_MANAGER_H
#define RS_EC_MANAGER_H

#include "../../utilities/includes.h"

class Object;
class Component;

class OCManager {
   protected:
    std::vector<Object*> objects;
    std::set<uint8_t> layers;

   public:
    OCManager();
    ~OCManager();

    void destroy();
    void destroyByLayer(uint8_t layer);

    void initialize();
    void initializeByLayer(uint8_t layer);
    void update(double deltaTime);
    void updateByLayer(double deltaTime, uint8_t layer);
    void render(double deltaTime);
    void renderByLayer(double deltaTime, uint8_t layer);

    Object* addObject(std::string name, uint8_t layer);

    std::vector<Object*> getObjects() const;
    std::vector<Object*> getObjectsByLayer(uint8_t layer) const;
    Object* getObjectByName(std::string name) const;
};

#endif
