#pragma once

#include <condition_variable>
#include <type_traits>
#include <functional>
#include <cstdint>
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

class ThreadPool
{
public:
    ThreadPool(uint32_t _number_of_threads) noexcept;
    ~ThreadPool();

    /**
     * @brief Adds a task to the task queue
     *
     * @param  Callable&&: taks to be executed
     * @param  Args&&: arguments of the Callable
     *
     * Example usage:
     *
     * @return void
     */
    template<typename Callable, typename... Args>
    auto Add_Task(Callable&& func, Args... args) -> std::future<typename std::result_of<Callable(Args...)>::type>;

    /* Get the max number of worker threads on this system
     * (possibly std::thread::hardware_concurrency */
    uint32_t Get_Number_Of_Threads() const noexcept;
    /* Number of threads that are currently working */
    uint32_t Busy_Threads() const noexcept;
    /* Get the number of tasks on the queue */
    std::size_t Number_Of_Tasks() const noexcept;

private:
    /* lock shared data */
    mutable std::mutex m_mutex;
    /* used to notify a thread in case it is waiting(this may happen outside of your program) */
    std::condition_variable m_condition_var;
    /* m_workers size should be based on the system it is running(maybe std::thread::hardware_concurrency) */
    std::vector<std::thread> m_workers;
    /* a queue of tasks where AddTask pushes new tasks and the executor removes tasks as soon as there is a free thread */
    std::queue<std::function<void()>> m_tasks;

    /* number of threads that are currenty working */
    uint32_t m_busy_threads{0};
    /* number of threads based on std::thread::hardware_concurrency */
    uint32_t m_threads_count{0};
    /* if there is a force quit you can still finish your current execution */
    bool m_force_stop{false};
};

/* contains the function definitions */
#include "thread_pool.hpp"

