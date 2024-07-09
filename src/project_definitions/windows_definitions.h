#pragma once

/*
 * This header contains definitions needed for WINDOWS systems
 * (only when _WIN32 is defined)
 * They should not be used in Unix specific code
 */

#ifdef _WIN32

#include <windows.h>
/* a hack to get the windows version */
#define _WIN32_VERSION *(ULONG*)(((BYTE*)0x7FFE0000) + 0x26c) // major version offset

#endif
