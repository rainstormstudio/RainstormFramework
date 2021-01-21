#include "light.h"

#include "../core/OCcore/object.h"
#include "../core/systems/graphics.h"
#include "../debug/debug.h"
#include "transform.h"

void Light::initialize() {
    Transform* transform = owner->getComponent<Transform>();
    lightID_ = graphics::registerLight(transform->transform, color);
}

void Light::update(double deltaTime) {
    Transform* transform = owner->getComponent<Transform>();
    graphics::updateLight(lightID_, transform->transform, color);
}
