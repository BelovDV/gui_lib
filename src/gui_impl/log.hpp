#pragma once

#ifdef MAKE_LOG
#include <iostream>
#include <sstream>
extern unsigned LOG_DEPTH;
#define LOG(VAR)                                                               \
  do {                                                                         \
    std::stringstream buffer;                                                  \
    buffer << __FILE__ << ':' << __LINE__;                                     \
    auto vsp = buffer.str();                                                   \
    vsp.resize(30, ' ');                                                       \
    std::cout << vsp << ":  ";                                                 \
    for (unsigned i = 0; i < LOG_DEPTH; ++i)                                   \
      std::cout << (i % 2 ? "|   " : ";   ");                                  \
    vsp = #VAR;                                                                \
    vsp.resize(25, ' ');                                                       \
    std::cout << vsp << ": '" << VAR << "'\n";                                 \
  } while (false)
#define LOG_IN                                                                 \
  do {                                                                         \
    std::stringstream buffer;                                                  \
    buffer << __FILE__ << ':' << __LINE__;                                     \
    auto vsp = buffer.str();                                                   \
    vsp.resize(30, ' ');                                                       \
    std::cout << vsp << ":  ";                                                 \
    for (unsigned i = 0; i < LOG_DEPTH; ++i)                                   \
      std::cout << (i % 2 ? "|   " : ";   ");                                  \
    std::stringstream buffer_2;                                                \
    buffer_2 << __PRETTY_FUNCTION__;                                           \
    vsp = buffer_2.str();                                                      \
    vsp.resize(35, ' ');                                                       \
    std::cout << vsp << '\n';                                                  \
    ++LOG_DEPTH;                                                               \
  } while (0)
#define LOG_OUT --LOG_DEPTH
#else
#define LOG(...)
#define LOG_IN
#define LOG_OUT
#endif
