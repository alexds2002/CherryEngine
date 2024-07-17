#include <debug_mode_definitions.h>
#include <debug_logger_component.h>
#include <debug_assert_component.h>
#include <unit_test_component.h>
#include "thread_pool/thread_pool.h"
#include "thread_pool/test/thread_pool_simple.h"

void TestFunction()
{
    int a = 0;
    int b = 0;

    for (b = 0; b < 1000000; ++b)
    {
        a = b;
    }
    for (b = 0; b < 1000000; ++b)
    {
        a = b;
    }
    for (b = 0; b < 1000000; ++b)
    {
        a = b;
    }
    for (b = 0; b < 100000; ++b)
    {
        a = b;
    }
    for (b = 0; b < 1000000; ++b)
    {
        a = b;
    }
    a = ++b;
}

int main(int argc, char* argv[])
{
    {
        UnitTest ut;
        for(int i = 0; i < 1000; ++i)
        {
            ThreadPool thread_pool(4);
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
            ThreadPoolSimple thread_pool(4);
            for(int i = 0; i < 1000; ++i)
            {
                thread_pool.Add_Task(TestFunction);
            }
        }
    }

    {
        UnitTest ut;
        ThreadPool thread_pool(2);
        for(int i = 0; i < 1000000; ++i)
        {
            thread_pool.Add_Task(TestFunction);
        }
    }
    {
        UnitTest ut;
        ThreadPoolSimple thread_pool(2);
        for(int i = 0; i < 1000000; ++i)
        {
            thread_pool.Add_Task(TestFunction);
        }
    }
    {
        UnitTest ut;
        ThreadPool thread_pool(1);
        for(int i = 0; i < 1000000; ++i)
        {
            thread_pool.Add_Task(TestFunction);
        }
    }
    {
        UnitTest ut;
        ThreadPoolSimple thread_pool(1);
        for(int i = 0; i < 1000000; ++i)
        {
            thread_pool.Add_Task(TestFunction);
        }
    }
    return 0;
}

