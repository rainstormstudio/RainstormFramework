# RainstormFramework

## Description
Rainstorm Framework is a game engine based on OpenGL and uses an Object Component system. The ultimate goal of this engine is to provide a GUI-free but simple-to-use code interface.

## Usage
### main interface
```
#include "REngine.h"

class App : public Engine {
   public:
    // calls before the game loop
    bool onCreate() override {
        ...
        return true;
    }

    // calls every frame 
    // for updating game logic
    bool onUpdate(double deltaTime) override {
        ...
        return true;
    }

    // calls every frame
    // for rendering game objects
    bool onRender(double deltaTime) override {
        ...
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
```
### Object Component system
```
// create an object:
// addObject requires two parameters:
//     a string for object name
//     an unsigned integer for layer index
Object* object = manager->addObject("ObjectName", 0);

// add a component
object->addComponent<ComponentType>
```