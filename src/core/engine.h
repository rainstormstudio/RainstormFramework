/**
 * @file engine.h
 * @author Daniel Hongyu Ding
 * @brief the core of the engine
 * @version 0.1
 * @date 2021-01-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef ENGINE_H
#define ENGINE_H

class ECManager;

class Engine {
    bool isRunning;

   public:
    Engine();
    virtual ~Engine();

   public:
    // interfaces
    virtual bool onCreate() = 0;
    virtual bool onUpdate(double deltaTime) = 0;
    virtual bool onRender(double deltaTime) = 0;
    virtual bool onDestroy();

   public:
    // must calls
    bool initialize();

    void run();

   public:
    ECManager* manager;

   private:
    void destroy();

    void gameLoop();
};

#endif
