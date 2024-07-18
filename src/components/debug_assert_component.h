#pragma once

/*
 * Custom Cherry Assert macro for checking a condition and aborting if true.
 * The CHERRY_ASSERT macro is empty in anything other than DEBUG_MODE,
 * since it is only needed for debugging.
 * TODO(Alex): Add this file in one big core.h file.
 *
 * !!! WARNING !!!
 * The macro works only with exprecions with valid operator!
 */

#ifdef DEBUG_MODE

#include <iostream>

/* Helper macros to count arguments */
#define NUM_ARGS_IMPL(_1, _2, N, ...) N
#define NUM_ARGS(...) NUM_ARGS_IMPL(__VA_ARGS__, 2, 1, 0)
/* Helper macros to call the correct implementation based on the number of arguments */
#define PRINT_IMPL_1(arg1) std::cout << (arg1) << std::endl
#define PRINT_IMPL_2(arg1, arg2) std::cout << (arg1) << ", " << (arg2) << std::endl
#define CHERRY_ASSERT_1(condition) \
    if(!(condition)) \
{            \
    std::cerr << "CHERRY_ASSERT: Assert failed" << std::endl; \
    std::exit(1);\
}
#define CHERRY_ASSERT_2(condition, message) \
    if(!(condition)) \
{            \
    std::cerr << "CHERRY_ASSERT: Assert failed" << std::endl; \
    std::cerr << message << std::endl;\
    std::exit(1);\
}
/* Macro to select the correct implementation */
#define CHERRY_ASSERT_IMPL_REDIRECT(count) CHERRY_ASSERT_##count
#define CHERRY_ASSERT_IMPL(count) CHERRY_ASSERT_IMPL_REDIRECT(count)

/*
 * Main macro that dispatches to the correct implementation based on the number of arguments(if message is passed or not).
 * Code inside is only compiled in DEBUG_MODE similiar to std::assert()
 */
#define CHERRY_ASSERT(...) CHERRY_ASSERT_IMPL(NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#else /* DEBUG_MODE not defined */

#define CHERRY_ASSERT(...) ((void)0)

#endif /* DEBUG_MODE */
