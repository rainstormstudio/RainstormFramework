#include "entity.h"

#include "../../debug/debug.h"
#include "component.h"
#include "ecManager.h"

Entity::Entity(ECManager& manager, std::string name, uint8_t layer)
    : manager{manager}, name{name}, layer{layer} {
    isActive_ = true;
    DEBUG_MSG("entity: " + name + " created");
}

Entity::~Entity() {
    for (size_t i = 0; i < components.size(); i++) {
        delete components[i];
        components[i] = nullptr;
        components.erase(components.begin() + i);
        i--;
    }
    DEBUG_MSG("entity: " + name + " deleted");
    DEBUG_LINE();
}

void Entity::update(double deltaTime) {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->update(deltaTime);
    }
}

void Entity::render(double deltaTime) {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->render(deltaTime);
    }
}

bool Entity::isActive() const { return isActive_; }

void Entity::destroy() { isActive_ = false; }
