#pragma once

#include <string>

#define UNIX_COLOR_END_TAG "\033[m"

struct Position
{
    double x;
    double y;
};


/* supported key mappings equivelent to glfw */
enum KeyCode
{
    CHERRY_KEY_SPACE           = 32,
    CHERRY_KEY_APOSTROPHE      = 39, /*, ' */
    CHERRY_KEY_COMMA           = 44, /*, , */
    CHERRY_KEY_MINUS           = 45, /*, - */
    CHERRY_KEY_PERIOD          = 46, /*, . */
    CHERRY_KEY_SLASH           = 47, /*, / */
    CHERRY_KEY_0               = 48,
    CHERRY_KEY_1               = 49,
    CHERRY_KEY_2               = 50,
    CHERRY_KEY_3               = 51,
    CHERRY_KEY_4               = 52,
    CHERRY_KEY_5               = 53,
    CHERRY_KEY_6               = 54,
    CHERRY_KEY_7               = 55,
    CHERRY_KEY_8               = 56,
    CHERRY_KEY_9               = 57,
    CHERRY_KEY_SEMICOLON       = 59, /* ; */
    CHERRY_KEY_EQUAL           = 61, /* = */
    CHERRY_KEY_A               = 65,
    CHERRY_KEY_B               = 66,
    CHERRY_KEY_C               = 67,
    CHERRY_KEY_D               = 68,
    CHERRY_KEY_E               = 69,
    CHERRY_KEY_F               = 70,
    CHERRY_KEY_G               = 71,
    CHERRY_KEY_H               = 72,
    CHERRY_KEY_I               = 73,
    CHERRY_KEY_J               = 74,
    CHERRY_KEY_K               = 75,
    CHERRY_KEY_L               = 76,
    CHERRY_KEY_M               = 77,
    CHERRY_KEY_N               = 78,
    CHERRY_KEY_O               = 79,
    CHERRY_KEY_P               = 80,
    CHERRY_KEY_Q               = 81,
    CHERRY_KEY_R               = 82,
    CHERRY_KEY_S               = 83,
    CHERRY_KEY_T               = 84,
    CHERRY_KEY_U               = 85,
    CHERRY_KEY_V               = 86,
    CHERRY_KEY_W               = 87,
    CHERRY_KEY_X               = 88,
    CHERRY_KEY_Y               = 89,
    CHERRY_KEY_Z               = 90,
    CHERRY_KEY_LEFT_BRACKET    = 91, /* [ */
    CHERRY_KEY_BACKSLASH       = 92, /* \ */
    CHERRY_KEY_RIGHT_BRACKET   = 93, /* ] */
    CHERRY_KEY_GRAVE_ACCENT    = 96, /* ` */
    CHERRY_KEY_WORLD_1         = 161, /* non-US #1 */
    CHERRY_KEY_WORLD_2         = 162, /* non-US #2 */
    CHERRY_KEY_ESCAPE          = 256,
    CHERRY_KEY_ENTER           = 257,
    CHERRY_KEY_TAB             = 258,
    CHERRY_KEY_BACKSPACE       = 259,
    CHERRY_KEY_INSERT          = 260,
    CHERRY_KEY_DELETE          = 261,
    CHERRY_KEY_RIGHT           = 262,
    CHERRY_KEY_LEFT            = 263,
    CHERRY_KEY_DOWN            = 264,
    CHERRY_KEY_UP              = 265,
    CHERRY_KEY_PAGE_UP         = 266,
    CHERRY_KEY_PAGE_DOWN       = 267,
    CHERRY_KEY_HOME            = 268,
    CHERRY_KEY_END             = 269,
    CHERRY_KEY_CAPS_LOCK       = 280,
    CHERRY_KEY_SCROLL_LOCK     = 281,
    CHERRY_KEY_NUM_LOCK        = 282,
    CHERRY_KEY_PRINT_SCREEN    = 283,
    CHERRY_KEY_PAUSE           = 284,
    CHERRY_KEY_F1              = 290,
    CHERRY_KEY_F2              = 291,
    CHERRY_KEY_F3              = 292,
    CHERRY_KEY_F4              = 293,
    CHERRY_KEY_F5              = 294,
    CHERRY_KEY_F6              = 295,
    CHERRY_KEY_F7              = 296,
    CHERRY_KEY_F8              = 297,
    CHERRY_KEY_F9              = 298,
    CHERRY_KEY_F10             = 299,
    CHERRY_KEY_F11             = 300,
    CHERRY_KEY_F12             = 301,
    CHERRY_KEY_F13             = 302,
    CHERRY_KEY_F14             = 303,
    CHERRY_KEY_F15             = 304,
    CHERRY_KEY_F16             = 305,
    CHERRY_KEY_F17             = 306,
    CHERRY_KEY_F18             = 307,
    CHERRY_KEY_F19             = 308,
    CHERRY_KEY_F20             = 309,
    CHERRY_KEY_F21             = 310,
    CHERRY_KEY_F22             = 311,
    CHERRY_KEY_F23             = 312,
    CHERRY_KEY_F24             = 313,
    CHERRY_KEY_F25             = 314,
    CHERRY_KEY_KP_0            = 320,
    CHERRY_KEY_KP_1            = 321,
    CHERRY_KEY_KP_2            = 322,
    CHERRY_KEY_KP_3            = 323,
    CHERRY_KEY_KP_4            = 324,
    CHERRY_KEY_KP_5            = 325,
    CHERRY_KEY_KP_6            = 326,
    CHERRY_KEY_KP_7            = 327,
    CHERRY_KEY_KP_8            = 328,
    CHERRY_KEY_KP_9            = 329,
    CHERRY_KEY_KP_DECIMAL      = 330,
    CHERRY_KEY_KP_DIVIDE       = 331,
    CHERRY_KEY_KP_MULTIPLY     = 332,
    CHERRY_KEY_KP_SUBTRACT     = 333,
    CHERRY_KEY_KP_ADD          = 334,
    CHERRY_KEY_KP_ENTER        = 335,
    CHERRY_KEY_KP_EQUAL        = 336,
    CHERRY_KEY_LEFT_SHIFT      = 340,
    CHERRY_KEY_LEFT_CONTROL    = 341,
    CHERRY_KEY_LEFT_ALT        = 342,
    CHERRY_KEY_LEFT_SUPER      = 343,
    CHERRY_KEY_RIGHT_SHIFT     = 344,
    CHERRY_KEY_RIGHT_CONTROL   = 345,
    CHERRY_KEY_RIGHT_ALT       = 346,
    CHERRY_KEY_RIGHT_SUPER     = 347,
    CHERRY_KEY_MENU            = 348,
    CHERRY_KEY_LAST            = CHERRY_KEY_MENU,
    GLFW_KEY_UNKNOWN           = -1
};

