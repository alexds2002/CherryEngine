#include "thread_pool.h"
#include <debug_logger_component.h>

ThreadPool::ThreadPool() : m_threads_count{std::thread::hardware_concurrency()}
{
    /* if hardware_concurrency fails it returns 0 */
    if(std::thread::hardware_concurrency() == 0)
    {
        m_threads_count = 1;
    }
}

template<typename Callable>
void ThreadPool::Add_Task(Callable&& func) noexcept
{
    {
        /* lock shrared data */
        std::unique_lock<std::mutex> lock(m_mutex);
        m_tasks.emplace(func);
    }
    /* wake up a thread if its waiting(should not be locked, can create a "hurry up and wait" scenario) */
    m_condition_var.notify_one();
}

uint32_t ThreadPool::Get_Number_Of_Threads() const noexcept
{
    return m_threads_count;
}

uint32_t ThreadPool::Busy_Threads() const noexcept
{
    return m_busy_threads;
}
