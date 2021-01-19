#include "material.h"

#include "../core/systems/graphics.h"

void Material::applyUniforms() {
    graphics::applyUniform("albedo", albedo_);
    graphics::applyUniform("metallic", metallic_);
    graphics::applyUniform("roughness", roughness_);
    graphics::applyUniform("ao", ao_);
}
