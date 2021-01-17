#include "REngine.h"

class App : public Engine {
public:
    bool onCreate() override {
        return true;
    }

    bool onUpdate(double deltaTime) override {
        return true;
    }

    bool onRender(double deltaTime) override {
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