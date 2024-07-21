#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>
#include <memory_track_component.h>

#ifdef DEBUG_MODE
TRACK_LEAKS_AND_MEMORY()
//TRACK_MEMORY_ONLY()
#endif /* DEBUG_MODE */

int main(int argc, char* argv[])
{
    //StackMemoryTracker gstack_memory_tracker;
    Debug_Log(EPrintColor::Magenta, "Starting Cherry Engine...");
    //int* arr = new int[100];
    //int* sth = new int(69);
    PRINT_HEAP_MEMORY()
    //gstack_memory_tracker.Print_Current_Stack_Size();
    //delete[] arr;
    //delete sth;
    return EXIT_SUCCESS;
}

