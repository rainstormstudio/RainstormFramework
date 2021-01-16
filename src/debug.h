/**
 * @file debug.hpp
 * @author Daniel Hongyu Ding
 * @brief this file defines everything for debugging
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*
STATIC_ASSERT(expr) assert expr at compile-time

ASSERT(expr) assert expr at run-time

DEBUG_MSG(expr) put expr to standard error

DEBUG_MSG_INDENT(expr, depth) put expr with indentation based on depth
    to standard error

DEBUG_LINE() put a horizontal line to standard error

DEBUG_LINE_INDENT(depth) put a horizontal line with indentation
    based on depth to standard error
*/

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_ENABLED

    #ifdef __cplusplus
        #if __cplusplus >= 201103L
            #define STATIC_ASSERT(expr) \
                static_assert(expr, "static assert failed:"#expr)
        #endif
    #endif

    #if defined(__i386__) || defined(__x86_64__)
        #define debugbreak() __asm__ __volatile__("int3")
    #elif defined(__aarch64__)
        #define debugbreak() __asm__ __volatile__(".inst 0xd4200000")
    #elif defined(__arm__)
        #define debugbreak() __asm__ __volatile__(".inst 0xe7f001f0")
    #endif

    #define ASSERT(expr) \
    if (expr) {}  \
    else {  \
        debug::msg(#expr, __FILE__, __LINE__);  \
        debugbreak(); \
    }

    #define DEBUG_MSG(expr) debug::msg(expr)
    #define DEBUG_MSG_INDENT(expr, depth) debug::msg(expr, depth)
    #define DEBUG_LINE() debug::line()
    #define DEBUG_LINE_INDENT(depth) debug::line(depth)

#else
    #define STATIC_ASSERT(expr)
    #define ASSERT(expr) 
    #define DEBUG_MSG(expr) 
    #define DEBUG_MSG_INDENT(expr, depth) 
    #define DEBUG_LINE()
    #define DEBUG_LINE_INDENT(depth)
#endif

#include <iostream>
namespace debug {
    void msg(const char* expr, const char* file, int line) {
        std::cerr << "[" << file << "] at line " << line << ": " << expr << std::endl; 
    }

    void msg(const char* expr, int depth = 0) {
        for (int i = 0; i < depth; i ++) {
            std::cerr << "    ";
        }
        std::cerr << expr << std::endl;
    }

    void line(int depth = 0) {
        for (int i = 0; i < depth; i ++) {
            std::cerr << "    ";
        }
        for (int i = 0; i < 80 - depth * 4; i ++) {
            std::cerr << "-";
        }
        std::cerr << std::endl;
    }
};

#endif
