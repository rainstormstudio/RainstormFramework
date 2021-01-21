#include "material.h"

#include "../core/systems/graphics.h"

Material::Material(std::string albedoMap, std::string normalMap,
                   std::string metallicMap, std::string roughnessMap,
                   std::string aoMap)
    : albedoMap_{albedoMap},
      normalMap_{normalMap},
      metallicMap_{metallicMap},
      roughnessMap_{roughnessMap},
      aoMap_{aoMap} {
    useTextures = true;
}

void Material::applyUniforms() {
    if (useTextures) {
        graphics::applyUniformInt("albedoMap", 0);
        graphics::applyUniformInt("normalMap", 1);
        graphics::applyUniformInt("metallicMap", 2);
        graphics::applyUniformInt("roughnessMap", 3);
        graphics::applyUniformInt("aoMap", 4);
        graphics::useTexture(albedoMap_, 0);
        graphics::useTexture(normalMap_, 1);
        graphics::useTexture(metallicMap_, 2);
        graphics::useTexture(roughnessMap_, 3);
        graphics::useTexture(aoMap_, 4);
    } else {
        graphics::applyUniform("albedo", albedo_);
        graphics::applyUniform("metallic", metallic_);
        graphics::applyUniform("roughness", roughness_);
        graphics::applyUniform("ao", ao_);
    }
}
