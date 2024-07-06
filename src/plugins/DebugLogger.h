#pragma once

#ifdef DEBUG_MODE
#include <iostream>
#include <chrono>
#include <ctime>
#endif

/** 
 * Only called when DEBUG_MODE is defined
 * RELEASE_MODE optimization
 **/
template<typename... Args>
void Debug_Print(Args&&... args)
{
#ifdef DEBUG_MODE
    auto call_time = std::chrono::high_resolution_clock::now();
    auto time_struct = std::chrono::system_clock::to_time_t(call_time);
    std::cout << std::ctime(&time_struct);
    ([&]
    {
        std::cout << ">>> " << args << std::endl;
    } (), ...);
#endif
}
