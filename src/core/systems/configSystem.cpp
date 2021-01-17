#include "configSystem.h"
#include "../../utilities/utility.h"

namespace config {
    std::string configFilePath = "./config/settings.cfg";

    uint32_t screenWidth = 800;
    uint32_t screenHeight = 600;

    void initialize() {
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

                if (tag == "screenwidth" && utility::isNat(value)) {
                    screenWidth = std::stoi(value);
                } else if (tag == "screenheight" && utility::isNat(value)) {
                    screenHeight = std::stoi(value);
                }
            }
            

            input.close();
        }
    }

    void destroy() {

    }
}

