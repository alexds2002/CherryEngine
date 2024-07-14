#include "thread_pool.h"
#include <debug_logger_component.h>

ThreadPool::ThreadPool(uint32_t _number_of_threads) noexcept : m_threads_count(_number_of_threads),
                                                               m_force_stop(false)
{
    /* if hardware_concurrency fails it returns 0 or if an invalid value is passed */
    if(_number_of_threads == 0) { m_threads_count = 1; }
    for(size_t i = 0; i < m_threads_count; ++i)
    {
        m_workers.empace_back([this]{
                    while(true)
                    {
                        std::function<void()> task;
                        {
                            /* lock critical code */
                            std::unique_lock<std::mutex> lock(this->m_mutex);
                            m_condition_var.wait(lock,
                                    [this]
                                    {
                                        return this->m_force_stop || !this->m_tasks.empty();
                                    }
                            if(this->m_force_stop || this->m_tasks.empty())
                            {
                                return;
                            }
                            task = std::move(this->m_tasks.front());
                            this->m_tasks.pop();
                        }
                        task();
                    }});
    }
}
ThreadPool::~ThreadPool()
{
    m_force_stop = true;
    m_condition_var.notify_all();
    for(auto& thread : m_thread_pool)
    {
        thread.join();
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
