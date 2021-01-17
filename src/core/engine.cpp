#include "engine.h"
#include "./systems/configSystem.h"
#include "./systems/jobSystem.h"
#include "./systems/graphics.h"
#include "../debug/debug.h"

Engine::Engine() {
    
}

Engine::~Engine() {
    
}

bool Engine::onDestroy() {
    return true;
}

bool Engine::initialize() {
    config::initialize();
    jobsystem::initialize();

    if (graphics::initialize() != Error::OK) {
        return false;
    }

    isRunning = false;
    return true;
}

void Engine::destroy() {
    graphics::destroy();
    jobsystem::destroy();
    config::destroy();
}

void Engine::run() {
    isRunning = true;
    gameLoop();
}

void Engine::update() {
    while (isRunning) {

        glfwPollEvents();

        if (!onUpdate(0)) {
            isRunning = false;
            jobsystem::sync();
            break;
        }
    }
}

void Engine::render() {
    while (isRunning) {
        graphics::clearBuffer();
        
        if (graphics::windowShouldClose()) {
            isRunning = false;
            jobsystem::sync();
            break;
        }

        if (!onRender(0)) {
            isRunning = false;
            jobsystem::sync();
            break;
        }

        graphics::renderBuffer();
    }
}

void Engine::gameLoop() {
    DEBUG_MSG("gameLoop starts")
    if (!onCreate()) {
        isRunning = false;
    }

    jobsystem::execute([this]{update();});
    jobsystem::execute([this]{render();});
    //render();
}