/* key states deffinitions */
enum KeyState
{
    CHERRY_RELEASE  = 0,
    CHERRY_PRESS    = 1,
    CHERRY_REPEAT   = 2
};

/* mouse key codes */
enum MouseKeyCode
{
    CHERRY_MOUSE_BUTTON_1      = 0,
    CHERRY_MOUSE_BUTTON_2      = 1,
    CHERRY_MOUSE_BUTTON_3      = 2,
    CHERRY_MOUSE_BUTTON_4      = 3,
    CHERRY_MOUSE_BUTTON_5      = 4,
    CHERRY_MOUSE_BUTTON_6      = 5,
    CHERRY_MOUSE_BUTTON_7      = 6,
    CHERRY_MOUSE_BUTTON_8      = 7,
    CHERRY_MOUSE_BUTTON_LAST   = CHERRY_MOUSE_BUTTON_8,
    CHERRY_MOUSE_BUTTON_LEFT   = CHERRY_MOUSE_BUTTON_1,
    CHERRY_MOUSE_BUTTON_RIGHT  = CHERRY_MOUSE_BUTTON_2,
    CHERRY_MOUSE_BUTTON_MIDDLE = CHERRY_MOUSE_BUTTON_3
};

/*
 * Supported Log Colors
 * Limited to 256 colors
 */
enum class EPrintColor : unsigned char
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

/*
 * Debug categories to filter Logs
 */
enum class ELogCategory : int
{
    Default,
    Error,
    Core,
    Editor,
    Component,
    Threads,
    AutoCount /* Should be last! Number of categories */
};

enum class ELogCategoryState : int
{
    Enabled,
    Disabled,
    AutoCount
};

/**
 * @brief Convert color to its coresponding ANSI code
 *
 * Color converter for Unix systems, compiled when DEBUG_MODE is defined(RELEASE_MODE optimization)
 *
 * @param color: enum color to be converted
 *
 * @return std::string: corresponding ANSI code
 */
inline std::string Color_To_Ansi(const EPrintColor color) noexcept
{
    switch (color)
    {
        case EPrintColor::Red:
            return "\033[1;31m";
            break;
        case EPrintColor::Green:
            return "\033[1;32m";
            break;
        case EPrintColor::Blue:
            return "\033[1;34m";
            break;
        case EPrintColor::White:
            return "\033[1;37m";
            break;
        case EPrintColor::Black:
            return "\033[1;30m";
            break;
        case EPrintColor::Magenta:
            return "\033[1;35m";
            break;
        case EPrintColor::Cyan:
            return "\033[1;36m";
            break;
        case EPrintColor::Yellow:
            return "\033[1;33m";
            break;
        case EPrintColor::Gray:
            return "\033[1;90m";
            break;
        case EPrintColor::LightRed:
            return "\033[1;91m";
            break;
        case EPrintColor::LightGreen:
            return "\033[1;92m";
            break;
        case EPrintColor::LightBlue:
            return "\033[1;94m";
            break;
        case EPrintColor::LightWhite:
            return "\033[1;97m";
            break;
        case EPrintColor::LightMagenta:
            return "\033[1;95m";
            break;
        case EPrintColor::LightCyan:
            return "\033[1;96m";
            break;
        case EPrintColor::LightYellow:
            return "\033[1;94m";
            break;
        default:
            return "\033[1;37m"; // return White by default
            break;
    }
}
