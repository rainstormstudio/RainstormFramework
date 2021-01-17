#include "debug.h"

#include <iostream>

namespace debug {
    void msg(const char* expr, const char* file, int line) {
        std::cerr << "[" << file << "] at line " << line << ": " << expr << std::endl; 
    }

    void msg(const char* expr, int depth) {
        for (int i = 0; i < depth; i ++) {
            std::cerr << "    ";
        }
        std::cerr << "MSG: " << expr << std::endl;
    }

    void error(const char* expr, int depth) {
        for (int i = 0; i < depth; i ++) {
            std::cerr << "    ";
        }
        std::cerr << "ERROR: " << expr << std::endl;
    }

    void line(int depth ) {
        for (int i = 0; i < depth; i ++) {
            std::cerr << "    ";
        }
        for (int i = 0; i < 80 - depth * 4; i ++) {
            std::cerr << "-";
        }
        std::cerr << std::endl;
    }
}