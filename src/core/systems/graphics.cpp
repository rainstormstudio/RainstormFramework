#include "graphics.h"

#include "../../debug/debug.h"
#include "configSystem.h"
#include "shader.h"

// callbacks
static void glfwErrorCallback(int error, const char *description) {
    DEBUG_ERROR(description);
}

static void glfwFramebufferSizeCallback(GLFWwindow *window, int screenWidth,
                                        int screenHeight) {
    glViewport(0, 0, screenWidth, screenHeight);
    graphics::screenWidth_ = screenWidth;
    graphics::screenHeight_ = screenHeight;
}

namespace graphics {

GLFWwindow *window = nullptr;

uint32_t screenWidth_ = 800;
uint32_t screenHeight_ = 600;
std::string windowTitle = "REngine";
bool showFPS = true;

std::vector<Shader *> shaderList;
size_t currentShaderIndex;

Error initialize() {
    DEBUG_MSG("Initializing Graphics");
    screenWidth_ = config::screenWidth;
    screenHeight_ = config::screenHeight;
    showFPS = config::showFPS;

    if (!glfwInit()) {
        DEBUG_ERROR_INDENT("Failed to initialize GLFW", 1);
        return Error::FAIL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    if (config::msaa) {
        glfwWindowHint(GLFW_SAMPLES, config::msaa);
    }

    glfwSetErrorCallback(glfwErrorCallback);

    window = glfwCreateWindow(screenWidth_, screenHeight_, windowTitle.c_str(),
                              nullptr, nullptr);
    if (!window) {
        DEBUG_ERROR_INDENT("Failed to create GLFW window", 1);
        glfwTerminate();
        return Error::FAIL;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        DEBUG_ERROR_INDENT("Failed to initialize GLEW", 1);
        glfwDestroyWindow(window);
        glfwTerminate();
        return Error::FAIL;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    if (config::msaa) {
        glEnable(GL_MULTISAMPLE);
    }

    glViewport(0, 0, screenWidth_, screenHeight_);
    glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    DEBUG_MSG_INDENT("window constructed", 1);

    Shader *shader = new Shader();
    shader->createFromFiles(config::vShaderPath.c_str(),
                            config::fShaderPath.c_str());
    shaderList.emplace_back(shader);
    currentShaderIndex = 0;

    DEBUG_MSG("Graphics initialized");

    return Error::OK;
}

void setCursorMode(CursorMode mode) {
    switch (mode) {
        case NORMAL: {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        }
        case HIDDEN: {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;
        }
        case DISABLED: {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        }
    }
}

void update(double deltaTime) {
    if (showFPS) {
        std::string title =
            windowTitle + " - FPS: " + std::to_string(1.0 / deltaTime);
        glfwSetWindowTitle(window, title.c_str());
    }
}

void destroy() {
    for (size_t i = 0; i < shaderList.size(); i++) {
        delete shaderList[i];
        shaderList[i] = nullptr;
        shaderList.erase(shaderList.begin() + i);
        i--;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *getWindow() { return window; }

void clearBuffer() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void useShader(size_t index) {
    if (0 <= index && index < shaderList.size()) {
        currentShaderIndex = index;
    }
    shaderList[currentShaderIndex]->use();
}

void unbindShader() { glUseProgram(0); }

void renderBuffer() { glfwSwapBuffers(window); }

bool windowShouldClose() { return glfwWindowShouldClose(window); }

uint32_t screenWidth() { return screenWidth_; }

uint32_t screenHeight() { return screenHeight_; }

void applyModel(glm::mat4 model) {
    glUniformMatrix4fv(shaderList[currentShaderIndex]->uniformModel(), 1,
                       GL_FALSE, glm::value_ptr(model));
}

void applyProjection(glm::mat4 projection) {
    glUniformMatrix4fv(shaderList[currentShaderIndex]->uniformProjection(), 1,
                       GL_FALSE, glm::value_ptr(projection));
}

void applyView(glm::mat4 view) {
    glUniformMatrix4fv(shaderList[currentShaderIndex]->uniformView(), 1,
                       GL_FALSE, glm::value_ptr(view));
}

void applyAlbedo(glm::vec3 albedo) {
    glUniform3fv(shaderList[currentShaderIndex]->uniformAlbedo(), 1,
                 glm::value_ptr(albedo));
}

void applyMetallic(float metallic) {
    glUniform1f(shaderList[currentShaderIndex]->uniformMetallic(), metallic);
}

void applyRoughness(float roughness) {
    glUniform1f(shaderList[currentShaderIndex]->uniformRoughness(), roughness);
}

void applyAO(float ao) {
    glUniform1f(shaderList[currentShaderIndex]->uniformAO(), ao);
}

}  // namespace graphics