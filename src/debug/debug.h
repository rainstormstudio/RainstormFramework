/**
 * @file debug.hpp
 * @author Daniel Hongyu Ding
 * @brief this file defines functions for displaying debug messages
 * @version 0.2
 * @date 2021-01-16
 *
 * @copyright Copyright (c) 2020
 *
 */

/*
STATIC_ASSERT(expr) assert expr at compile-time

ASSERT(expr) assert expr at run-time

DEBUG_ADD_DEPTH() add one level more indentation for displaying

DEBUG_DEC_DEPTH() decrease on level of indentation

DEBUG_MSG(expr) put expr to standard error

DEBUG_LINE() put a horizontal line to standard error

DEBUG_ERROR(expr) put expr to standard error
*/

#ifndef RS_DEBUG_H
#define RS_DEBUG_H

#include <string>

#ifndef NDEBUG

#ifdef __cplusplus
#if __cplusplus >= 201103L
#define STATIC_ASSERT(expr) static_assert(expr, "static assert failed:" #expr)
#endif
#endif

#if defined(__i386__) || defined(__x86_64__)
#define debugbreak() __asm__ __volatile__("int3")
#elif defined(__aarch64__)
#define debugbreak() __asm__ __volatile__(".inst 0xd4200000")
#elif defined(__arm__)
#define debugbreak() __asm__ __volatile__(".inst 0xe7f001f0")
#endif

#define ASSERT(expr)                           \
    if (expr) {                                \
    } else {                                   \
        debug::msg(#expr, __FILE__, __LINE__); \
        debugbreak();                          \
    }

#define DEBUG_ADD_DEPTH() debug::addDepth()
#define DEBUG_DEC_DEPTH() debug::decDepth()
#define DEBUG_MSG(expr) debug::msg(expr)
#define DEBUG_LINE() debug::line()
#define DEBUG_DLINE() debug::line('=')
#define DEBUG_ERROR(expr) debug::error(expr)

#else
#define STATIC_ASSERT(expr)
#define ASSERT(expr)
#define DEBUG_ADD_DEPTH()
#define DEBUG_DEC_DEPTH()
#define DEBUG_MSG(expr)
#define DEBUG_DLINE()
#define DEBUG_LINE()
#define DEBUG_ERROR(expr)
#endif

namespace debug {
void msg(const char* expr, const char* file, int line);

void msg(std::string expr);

void msg(const char* expr);

void error(std::string expr);

void error(const char* expr);

void line(char ch = '-');

void addDepth();

void decDepth();
}  // namespace debug

#endif
