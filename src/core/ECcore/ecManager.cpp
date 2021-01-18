#include "ecManager.h"

#include "component.h"
#include "entity.h"

ECManager::ECManager() {}

ECManager::~ECManager() { destroy(); }

void ECManager::destroy() {
    for (size_t i = 0; i < entities.size(); i++) {
        delete entities[i];
        entities[i] = nullptr;
        entities.erase(entities.begin() + i);
        i--;
    }
    layers.clear();
}

void ECManager::destroyByLayer(uint8_t layer) {
    if (layers.find(layer) == layers.end()) return;
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i]->layer == layer) {
            delete entities[i];
            entities[i] = nullptr;
            entities.erase(entities.begin() + i);
            i--;
        }
    }
    layers.erase(layer);
}

void ECManager::initialize() {
    for (auto layer : layers) {
        for (auto& entity : getEntitiesByLayer(layer)) {
            entity->initialize();
        }
    }
}

void ECManager::initializeByLayer(uint8_t layer) {
    for (auto& entity : getEntitiesByLayer(layer)) {
        entity->initialize();
    }
}

void ECManager::update(double deltaTime) {
    for (auto layer : layers) {
        for (auto& entity : getEntitiesByLayer(layer)) {
            entity->update(deltaTime);
        }
    }
    for (size_t i = 0; i < entities.size(); i++) {
        if (!entities[i]->isActive()) {
            delete entities[i];
            entities[i] = nullptr;
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

void ECManager::updateByLayer(double deltaTime, uint8_t layer) {
    for (auto& entity : getEntitiesByLayer(layer)) {
        entity->update(deltaTime);
    }

    for (size_t i = 0; i < entities.size(); i++) {
        if (!entities[i]->isActive()) {
            delete entities[i];
            entities[i] = nullptr;
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

void ECManager::render(double deltaTime) {
    for (auto layer : layers) {
        for (auto& entity : getEntitiesByLayer(layer)) {
            entity->render(deltaTime);
        }
    }
}

void ECManager::renderByLayer(double deltaTime, uint8_t layer) {
    for (auto& entity : getEntitiesByLayer(layer)) {
        entity->render(deltaTime);
    }
}

Entity* ECManager::addEntity(std::string name, uint8_t layer) {
    Entity* entity = new Entity(*this, name, layer);
    entities.emplace_back(entity);
    layers.insert(layer);
    return entity;
}

std::vector<Entity*> ECManager::getEntities() const { return entities; }

std::vector<Entity*> ECManager::getEntitiesByLayer(uint8_t layer) const {
    std::vector<Entity*> theEntities;
    for (auto& entity : entities) {
        if (entity->layer == layer) {
            theEntities.emplace_back(entity);
        }
    }
    return theEntities;
}

Entity* ECManager::getEntityByName(std::string name) const {
    for (auto& entity : entities) {
        if (entity->name == name) {
            return entity;
        }
    }
    return nullptr;
}
