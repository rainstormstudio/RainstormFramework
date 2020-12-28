#define DEBUG_ENABLED 1
#include "debug.hpp"

int main() {
    DEBUG_LINE();
    DEBUG_MSG("start main");

    STATIC_ASSERT(sizeof(int) == 4);

    bool flag = true;

    ASSERT(flag);

    DEBUG_MSG("end main");

    DEBUG_LINE_INDENT(1);
    DEBUG_MSG_INDENT("main", 1);
    DEBUG_LINE_INDENT(1);

    return 0;
}