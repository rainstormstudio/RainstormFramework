#include "utility.h"

std::string utility::readFile(const char* filePath) {
    std::string content;
    std::ifstream input(filePath, std::ios::in);
    if (!input.is_open()) {
        DEBUG_ERROR("Failed to load file: " + std::string(filePath));
        return "";
    }

    std::string line = "";
    while (std::getline(input, line)) {
        content.append(line + "\n");
    }

    input.close();
    return content;
}
