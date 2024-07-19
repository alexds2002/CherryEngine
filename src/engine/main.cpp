#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>

int main(int argc, char* argv[])
{
    Debug_Log(EPrintColor::Magenta, "Starting Cherry Engine...");
    return EXIT_SUCCESS;
}

