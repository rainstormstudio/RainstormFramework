#include "utility.h"

std::string utility::readFile(const char* filePath) {
    std::string content;
    std::ifstream input(filePath, std::ios::in);
    if (!input.is_open()) {
        DEBUG_ERROR_INDENT("Failed to load file: " + std::string(filePath), 1);
        return "";
    }
    DEBUG_MSG_INDENT("Loaded file: " + std::string(filePath), 1);

    std::string line = "";
    while (std::getline(input, line)) {
        content.append(line + "\n");
    }

    input.close();
    return content;
}
