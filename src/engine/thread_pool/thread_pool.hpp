#pragma once

#include "thread_pool.h"
#include <memory>

inline ThreadPool::ThreadPool(uint32_t _number_of_threads) noexcept : m_threads_count(_number_of_threads),
                                                               m_force_stop(false)
{
    /* if hardware_concurrency fails it returns 0 or if an invalid value is passed */
    if(_number_of_threads == 0) { m_threads_count = 1; }
    for(size_t i = 0; i < m_threads_count; ++i)
    {
        m_workers.emplace_back([this]{
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
                            });
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
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_force_stop = true;
    }
    m_condition_var.notify_all();
    for(auto& worker : m_workers)
    {
        worker.join();
    }
}

template<typename Callable, typename... Args>
auto ThreadPool::Add_Task(Callable&& func, Args... args) ->
                std::future<typename std::result_of<Callable(Args...)>::type>
{
    using return_type = typename std::result_of<Callable(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Callable>(func), std::forward<Args>(args)...));
    std::future<return_type> result = task->get_future();
    {
        /* lock shrared data */
        std::unique_lock<std::mutex> lock(m_mutex);
        /* dont allow task adding after force stop */
        if(m_force_stop)
        {
            throw std::runtime_error("Trying to add taks after forced stop!");
        }
        m_tasks.emplace([task](){ (*task)(); });
    }
    /* wake up a thread if its waiting(should not be locked, can create a "hurry up and wait" scenario) */
    m_condition_var.notify_one();
    return result;
}

inline uint32_t ThreadPool::Get_Number_Of_Threads() const noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_threads_count;
}

inline uint32_t ThreadPool::Busy_Threads() const noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_busy_threads;
}

inline std::size_t ThreadPool::Number_Of_Tasks() const noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_tasks.size();
}
