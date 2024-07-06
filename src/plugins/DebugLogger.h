#pragma once

/*
 *
 * DebugLogger is a collection of global variadic templated functions 
 * with different overload options(color, time/date, and more to come).
 * The functionalities get compiled ONLY when DEBUG_MODE is defined in CMake,
 * otherwise the funcitons bodies are compiled empty to avoid Debug Logs in RELEASE_MODE.
 * DebugLogger is planned to be a 'core' header that every class in the engine will have
 * so the debug colors will be visiable unless I put the file in a namespace.
 *
 */

#ifdef DEBUG_MODE
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <tuple>
#include <cinttypes>

/* Supported Debug Colors */
enum EDebugColors : uint8_t
{
    Red,
    Green,
    Blue,
    White,
    Black,
    Magenta,
    Cyan,
    Yellow,
    Gray,
    LightRed,
    LightGreen,
    LightBlue,
    LightWhite,
    LightMagenta,
    LightCyan,
    LightYellow
};

/* Convert color to its coresponding ANSI code */
std::string Ansi_To_Tuple(EDebugColors color)
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
            return "Invalid Color!!!";
            break;
    }
}

#endif

/** 
 * Only called when DEBUG_MODE is defined
 * RELEASE_MODE optimization
 * Print with @color
 **/
template<class... Args>
void Debug_Print(EDebugColors color, Args&&... args)
{
#ifdef DEBUG_MODE
    auto call_time = std::chrono::high_resolution_clock::now();
    auto time_struct = std::chrono::system_clock::to_time_t(call_time);
    std::cout << std::ctime(&time_struct);
    ([&]
    {
        std::string color_code = Ansi_To_Tuple(color);
        // \033[m -> eding color tag
        std::cout << ">>> " << color_code << args << "\033[m" << std::endl;
    } (), ...);
#endif
}

/** 
 * Only called when DEBUG_MODE is defined
 * RELEASE_MODE optimization
 * Print without color
 **/
template<class... Args>
void Debug_Print(Args&&... args)
{
#ifdef DEBUG_MODE
    auto call_time = std::chrono::high_resolution_clock::now();
    auto time_struct = std::chrono::system_clock::to_time_t(call_time);
    std::cout << std::ctime(&time_struct);
    ([&]
    {
        std::string color_code = Ansi_To_Tuple(EDebugColors::White);
        // \033[m -> ending color tag
        std::cout << ">>> " << color_code << args << "\033[m" << std::endl;
    } (), ...);
#endif
}

/** 
 * Only called when DEBUG_MODE is defined
 * RELEASE_MODE optimization
 * Print with @color
 * @bPrintTime shows the time of the function call if true
 **/
template<class... Args>
void Debug_Print(EDebugColors color, bool bPrintTime, Args&&... args)
{
#ifdef DEBUG_MODE
    if(bPrintTime)
    {
        auto call_time = std::chrono::high_resolution_clock::now();
        auto time_struct = std::chrono::system_clock::to_time_t(call_time);
        std::cout << std::ctime(&time_struct);
    }
    ([&]
    {
        std::string color_code = Ansi_To_Tuple(color);
        // \033[m -> ending color tag
        std::cout << ">>> " << color_code << args << "\033[m" << std::endl;
    } (), ...);
#endif
}
