#pragma once

#ifdef DEBUG_MODE
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <tuple>

enum EDebugColors : uint8_t
{
    Red,
    Green,
    Blue,
    White,
    Black,
    Magenta
};

std::tuple<std::string, std::string> Ansi_To_Tuple(EDebugColors color)
{
    switch (color)
    {
        case EDebugColors::Red:
            return {"\033[1;31m", "\033[0m"};
            break;
        case EDebugColors::Green:
            return {"\033[1;32m", "\033[0m"};
            break;
        case EDebugColors::Blue:
            return {"\033[1;34m", "\033[0m"};
            break;
        case EDebugColors::White:
            return {"\033[1;37m", "\033[0m"};
            break;
        case EDebugColors::Black:
            return {"\033[1;30m", "\033[0m"};
            break;
        case EDebugColors::Magenta:
            return {"\033[1;35m", "\033[0m"};
            break;
        default:
            return {};
            break;
    }
}

#endif

/** 
 * Only called when DEBUG_MODE is defined
 * RELEASE_MODE optimization
 **/
template<typename... Args>
void Debug_Print(EDebugColors color, Args&&... args)
{
#ifdef DEBUG_MODE
    auto call_time = std::chrono::high_resolution_clock::now();
    auto time_struct = std::chrono::system_clock::to_time_t(call_time);
    std::cout << std::ctime(&time_struct);
    ([&]
    {
        // std::tuple<std::string, std::string> 
        const auto [color_begin_code, color_end_code] = Ansi_To_Tuple(color);
        std::cout << ">>> " << color_begin_code << args << color_end_code << std::endl;
    } (), ...);
#endif
}
