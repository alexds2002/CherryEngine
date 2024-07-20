#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>
#include <heap_memory_track_component.h>

TRACK_MEMORY_AND_LEAKS()

int main(int argc, char* argv[])
{
    Debug_Log(EPrintColor::Magenta, "Starting Cherry Engine...");
    int* arr = new int[100];
    int* sth = new int(69);
    return EXIT_SUCCESS;
}

