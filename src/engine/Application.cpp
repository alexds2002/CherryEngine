#include "Application.h"
#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>
#include <heap_memory_track_component.h>
#include <stack_memory_track_component.h>
#include <project_definitions.h>

bool Application::Init()
{
    Init_Categories();
    Disable_Category(ELogCategory::Default);
    Enable_Category(ELogCategory::Default);
    Debug_Log(ELogCategory::Default, EPrintColor::Magenta, "Starting Cherry Engine...");
    return true; /* success */
}
