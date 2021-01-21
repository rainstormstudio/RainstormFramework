#include "configSystem.h"

#include "../../debug/debug.h"
#include "../../utilities/utility.h"

namespace config {
std::string configFilePath = "./config/settings.cfg";
std::string vShaderPath = "./shaders/vertex.glsl";
std::string fShaderPath = "./shaders/fragment.glsl";
std::string vTexShaderPath = "./shaders/vertexTex.glsl";
std::string fTexShaderPath = "./shaders/fragmentTex.glsl";
std::string vLightShaderPath = "./shaders/light_vertex.glsl";
std::string fLightShaderPath = "./shaders/light_fragment.glsl";

uint32_t screenWidth = 800;
uint32_t screenHeight = 600;
bool showFPS = true;
uint8_t msaa = 0;

Error initialize() {
    DEBUG_MSG("Initializing Configuration");
    DEBUG_ADD_DEPTH();

    std::ifstream input{configFilePath};
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            if (line == "") continue;
            int len = line.length();
            std::string tag = "";
            std::string value = "";
            bool flag = false;
            for (int i = 0; i < len; ++i) {
                if (line[i] == '#') {
                    break;
                } else if (line[i] == '=') {
                    flag = true;
                } else {
                    if (flag) {
                        value += line[i];
                    } else {
                        tag += line[i];
                    }
                }
            }
            if (tag == "") continue;
            if (value == "") continue;

            tag = utility::toLower(utility::trim(tag));
            value = utility::trim(value);

            DEBUG_MSG("tag: " + tag);
            DEBUG_MSG("value: " + value);
            DEBUG_LINE();

            if (tag == "screenwidth" && utility::isNat(value)) {
                screenWidth = std::stoi(value);
            } else if (tag == "screenheight" && utility::isNat(value)) {
                screenHeight = std::stoi(value);
            } else if (tag == "showfps") {
                showFPS = utility::toBool(value);
            } else if (tag == "vshader") {
                vShaderPath = value;
            } else if (tag == "fshader") {
                fShaderPath = value;
            } else if (tag == "vtexshader") {
                vTexShaderPath = value;
            } else if (tag == "ftexshader") {
                fTexShaderPath = value;
            } else if (tag == "vlightshader") {
                vLightShaderPath = value;
            } else if (tag == "flightshader") {
                fLightShaderPath = value;
            } else if (tag == "msaa" && utility::isNat(value)) {
                msaa = std::stoi(value);
            }
        }

        input.close();
    } else {
        DEBUG_ERROR("Failed to load config file: " + configFilePath);
        DEBUG_DEC_DEPTH();
        return Error::CANT_OPEN;
    }

    DEBUG_DEC_DEPTH();
    return Error::OK;
}

void destroy() {}
}  // namespace config
