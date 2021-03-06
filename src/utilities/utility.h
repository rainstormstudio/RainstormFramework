/**
 * @file utility.h
 * @author Daniel Hongyu Ding
 * @brief This file defines some utility functions
 * @version 0.1
 * @date 2021-01-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_UTILITY_H
#define RS_UTILITY_H

#include "../debug/debug.h"
#include "includes.h"

namespace utility {

inline std::string trim(const std::string& str) {
    const auto begin = str.find_first_not_of(' ');
    if (begin == std::string::npos) {
        return "";
    }
    const auto end = str.find_last_not_of(' ');
    const auto range = end - begin + 1;

    return str.substr(begin, range);
}

inline bool isNat(const std::string& str) {
    return !str.empty() &&
           std::find_if(str.begin(), str.end(), [](unsigned char c) {
               return !std::isdigit(c);
           }) == str.end();
}

inline std::string toLower(const std::string& str) {
    std::string ans = "";
    for (auto ch : str) {
        if (ch >= 'A' && ch <= 'Z') {
            ans += ch - 'A' + 'a';
        } else {
            ans += ch;
        }
    }
    return ans;
}

inline bool toBool(const std::string& str) {
    std::string ans = toLower(str);
    return (ans == "t" || ans == "true");
}

std::string readFile(const char* filePath);

}  // namespace utility

#endif