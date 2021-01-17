#include "graphics.h"
#include "../../debug/debug.h"
#include "configSystem.h"

// callbacks
void glfwErrorCallback(int error, const char* description) {
    DEBUG_ERROR(description);
}

void glfwFramebufferSizeCallback(GLFWwindow* window, int screenWidth, int screenHeight) {
    glViewport(0, 0, screenWidth, screenHeight);
}

namespace graphics {

    GLFWwindow* window;
    
    uint32_t screenWidth = 800;
    uint32_t screenHeight = 600;
    std::string windowTitle;

    Error initialize() {
        DEBUG_MSG("Initializing Graphics");
        screenWidth = config::screenWidth;
        screenHeight = config::screenHeight;

        if (!glfwInit()) {
            DEBUG_ERROR("Failed to initialize GLFW");
            return Error::FAIL;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwSetErrorCallback(glfwErrorCallback);

        window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);
        if (!window) {
            DEBUG_ERROR("Failed to create GLFW window");
            glfwTerminate();
            return Error::FAIL;
        }
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) {
            DEBUG_ERROR("Failed to initialize GLEW");
            glfwDestroyWindow(window);
            glfwTerminate();
            return Error::FAIL;
        }

        glViewport(0, 0, screenWidth, screenHeight);
        glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glfwSwapInterval(1);

        DEBUG_MSG("window constructed");

        return Error::OK;
    }

    void destroy() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void clearBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void renderBuffer() {
        glfwSwapBuffers(window);
    }

    bool windowShouldClose() {
        return glfwWindowShouldClose(window);
    }

}