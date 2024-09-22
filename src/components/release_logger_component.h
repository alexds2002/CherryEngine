#pragma once

/*
 * Should only be used for Logs that are NEEDED in RELEASE_MODE.
 * Could be for debugging or for showing some information in Released products.
 * For debugging logs see debug_logger_component.h
 */

#include <project_definitions.h>
#include <iostream>
#include <chrono>

#include "log_categories.h"

/**
 * @brief Print on the standard output dynamic number of args
 *
 * @param ...args: dinamic number of arguments to print regardless of their type
 * Example usage:
 * Release_Log("Loading next level", 69, 420.69);
 *
 * @return void
 */
template <typename... Args>
void Release_Log(Args&&... args)
{
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(ELogCategory::Default))
    {
        return;
    }
    std::cout << ">>> ";
    ([&]()
    {
        std::cout << args;
    }(), ...);
    std::cout << std::endl;
}

/**
 * @brief Print on the standard output dynamic number of args
 *
 * @param ...args: dinamic number of arguments to print regardless of their type
 * Example usage:
 * Release_Log("Loading next level", 69, 420.69);
 *
 * @return void
 */
template <typename... Args>
void Release_Log(ELogCategory category, Args&&... args)
{
    LogManager* logManager = LogManager::GetInstance();
    if(logManager->IsCategoryDisabled(category))
    {
        return;
    }
    std::cout << ">>> ";
    ([&]()
    {
        std::cout << args;
    }(), ...);
    std::cout << std::endl;
}

/**
 * @brief Print on the standard output dynamic number of args
 *
 * @param ...args: dinamic number of arguments to print regardless of their type
 * @param color: color of the output
 *
 * Example usage:
 * Release_Log(EPrintColor::Red, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template <typename... Args>
void Release_Log(const EPrintColor color, Args&&... args)
{
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
}


/**
 * @brief Print on the standard output dynamic number of args
 *
 * @param ...args: dinamic number of arguments to print regardless of their type
 * @param color: color of the output
 *
 * Example usage:
 * Release_Log(EPrintColor::Red, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template <typename... Args>
void Release_Log(ELogCategory category, const EPrintColor color, Args&&... args)
{
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
}

/**
 * @brief Print on standard output stream dynamic number of args with color and time option
 *
 * @param  color: print color
 * @param  bShowTime: show date and time of function call
 * @param ...args: dinamic number of arguments to print regardles of their type
 *
 * Example usage:
 * Release_Log(EPrintColor::Red, true, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Release_Log(const EPrintColor color, const bool bShowTime, Args&&... args) noexcept
{
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
}

/**
 * @brief Print on standard output stream dynamic number of args with color and time option
 *
 * @param  color: print color
 * @param  bShowTime: show date and time of function call
 * @param ...args: dinamic number of arguments to print regardles of their type
 *
 * Example usage:
 * Release_Log(EPrintColor::Red, true, "Loading next level", 69, 420.69);
 *
 * @return void
 */
template<class... Args>
inline void Release_Log(ELogCategory category, const EPrintColor color, const bool bShowTime, Args&&... args) noexcept
{
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
}
