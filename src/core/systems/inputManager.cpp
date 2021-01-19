#include "inputManager.h"

#include "graphics.h"

namespace inputManager {

double mouseLastX_ = 0.0f;
double mouseLastY_ = 0.0f;
double mousePosX_ = 0.0f;
double mousePosY_ = 0.0f;
double mouseXChange_ = 0.0f;
double mouseYChange_ = 0.0f;
bool mouseFirstMoved;

void initialize() { mouseFirstMoved = false; }

void update() {
    glfwPollEvents();

    GLFWwindow* window = graphics::getWindow();

    glfwGetCursorPos(window, &mousePosX_, &mousePosY_);
    if (!mouseFirstMoved) {
        mouseLastX_ = mousePosX_;
        mouseLastY_ = mousePosY_;
        mouseFirstMoved = true;
    }
    mouseXChange_ = mousePosX_ - mouseLastX_;
    mouseYChange_ = -(mousePosY_ - mouseLastY_);

    mouseLastX_ = mousePosX_;
    mouseLastY_ = mousePosY_;
}

void destroy() {}

double mouseXChange() { return mouseXChange_; }

double mouseYChange() { return mouseYChange_; }

double mousePosX() { return mousePosX_; }

double mousePosY() { return mousePosY_; }

InputState getKeyState(int key) {
    GLFWwindow* window = graphics::getWindow();
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS) {
        return PRESS;
    } else if (state == GLFW_RELEASE) {
        return RELEASE;
    } else if (state == GLFW_REPEAT) {
        return REPEAT;
    }
    return UNKNOWN;
}

InputState getMouseButtonState(int button) {
    GLFWwindow* window = graphics::getWindow();
    int state = glfwGetMouseButton(window, button);
    if (state == GLFW_PRESS) {
        return PRESS;
    } else if (state == GLFW_RELEASE) {
        return RELEASE;
    } else if (state == GLFW_REPEAT) {
        return REPEAT;
    }
    return UNKNOWN;
}

}  // namespace inputManager