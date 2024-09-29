#pragma once

#ifdef DEBUG_MODE

#include <iostream>

/**
 * @file CherryAssert.h
 * @brief Macros for handling assertions with optional messages.
 *
 * This header defines macros to assert conditions and optionally print custom
 * error messages. It uses variadic macros to determine the number of arguments
 * passed (either 1 or 2) and calls the appropriate assertion implementation.
 *
 * If `DEBUG_MODE` is not defined, assertions are disabled and compiled out.
 *
 * Example usage:
 * @code
 * CHERRY_ASSERT(x > 0);                     // Asserts with a condition
 * CHERRY_ASSERT(x > 0, "x must be positive"); // Asserts with a custom error message
 * @endcode
 */

/**
 * @brief Macro to help determine the number of arguments passed to `CHERRY_ASSERT`.
 *
 * This helper macro is used internally to implement variadic argument counting.
 */
#define NUM_ARGS_IMPL(_1, _2, N, ...) N

/**
 * @brief Counts the number of arguments passed.
 *
 * This macro determines how many arguments are passed to `CHERRY_ASSERT`,
 * so the correct implementation (with or without a message) can be selected.
 *
 * @param ... Variadic arguments.
 * @return The number of arguments passed (1 or 2).
 */
#define NUM_ARGS(...) NUM_ARGS_IMPL(__VA_ARGS__, 2, 1, 0)

/**
 * @brief Prints a single argument.
 *
 * This is the implementation that handles a single argument for printing.
 *
 * @param arg1 The argument to print.
 */
#define PRINT_IMPL_1(arg1) std::cout << (arg1) << std::endl

/**
 * @brief Prints two arguments.
 *
 * This is the implementation that handles two arguments for printing.
 *
 * @param arg1 The first argument to print.
 * @param arg2 The second argument to print.
 */
#define PRINT_IMPL_2(arg1, arg2) std::cout << (arg1) << ", " << (arg2) << std::endl

/**
 * @brief Asserts a condition without a custom message.
 *
 * If the condition is false, an error message is printed, and the program
 * exits with a failure code.
 *
 * @param condition The condition to assert.
 */
#define CHERRY_ASSERT_1(condition) \
    if(!(condition)) \
{            \
    std::cerr << "CHERRY_ASSERT: Assert failed" << std::endl; \
    std::exit(1);\
}

/**
 * @brief Asserts a condition with a custom message.
 *
 * If the condition is false, an error message and the provided custom message
 * are printed, and the program exits with a failure code.
 *
 * @param condition The condition to assert.
 * @param message The custom message to print if the assertion fails.
 */
#define CHERRY_ASSERT_2(condition, message) \
    if(!(condition)) \
{            \
    std::cerr << "CHERRY_ASSERT: Assert failed" << std::endl; \
    std::cerr << message << std::endl;\
    std::exit(1);\
}

/**
 * @brief Redirects to the appropriate `CHERRY_ASSERT` implementation based on the argument count.
 *
 * This helper macro selects the correct `CHERRY_ASSERT` implementation depending on whether
 * 1 or 2 arguments were passed to the main `CHERRY_ASSERT` macro.
 *
 * @param count The number of arguments passed.
 */
#define CHERRY_ASSERT_IMPL_REDIRECT(count) CHERRY_ASSERT_##count

/**
 * @brief Selects the correct `CHERRY_ASSERT` implementation.
 *
 * This macro directs to the appropriate `CHERRY_ASSERT` function, based on the
 * number of arguments passed.
 *
 * @param count The number of arguments passed (determined by `NUM_ARGS`).
 */
#define CHERRY_ASSERT_IMPL(count) CHERRY_ASSERT_IMPL_REDIRECT(count)

/**
 * @brief Main macro that handles assertions with an optional custom message.
 *
 * This macro asserts the given condition and optionally takes a custom error message
 * as the second argument. It uses `NUM_ARGS` to determine the number of arguments passed
 * and dispatches to the appropriate implementation.
 *
 * @note This macro behaves similarly to `std::assert()`, but it only compiles
 *       in `DEBUG_MODE`. When `DEBUG_MODE` is not defined, this macro does nothing.
 *
 * @param ... Variadic arguments: a condition and an optional custom message.
 */
#define CHERRY_ASSERT(...) CHERRY_ASSERT_IMPL(NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#else /* DEBUG_MODE not defined */

/**
 * @brief Disables `CHERRY_ASSERT` when `DEBUG_MODE` is not defined.
 *
 * In non-debug builds, this macro does nothing and is optimized out.
 */
#define CHERRY_ASSERT(...) ((void)0)

#endif /* DEBUG_MODE */
