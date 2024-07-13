#pragma once

/*
 *
 * debug_logger_component is a collection of global variadic templated functions
 * with different overload options(color, time/date, and more to come).
 * The functionalities get compiled ONLY when DEBUG_MODE is defined in CMake,
 * otherwise the funcitons bodies are compiled empty to avoid Debug Logs in RELEASE_MODE(optimization).
 * TODO(Alex): debug_logger_component is planned to be a 'core' header that every class in the engine will have.
 *
 * !!! WARNINGS !!!
 * Shipped products(in RELEASE_MODE) should not rely on these functions as they are only compiled in DEBUG_MODE
 * However you do not need to delete them when shipping.
 * (BUG warning)inline global function with external linkage have undefined behavior
 * fix is to remove inline then the compilation will crash becouse of redefinition.
 *
 */

#include <debug_mode_definitions.h>

#ifdef DEBUG_MODE
#include <iostream>
#include <chrono>
#include <ctime>

#define UNIX_COLOR_END_TAG "\033[m"
#endif /* DEBUG_MODE */

namespace DebugOnly
{
namespace
{
#ifdef DEBUG_MODE

/**
 * @brief Convert color to its coresponding ANSI code
 *
 * Color converter for Unix systems, compiled when DEBUG_MODE is defined(RELEASE_MODE optimization)
 *
 * @param color: enum color to be converted
 *
 * @return std::string: corresponding ANSI code
 */
std::string Ansi_To_Tuple(const EDebugColors color) noexcept
{
    switch (color)
    {
        case EDebugColors::Red:
            return "\033[1;31m";
            break;
        case EDebugColors::Green:
            return "\033[1;32m";
            break;
        case EDebugColors::Blue:
            return "\033[1;34m";
            break;
        case EDebugColors::White:
            return "\033[1;37m";
            break;
        case EDebugColors::Black:
            return "\033[1;30m";
            break;
        case EDebugColors::Magenta:
            return "\033[1;35m";
            break;
        case EDebugColors::Cyan:
            return "\033[1;36m";
            break;
        case EDebugColors::Yellow:
            return "\033[1;33m";
            break;
        case EDebugColors::Gray:
            return "\033[1;90m";
            break;
        case EDebugColors::LightRed:
            return "\033[1;91m";
            break;
        case EDebugColors::LightGreen:
            return "\033[1;92m";
            break;
        case EDebugColors::LightBlue:
            return "\033[1;94m";
            break;
        case EDebugColors::LightWhite:
            return "\033[1;97m";
            break;
        case EDebugColors::LightMagenta:
            return "\033[1;95m";
            break;
        case EDebugColors::LightCyan:
            return "\033[1;96m";
            break;
        case EDebugColors::LightYellow:
            return "\033[1;94m";
            break;
        default:
            return "\033[1;37m"; // return White by default
            break;
    }
}
} /* empty namespace */
#endif /* DEBUG_MODE */
} /* namespace DebugOnly */

/**
 * @brief Print on console dynamic number of args
 *
 * The body of the function is only compiled in DEBUG_MODE(RELEASE_MODE optimization)
 *
 * @param ...args: dinamic number of arguments to print regardless of their type
 * Example usage:
 * Debug_Log("Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    std::cout << ">>> ";
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << std::endl;
#endif /* DEBUG_MODE */
}

/**
 * @brief Print on console dynamic number of args with color
 *
 * The body of the function is only compiled in DEBUG_MODE(RELEASE_MODE optimization)
 *
 * @param  color: print color
 * @param ...args: dinamic number of arguments to print regardles of their type
 *
 * Example usage:
 * Debug_Log(EDebugColors::Red, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(const EDebugColors color, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    std::string color_code = DebugOnly::Ansi_To_Tuple(color);
    std::cout << ">>> " << color_code;
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << UNIX_COLOR_END_TAG << std::endl;
#endif /* DEBUG_MODE */
}

/**
 * @brief Print on console dynamic number of args with color and time option
 *
 * The body of the function is only compiled in DEBUG_MODE(RELEASE_MODE optimization)
 *
 * @param  color: print color
 * @param  bShowTime: show date and time of function call
 * @param ...args: dinamic number of arguments to print regardles of their type
 *
 * Example usage:
 * Debug_Log(EDebugColors::Red, true, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(const EDebugColors color, const bool bShowTime, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    if(bShowTime)
    {
        auto call_time = std::chrono::high_resolution_clock::now();
        auto time_struct = std::chrono::system_clock::to_time_t(call_time);
        std::cout << std::ctime(&time_struct);
    }
    std::string color_code = DebugOnly::Ansi_To_Tuple(color);
    std::cout << ">>> " << color_code;
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << UNIX_COLOR_END_TAG << std::endl;
#endif /* DEBUG_MODE */
}

