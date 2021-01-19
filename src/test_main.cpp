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

        Object* obj = manager->addObject("cube", 1);
        {
            obj->addComponent<Transform>(glm::vec3(-1, 0, -5));
            obj->addComponent<Mesh>(Mesh::CUBE);
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