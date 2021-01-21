#include "utility.h"

std::string utility::readFile(const char* filePath) {
    DEBUG_ADD_DEPTH();
    std::string content;
    std::ifstream input(filePath, std::ios::in);
    if (!input.is_open()) {
        DEBUG_ERROR("Failed to load file: " + std::string(filePath));
        DEBUG_DEC_DEPTH();
        return "";
    }
    DEBUG_MSG("Loaded file: " + std::string(filePath));

    std::string line = "";
    while (std::getline(input, line)) {
        content.append(line + "\n");
    }

    input.close();
    DEBUG_DEC_DEPTH();
    return content;
}
