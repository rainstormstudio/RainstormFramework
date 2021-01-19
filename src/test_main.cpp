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

        for (int i = 0; i < 3000; i++) {
            Object* obj = manager->addObject("cube" + std::to_string(i), 1);
            {
                obj->addComponent<Transform>(glm::ballRand(50.0f));
                obj->addComponent<Mesh>(Mesh::CUBE);
                obj->addComponent<Material>(glm::ballRand(1.0f));
            }
        }

        Object* obj = manager->addObject("plane", 1);
        {
            obj->addComponent<Transform>(glm::vec3(0, -1.1, 0),
                                         glm::vec3(20, 20, 20));
            obj->addComponent<Mesh>(Mesh::PLANE);
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