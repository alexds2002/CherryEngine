#pragma once

/*
 * Should only be used for Logs that are needed in RELEASE_MODE.
 * Could be for debugging or for showing some information in Released products.
 * For debugging logs see debug_logger_component.h
 */

#include <project_definitions.h>
#include <iostream>
#include <chrono>

#include "log_categories.h"

/**
 * @brief Logs information to the standard output stream.
 *
 * This function prints the provided arguments to the console. It uses variadic
 * templates to accept a flexible number of arguments and formats them as
 * a single line of output.
 *
 * @tparam Args Variadic template parameter representing the types of the arguments to be logged.
 * @param args The arguments to be printed. These can be of any type that is compatible with `std::ostream` (e.g., `std::cout`).
 *
 * @note
 * - Before printing, the function checks whether the default logging category (`ELogCategory::Default`)
 *   is enabled. If it is disabled, no output is printed.
 * - The logging format starts with a prefix (`>>>`), followed by the arguments, each printed in sequence,
 *   and ends with a newline.
 *
 * @details
 * - The function uses the `LogManager` singleton to check whether the default log category is disabled.
 *   If the category is disabled, the function returns early without printing anything.
 * - The use of a fold expression `([&] { std::cout << args; } (), ...)` ensures that all arguments
 *   are printed in sequence, with no separator between them.
 * - This function is marked `noexcept` to ensure that it does not throw exceptions.
 *
 * Example usage:
 * @code
 * Debug_Log("This is a debug message with a number: ", 42);
 * // Output: >>> This is a debug message with a number: 42
 * @endcode
 */
template <typename... Args>
void Release_Log(Args&&... args) noexcept
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
void Release_Log(ELogCategory category, Args&&... args) noexcept
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
void Release_Log(const EPrintColor color, Args&&... args) noexcept
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
void Release_Log(ELogCategory category, const EPrintColor color, Args&&... args) noexcept
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
