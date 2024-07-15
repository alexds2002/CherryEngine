#include <debug_mode_definitions.h>
#include <debug_logger_component.h>
#include <unit_test_component.h>
#include "thread_pool/thread_pool.h"
#include "thread_pool/test/thread_pool_simple.h"
#include <unistd.h>

void TestFunction()
{
}

int main(int argc, char* argv[])
{
    {
        UnitTest ut;
        for(int i = 0; i < 1000; ++i)
        {
            ThreadPool thread_pool(std::thread::hardware_concurrency());
            for(int i = 0; i < 1000; ++i)
            {
                thread_pool.Add_Task(TestFunction);
            }
        }
    }
    {
        UnitTest ut;
        for(int i = 0; i < 1000; ++i)
        {
            ThreadPoolSimple thread_pool(std::thread::hardware_concurrency());
            for(int i = 0; i < 1000; ++i)
            {
                thread_pool.Add_Task(TestFunction);
            }
        }
    }
    return 0;
}

