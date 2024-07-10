#pragma once

/*
 * This header contains definitions needed for debugging
 * (only when DEBUG_MODE is defined from CMake)
 * They are not compiled in production code so
 * they should not be used in shipped products
 */

#ifdef DEBUG_MODE

#endif /* DEBUG_MODE */

/* Supported Debug Colors
 * Limited to 256 colors
 *
 * !!! WARNINGS !!!
 * Lives outside DEBUG_MODE so that people do not have to worry
 * about deleting debug logs for releases
 * only the function definition will be compiled
 * and called with empty body
 */
enum class EDebugColors : unsigned char
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
