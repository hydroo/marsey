#ifndef DEBUG_HPP
#define DEBUG_HPP


#include <iostream>

#ifdef DEBUG
#define ASSERT(expression) \
    if ((expression) == false) { \
        std::cerr << "\e[0;31m\033[1m" \
                << "ASSERT" \
                << "\033[0m\e[0;30m" \
                << " in " << __FILE__ << ":" << __LINE__ \
                << ": \"" << #expression << "\"" << std::endl; \
        std::abort(); \
    }
#else
#define ASSERT(expression)
#endif


#endif /* DEBUG_HPP */
