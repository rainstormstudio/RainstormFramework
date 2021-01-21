#include "graphics.h"

#include "../../debug/debug.h"
#include "configSystem.h"
#include "shader.h"
#include "texture.h"

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

const size_t MAX_LIGHTS = 10;
glm::vec3 lightPositions[MAX_LIGHTS];
glm::vec3 lightColors[MAX_LIGHTS];
size_t nLights = 0;

std::vector<Shader *> shaderList;
size_t currentShaderIndex;

std::map<std::string, Texture *> textures;

Error initialize() {
    DEBUG_MSG("Initializing Graphics");
    DEBUG_ADD_DEPTH();
    screenWidth_ = config::screenWidth;
    screenHeight_ = config::screenHeight;
    showFPS = config::showFPS;

    if (!glfwInit()) {
        DEBUG_ERROR("Failed to initialize GLFW");
        DEBUG_DEC_DEPTH();
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
        DEBUG_ERROR("Failed to create GLFW window");
        DEBUG_DEC_DEPTH();
        glfwTerminate();
        return Error::FAIL;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        DEBUG_ERROR("Failed to initialize GLEW");
        DEBUG_DEC_DEPTH();
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

    DEBUG_MSG("window constructed");

    Shader *shader = new Shader();
    shader->createFromFiles(config::vShaderPath.c_str(),
                            config::fShaderPath.c_str());
    shaderList.emplace_back(shader);
    Shader *lightShader = new Shader();
    lightShader->createFromFiles(config::vLightShaderPath.c_str(),
                                 config::fLightShaderPath.c_str());
    shaderList.emplace_back(lightShader);
    Shader *texShader = new Shader();
    texShader->createFromFiles(config::vTexShaderPath.c_str(),
                               config::fTexShaderPath.c_str());
    shaderList.emplace_back(texShader);
    currentShaderIndex = 0;

    DEBUG_DEC_DEPTH();
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
    for (auto &texture : textures) {
        delete texture.second;
        texture.second = nullptr;
    }
    textures.clear();
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

void applyUniform(const std::string &name, glm::mat4 value) {
    glUniformMatrix4fv(shaderList[currentShaderIndex]->getUniform(name), 1,
                       GL_FALSE, glm::value_ptr(value));
}

void applyUniform(const std::string &name, glm::vec3 value) {
    glUniform3fv(shaderList[currentShaderIndex]->getUniform(name), 1,
                 glm::value_ptr(value));
}

void applyUniform(const std::string &name, float value) {
    glUniform1f(shaderList[currentShaderIndex]->getUniform(name), value);
}

void applyUniformInt(const std::string &name, int value) {
    glUniform1i(shaderList[currentShaderIndex]->getUniform(name), value);
}

size_t registerLight(glm::vec3 pos, glm::vec3 color) {
    if (nLights < MAX_LIGHTS) {
        size_t id = nLights;
        lightPositions[id] = pos;
        lightColors[id] = color;
        nLights++;
        return id;
    }
    return 0;
}

void updateLight(size_t id, glm::vec3 pos, glm::vec3 color) {
    if (id < nLights) {
        lightPositions[id] = pos;
        lightColors[id] = color;
    }
}

void applyLightUniforms() {
    glUniform3fv(shaderList[currentShaderIndex]->getUniform("lightPositions"),
                 nLights, glm::value_ptr(lightPositions[0]));
    glUniform3fv(shaderList[currentShaderIndex]->getUniform("lightColors"),
                 nLights, glm::value_ptr(lightColors[0]));
    glUniform1i(shaderList[currentShaderIndex]->getUniform("nLights"), nLights);
}

void registerTexture(std::string name, std::string filePath) {
    DEBUG_MSG("registering texture: [" + name + "] at " + filePath);
    DEBUG_ADD_DEPTH();
    if (textures.find(name) == textures.end()) {
        DEBUG_MSG("creating new texture");
        textures[name] = new Texture(filePath.c_str());
        DEBUG_MSG("loading texture:");
        DEBUG_ADD_DEPTH();
        textures[name]->loadTexture();
        DEBUG_DEC_DEPTH();
        DEBUG_MSG("texture registered");
    }
    DEBUG_DEC_DEPTH();
}

void useTexture(std::string name, size_t index) { textures[name]->use(index); }

}  // namespace graphics