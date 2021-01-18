#include "REngine.h"

class App : public Engine {
   public:
    bool onCreate() override {
        Entity* camera = manager->addEntity("mainCamera", 0);
        {
            camera->addComponent<Transform>();
            camera->addComponent<Camera>();
        }

        Entity* obj = manager->addEntity("cube", 1);
        {
            obj->addComponent<Transform>(glm::vec3(0, 0, -10));
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