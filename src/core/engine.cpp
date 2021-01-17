#include "engine.h"

#include "../debug/debug.h"
#include "./systems/configSystem.h"
#include "./systems/graphics.h"
#include "./systems/jobManager.h"

Engine::Engine() {}

Engine::~Engine() {}

bool Engine::onDestroy() { return true; }

bool Engine::initialize() {
    if (config::initialize() != Error::OK) {
        return false;
    }

    jobManager::initialize();

    if (graphics::initialize() != Error::OK) {
        return false;
    }

    isRunning = false;

    DEBUG_MSG("engine initialized");
    DEBUG_DLINE();

    return true;
}

void Engine::destroy() {
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
    DEBUG_MSG("gameLoop starts");
    if (!onCreate()) {
        isRunning = false;
    }

    double deltaTime = 0.0;
    double time_a = glfwGetTime();
    double time_b = glfwGetTime();

    while (isRunning) {
        while (isRunning) {
            time_b = glfwGetTime();
            deltaTime = time_b - time_a;
            while (deltaTime < 0.001) {
                time_b = glfwGetTime();
                deltaTime = time_b - time_a;
            }
            time_a = time_b;

            glfwPollEvents();
            if (graphics::windowShouldClose()) {
                isRunning = false;
            }

            if (!onUpdate(0)) {
                isRunning = false;
            }

            graphics::clearBuffer();

            if (!onRender(0)) {
                isRunning = false;
            }

            graphics::renderBuffer();
        }

        if (!onDestroy()) {
            isRunning = true;
        }
    }

    DEBUG_MSG("gameLoop ends");

    destroy();
}