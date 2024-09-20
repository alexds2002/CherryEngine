#include "Application.h"
#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>
#include <heap_memory_track_component.h>
#include <stack_memory_track_component.h>
#include <project_definitions.h>
#include <string_algorithms.h>
#include <array_algorithms.h>
#include <linked_list_algorithms.h>
#include "../data_structures/stack.hpp"

bool Application::Init()
{
    Init_Categories();
    Debug_Log(ELogCategory::Default, EPrintColor::Magenta, "Starting Cherry Engine...");

    return true; /* success */
}

void Application::Update(double deltaTime)
{
    while(true)
    {
    }
}
