/**
 * @file entityManager.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the entity manager
 * @version 0.1
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_EC_MANAGER_H
#define RS_EC_MANAGER_H

#include "../../utilities/includes.h"

class Entity;
class Component;

class ECManager {
   protected:
    std::vector<Entity*> entities;
    std::set<uint8_t> layers;

   public:
    ECManager();
    ~ECManager();

    void destroy();
    void destroyByLayer(uint8_t layer);

    void update(double deltaTime);
    void updateByLayer(double deltaTime, uint8_t layer);
    void render(double deltaTime);
    void renderByLayer(double deltaTime, uint8_t layer);

    Entity* addEntity(std::string name, uint8_t layer);

    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntitiesByLayer(uint8_t layer) const;
    Entity* getEntityByName(std::string name) const;
};

#endif
