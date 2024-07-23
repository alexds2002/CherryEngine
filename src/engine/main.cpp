#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>
#include <heap_memory_track_component.h>
#include <stack_memory_track_component.h>

#ifdef DEBUG_MODE
TRACK_HEAP_AND_LEAKS() // start tracking the heap
//StackMemoryTracker gstack_memory_tracker; // create a stack memory tracker
#endif /* DEBUG_MODE */

int main(int argc, char* argv[])
{
    Debug_Log(EPrintColor::Magenta, "Starting Cherry Engine...");
    PRINT_HEAP_MEMORY()
    return EXIT_SUCCESS;
}

