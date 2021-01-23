#include "REngine.h"

class Move : public Component {
    float delta;
    bool front;
    float speed;

   public:
    Move() {
        delta = 0.0f;
        front = true;
    }
    ~Move() override {}

    void initialize() override { speed = glm::linearRand(0.1, 1.0); }
    void update(double deltaTime) override {
        if (front) {
            delta += deltaTime * speed;
        } else {
            delta -= deltaTime * speed;
        }
        if (delta > 1.0) front = false;
        if (delta < -1.0) front = true;

        Transform* transform = owner->getComponent<Transform>();
        transform->transform.x += delta * 0.1;
    }
    void render(double deltaTime) override {}
};

class App : public Engine {
   public:
    bool onCreate() override {
        DEBUG_MSG("onCreate");
        DEBUG_ADD_DEPTH();
        graphics::setCursorMode(graphics::DISABLED);
        std::string materialName = "marble-floor";
        graphics::registerTexture(
            "floor_albedo",
            "./assets/textures/" + materialName + "/albedo.jpg");
        graphics::registerTexture(
            "floor_normal",
            "./assets/textures/" + materialName + "/normal.jpg");
        graphics::registerTexture(
            "floor_metallic",
            "./assets/textures/" + materialName + "/metallic.jpg");
        graphics::registerTexture(
            "floor_roughness",
            "./assets/textures/" + materialName + "/roughness.jpg");
        graphics::registerTexture(
            "floor_ao", "./assets/textures/" + materialName + "/ao.jpg");

        materialName = "sci-fi-floor";
        graphics::registerTexture(
            "cube_albedo", "./assets/textures/" + materialName + "/albedo.jpg");
        graphics::registerTexture(
            "cube_normal", "./assets/textures/" + materialName + "/normal.jpg");
        graphics::registerTexture(
            "cube_metallic",
            "./assets/textures/" + materialName + "/metallic.jpg");
        graphics::registerTexture(
            "cube_roughness",
            "./assets/textures/" + materialName + "/roughness.jpg");
        graphics::registerTexture(
            "cube_ao", "./assets/textures/" + materialName + "/ao.jpg");

        Object* camera = manager->addObject("mainCamera", 0);
        {
            camera->addComponent<Transform>();
            camera->addComponent<Camera>();
            camera->addComponent<Control>(5.0);
        }
        DEBUG_MSG("camera created");

        Object* obj = nullptr;

        for (int i = 0; i < 10; i++) {
            obj = manager->addObject("light" + std::to_string(i), 0);
            {
                obj->addComponent<Transform>(glm::ballRand(10.0),
                                             glm::vec3(0.1));
                obj->addComponent<Mesh>(Mesh::CUBE, 1);
                obj->addComponent<Move>();
                obj->addComponent<Light>(glm::vec3(glm::linearRand(0.5, 1.0),
                                                   glm::linearRand(0.5, 1.0),
                                                   glm::linearRand(0.5, 1.0)));
            }
        }
        DEBUG_MSG("lights created");

        for (int i = 0; i < 100; i++) {
            obj = manager->addObject("cube" + std::to_string(i), 1);
            {
                obj->addComponent<Transform>(glm::vec3(glm::ballRand(50.0)),
                                             glm::vec3(1.0));
                obj->addComponent<Mesh>(Mesh::CUBE, 2);
                obj->addComponent<Material>("cube_albedo", "cube_normal",
                                            "cube_metallic", "cube_roughness",
                                            "cube_ao");
            }
        }
        DEBUG_MSG("cubes created");

        obj = manager->addObject("plane", 1);
        {
            obj->addComponent<Transform>(glm::vec3(0, -1.1, 0),
                                         glm::vec3(100, 100, 100));
            obj->addComponent<Mesh>(Mesh::PLANE, 2);
            obj->addComponent<Material>("floor_albedo", "floor_normal",
                                        "floor_metallic", "floor_roughness",
                                        "floor_ao");
        }
        DEBUG_MSG("plane created");

        DEBUG_DEC_DEPTH();

        return true;
    }

    bool onUpdate(double deltaTime) override {
        manager->update(deltaTime);
        return true;
    }

    bool onRender(double deltaTime) override {
        manager->render(deltaTime);
        return true;
    }
};

int main() {
    App app;
    if (app.initialize()) {
        app.run();
    }

    return 0;
}