#include "REngine.h"

class App : public Engine {
   public:
    bool onCreate() override {
        graphics::setCursorMode(graphics::DISABLED);

        Object* camera = manager->addObject("mainCamera", 0);
        {
            camera->addComponent<Transform>();
            camera->addComponent<Camera>();
            camera->addComponent<Control>(5.0);
        }

        Object* obj = nullptr;

        for (int i = 0; i < 10; i++) {
            obj = manager->addObject("light" + std::to_string(i), 0);
            {
                obj->addComponent<Transform>(glm::ballRand(10.0),
                                             glm::vec3(0.1, 0.1, 0.1));
                obj->addComponent<Mesh>(Mesh::CUBE, 1);
                obj->addComponent<Light>(glm::ballRand(1.0f));
            }
        }

        for (int i = 0; i < 3000; i++) {
            obj = manager->addObject("cube" + std::to_string(i), 1);
            {
                obj->addComponent<Transform>(glm::ballRand(50.0f));
                obj->addComponent<Mesh>(Mesh::CUBE);
                obj->addComponent<Material>(glm::vec3(1.0f));
            }
        }

        obj = manager->addObject("plane", 1);
        {
            obj->addComponent<Transform>(glm::vec3(0, -1.1, 0),
                                         glm::vec3(20, 20, 20));
            obj->addComponent<Mesh>(Mesh::PLANE);
            obj->addComponent<Material>(glm::vec3(0, 0.5, 0));
        }

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