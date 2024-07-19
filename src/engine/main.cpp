#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <benchmark_component.h>
#include "thread_pool/thread_pool.h"

void TestFunction()
{
    int a = 0;
    int i = 0;
    for(i = 0; i < 100'000; ++i)
    {
        a += i;
    }
    a = i;
}

struct Test
{
    int64_t test;
};

void dummpy()
{
    int64_t test11;
    printStackPointer();
}

int main(int argc, char* argv[])
{
    CHERRY_ASSERT(1 == 2, "HELLO");
    for(int i = 1; i < 17; ++i)
    {
        BenchMark ut;
        ThreadPool thread_pool(i);
        for(int i = 0; i < 10000; ++i)
        {
            thread_pool.Add_Task(TestFunction);
        }
    }
    printStackPointer();
    dummpy();
    printStackPointer();
    return EXIT_SUCCESS;
}

