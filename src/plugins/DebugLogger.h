#pragma once

//TODO(Alex): add this DEBUG_MODE in CMake
#define DEBUG_MODE

#ifdef DEBUG_MODE
#include <iostream>
#include <chrono>
#include <ctime>
#endif

/** 
 * Only called when DEBUG_MODE is defined
 **/
template<typename... Args>
void Debug_Print(Args&&... args)
{
    auto call_time = std::chrono::high_resolution_clock::now();
    auto time_struct = std::chrono::system_clock::to_time_t(call_time);
    std::cout << std::ctime(&time_struct);
#ifdef DEBUG_MODE
    ([&]
    {
        std::cout << ">>> " << args << std::endl;
    } (), ...);
#endif
}
