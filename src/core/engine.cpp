#include "engine.h"

#include "../debug/debug.h"
#include "./OCcore/ocManager.h"
#include "./systems/configSystem.h"
#include "./systems/graphics.h"
#include "./systems/inputManager.h"
#include "./systems/jobManager.h"

Engine::Engine() {}

Engine::~Engine() {}

bool Engine::onDestroy() { return true; }

bool Engine::initialize() {
    std::srand(std::time(0));

    if (config::initialize() != Error::OK) {
        return false;
    }

    jobManager::initialize();

    if (graphics::initialize() != Error::OK) {
        return false;
    }

    inputManager::initialize();

    manager = new OCManager();

    isRunning = false;

    DEBUG_MSG("engine initialized");
    DEBUG_DLINE();

    return true;
}

void Engine::destroy() {
    delete manager;
    inputManager::destroy();
    graphics::destroy();
    jobManager::sync();
    jobManager::destroy();
    config::destroy();

    DEBUG_MSG("engine destroyed");
    DEBUG_DLINE();
}

void Engine::run() {
    isRunning = true;
    gameLoop();
}

void Engine::gameLoop() {
    if (!onCreate()) {
        isRunning = false;
    }

    DEBUG_MSG("initializing manager");
    manager->initialize();

    DEBUG_LINE();

    double deltaTime = 0.0;
    double time_a = glfwGetTime();
    double time_b = glfwGetTime();

    DEBUG_MSG("gameLoop starts");

    while (isRunning) {
        while (isRunning) {
            time_b = glfwGetTime();
            deltaTime = time_b - time_a;
            while (deltaTime < 0.001) {
                time_b = glfwGetTime();
                deltaTime = time_b - time_a;
            }
            time_a = time_b;

            inputManager::update();

            if (graphics::windowShouldClose()) {
                isRunning = false;
            }

            if (!onUpdate(deltaTime)) {
                isRunning = false;
            }

            graphics::clearBuffer();
            // graphics::useShader(0);

            if (!onRender(deltaTime)) {
                isRunning = false;
            }

            graphics::update(deltaTime);

            // graphics::unbindShader();

            graphics::renderBuffer();
        }

        if (!onDestroy()) {
            isRunning = true;
        }
    }

    DEBUG_MSG("gameLoop ends");

    destroy();
}
