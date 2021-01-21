#include "REngine.h"

class App : public Engine {
   public:
    bool onCreate() override {
        DEBUG_MSG("onCreate");
        DEBUG_ADD_DEPTH();
        graphics::setCursorMode(graphics::DISABLED);
        graphics::registerTexture("floor_albedo",
                                  "./assets/textures/marble-floor/albedo.jpg");
        graphics::registerTexture("floor_normal",
                                  "./assets/textures/marble-floor/normal.jpg");
        graphics::registerTexture(
            "floor_metallic", "./assets/textures/marble-floor/metallic.jpg");
        graphics::registerTexture(
            "floor_roughness", "./assets/textures/marble-floor/roughness.jpg");
        graphics::registerTexture("floor_ao",
                                  "./assets/textures/marble-floor/ao.jpg");
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
                                             glm::vec3(0.1, 0.1, 0.1));
                obj->addComponent<Mesh>(Mesh::CUBE, 1);
                obj->addComponent<Light>(glm::vec3(glm::linearRand(0.5, 1.0),
                                                   glm::linearRand(0.5, 1.0),
                                                   glm::linearRand(0.5, 1.0)));
            }
        }
        DEBUG_MSG("lights created");

        for (int i = 0; i < 3000; i++) {
            obj = manager->addObject("cube" + std::to_string(i), 1);
            {
                obj->addComponent<Transform>(glm::ballRand(50.0f));
                obj->addComponent<Mesh>(Mesh::CUBE);
                obj->addComponent<Material>(glm::ballRand(1.0f),
                                            glm::linearRand(0.0f, 1.0f),
                                            glm::linearRand(0.0f, 1.0f));
            }
        }
        DEBUG_MSG("cubes created");

        obj = manager->addObject("plane", 1);
        {
            obj->addComponent<Transform>(glm::vec3(0, -1.1, 0),
                                         glm::vec3(20, 20, 20));
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