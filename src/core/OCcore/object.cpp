#include "object.h"

#include "../../debug/debug.h"
#include "component.h"
#include "ocManager.h"

Object::Object(OCManager* manager, std::string name, uint8_t layer)
    : manager{manager}, name{name}, layer{layer} {
    isActive_ = true;
    DEBUG_MSG("object: " + name + " created");
}

Object::~Object() {
    for (size_t i = 0; i < components.size(); i++) {
        delete components[i];
        components[i] = nullptr;
        components.erase(components.begin() + i);
        i--;
    }
    DEBUG_MSG("object: " + name + " deleted");
    DEBUG_LINE();
}

void Object::initialize() {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->initialize();
    }
}

void Object::update(double deltaTime) {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->update(deltaTime);
    }
}

void Object::render(double deltaTime) {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->render(deltaTime);
    }
}

bool Object::isActive() const { return isActive_; }

void Object::destroy() { isActive_ = false; }
