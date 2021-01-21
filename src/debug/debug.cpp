#include "debug.h"

#include <iostream>

namespace debug {

static unsigned int depth = 0;

void msg(const char* expr, const char* file, int line) {
    std::cerr << "[" << file << "] at line " << line << ": " << expr
              << std::endl;
}

void msg(std::string expr) {
    for (int i = 0; i < depth; i++) {
        std::cerr << "    ";
    }
    std::cerr << "MSG: " << expr << std::endl;
}

void msg(const char* expr) {
    for (int i = 0; i < depth; i++) {
        std::cerr << "    ";
    }
    std::cerr << "MSG: " << expr << std::endl;
}

void error(std::string expr) {
    for (int i = 0; i < depth; i++) {
        std::cerr << "    ";
    }
    std::cerr << "\033[0;31m"
              << "ERROR: " << expr << "\033[0m" << std::endl;
}

void error(const char* expr) {
    for (int i = 0; i < depth; i++) {
        std::cerr << "    ";
    }
    std::cerr << "\033[0;31m"
              << "ERROR: " << expr << "\033[0m" << std::endl;
}

void line(char ch) {
    for (int i = 0; i < depth; i++) {
        std::cerr << "    ";
    }
    for (int i = 0; i < 80 - depth * 4; i++) {
        std::cerr << ch;
    }
    std::cerr << std::endl;
}

void addDepth() { depth++; }

void decDepth() {
    if (depth) {
        depth--;
    }
}

}  // namespace debug