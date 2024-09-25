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

/* needed outside DEBUG_MODE to compile in other modes (EPrintColor)*/
#include <project_definitions.h>

#ifdef DEBUG_MODE

#include <iostream>
#include <chrono>
#include <ctime>

#include "log_categories.h"

#endif /* DEBUG_MODE */

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
    /* Do not print if the default category is disabled */
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(ELogCategory::Default))
    {
        return;
    }
    std::cout << ">>> ";
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << std::endl;
#endif /* DEBUG_MODE */
}

/**
 * @brief Print on console dynamic number of args with a print category
 *
 * The body of the function is only compiled in DEBUG_MODE(RELEASE_MODE optimization)
 *
 * @param  category: print category
 * @param ...args: dinamic number of arguments to print regardless of their type
 *
 * Example usage:
 * Debug_Log("Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(ELogCategory category, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    /* Do not print disabled categories */
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(category))
    {
        return;
    }
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
 * Debug_Log(EPrintColor::Red, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(const EPrintColor color, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    /* Do not print if default category is disabled */
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(ELogCategory::Default))
    {
        return;
    }
    std::string color_code = Color_To_Ansi(color);
    std::cout << ">>> " << color_code;
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << UNIX_COLOR_END_TAG << std::endl;
#endif /* DEBUG_MODE */
}

/**
 * @brief Print on console dynamic number of args with color and a category
 *
 * The body of the function is only compiled in DEBUG_MODE(RELEASE_MODE optimization)
 *
 * @param  category: category to print in
 * @param  color: print color
 * @param ...args: dinamic number of arguments to print regardles of their type
 *
 * Example usage:
 * Debug_Log(EPrintColor::Red, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(const ELogCategory category, const EPrintColor color, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    /* Do not print disabled categories */
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(category))
    {
        return;
    }
    std::string color_code = Color_To_Ansi(color);
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
 * Debug_Log(EPrintColor::Red, true, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(const EPrintColor color, const bool bShowTime, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(ELogCategory::Default))
    {
        return;
    }
    if(bShowTime)
    {
        auto call_time = std::chrono::high_resolution_clock::now();
        auto time_struct = std::chrono::system_clock::to_time_t(call_time);
        std::cout << std::ctime(&time_struct);
    }
    std::string color_code = Color_To_Ansi(color);
    std::cout << ">>> " << color_code;
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << UNIX_COLOR_END_TAG << std::endl;
#endif /* DEBUG_MODE */
}

/**
 * @brief Print on console dynamic number of args with color, time and category option
 *
 * The body of the function is only compiled in DEBUG_MODE(RELEASE_MODE optimization)
 *
 * @param  category: print category
 * @param  color: print color
 * @param  bShowTime: show date and time of function call
 * @param ...args: dinamic number of arguments to print regardles of their type
 *
 * Example usage:
 * Debug_Log(EPrintColor::Red, true, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Debug_Log(const ELogCategory category, const EPrintColor color, const bool bShowTime, Args&&... args) noexcept
{
#ifdef DEBUG_MODE
    /* Do not print disabled categories */
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(category))
    {
        return;
    }
    if(bShowTime)
    {
        auto call_time = std::chrono::high_resolution_clock::now();
        auto time_struct = std::chrono::system_clock::to_time_t(call_time);
        std::cout << std::ctime(&time_struct);
    }
    std::string color_code = Color_To_Ansi(color);
    std::cout << ">>> " << color_code;
    ([&]
    {
        std::cout << args;
    } (), ...);
    std::cout << UNIX_COLOR_END_TAG << std::endl;
#endif /* DEBUG_MODE */
}

