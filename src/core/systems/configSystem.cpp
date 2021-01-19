#include "configSystem.h"

#include "../../debug/debug.h"
#include "../../utilities/utility.h"

namespace config {
std::string configFilePath = "./config/settings.cfg";
std::string vShaderPath = "./shaders/vertex.glsl";
std::string fShaderPath = "./shaders/fragment.glsl";

uint32_t screenWidth = 800;
uint32_t screenHeight = 600;
bool showFPS = true;
uint8_t msaa = 0;

Error initialize() {
    DEBUG_MSG("Initializing Configuration");

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

            tag = utility::toLower(utility::trim(tag));
            value = utility::toLower(utility::trim(value));

            DEBUG_MSG_INDENT("tag: " + tag, 1);
            DEBUG_MSG_INDENT("value: " + value, 1);
            DEBUG_LINE_INDENT(1);

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
            } else if (tag == "msaa" && utility::isNat(value)) {
                msaa = std::stoi(value);
            }
        }

        input.close();
    } else {
        DEBUG_ERROR("Failed to load config file: " + configFilePath);
        return Error::CANT_OPEN;
    }

    return Error::OK;
}

void destroy() {}
}  // namespace config
