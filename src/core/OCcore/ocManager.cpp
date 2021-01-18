#include "ocManager.h"

#include "component.h"
#include "object.h"

OCManager::OCManager() {}

OCManager::~OCManager() { destroy(); }

void OCManager::destroy() {
    for (size_t i = 0; i < objects.size(); i++) {
        delete objects[i];
        objects[i] = nullptr;
        objects.erase(objects.begin() + i);
        i--;
    }
    layers.clear();
}

void OCManager::destroyByLayer(uint8_t layer) {
    if (layers.find(layer) == layers.end()) return;
    for (size_t i = 0; i < objects.size(); i++) {
        if (objects[i]->layer == layer) {
            delete objects[i];
            objects[i] = nullptr;
            objects.erase(objects.begin() + i);
            i--;
        }
    }
    layers.erase(layer);
}

void OCManager::initialize() {
    for (auto layer : layers) {
        for (auto& entity : getObjectsByLayer(layer)) {
            entity->initialize();
        }
    }
}

void OCManager::initializeByLayer(uint8_t layer) {
    for (auto& entity : getObjectsByLayer(layer)) {
        entity->initialize();
    }
}

void OCManager::update(double deltaTime) {
    for (auto layer : layers) {
        for (auto& entity : getObjectsByLayer(layer)) {
            entity->update(deltaTime);
        }
    }
    for (size_t i = 0; i < objects.size(); i++) {
        if (!objects[i]->isActive()) {
            delete objects[i];
            objects[i] = nullptr;
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

void OCManager::updateByLayer(double deltaTime, uint8_t layer) {
    for (auto& entity : getObjectsByLayer(layer)) {
        entity->update(deltaTime);
    }

    for (size_t i = 0; i < objects.size(); i++) {
        if (!objects[i]->isActive()) {
            delete objects[i];
            objects[i] = nullptr;
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

void OCManager::render(double deltaTime) {
    for (auto layer : layers) {
        for (auto& entity : getObjectsByLayer(layer)) {
            entity->render(deltaTime);
        }
    }
}

void OCManager::renderByLayer(double deltaTime, uint8_t layer) {
    for (auto& entity : getObjectsByLayer(layer)) {
        entity->render(deltaTime);
    }
}

Object* OCManager::addObject(std::string name, uint8_t layer) {
    Object* entity = new Object(*this, name, layer);
    objects.emplace_back(entity);
    layers.insert(layer);
    return entity;
}

std::vector<Object*> OCManager::getObjects() const { return objects; }

std::vector<Object*> OCManager::getObjectsByLayer(uint8_t layer) const {
    std::vector<Object*> theEntities;
    for (auto& entity : objects) {
        if (entity->layer == layer) {
            theEntities.emplace_back(entity);
        }
    }
    return theEntities;
}

Object* OCManager::getObjectByName(std::string name) const {
    for (auto& entity : objects) {
        if (entity->name == name) {
            return entity;
        }
    }
    return nullptr;
}
