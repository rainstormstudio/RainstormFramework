/**
 * @file material.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the material component
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_C_MATERIAL_H
#define RS_C_MATERIAL_H

#include "../core/OCcore/component.h"
#include "../core/systems/texture.h"
#include "../debug/debug.h"
#include "../math/math.h"

class Material : public Component {
    glm::vec3 albedo_;
    float metallic_;
    float roughness_;
    float ao_;

    std::string albedoMap_;
    std::string normalMap_;
    std::string metallicMap_;
    std::string roughnessMap_;
    std::string aoMap_;

    bool useTextures;

   public:
    Material(glm::vec3 albedo, float metallic = 0.0f, float roughness = 0.0f,
             float ao = 0.0f)
        : albedo_{albedo}, metallic_{metallic}, roughness_{roughness}, ao_{ao} {
        albedoMap_ = "";
        normalMap_ = "";
        metallicMap_ = "";
        roughnessMap_ = "";
        aoMap_ = "";
        useTextures = false;
    }

    Material(std::string albedoMap, std::string normalMap,
             std::string metallicMap, std::string roughnessMap,
             std::string aoMap);

    ~Material() override {}

    void applyUniforms();

    void initialize() override {}
    void update(double deltaTime) override {}
    void render(double deltaTime) override {}
};

#endif
