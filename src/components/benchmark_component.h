#pragma once

/*
 * benchmark_component is a class that can benchmark execution times
 */

#include <stack>
#include <chrono>
#include <debug_logger_component.h>

/* can track execution time of code segments */
class BenchMarkExecution
{
public:
    BenchMarkExecution() noexcept;
    explicit BenchMarkExecution(EPrintColor color) noexcept;
    ~BenchMarkExecution() noexcept;
    void Save_Time_Point() noexcept;
    std::chrono::milliseconds Get_Time_From_Last_Point() const noexcept;
    void Print_Time_From_Last_Point() const noexcept;
    std::chrono::milliseconds Pop_Last_Point() noexcept;
    EPrintColor Get_Print_Color() const noexcept;
    void Change_Print_Color(const EPrintColor color) noexcept;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_begin_time;
    /* used for timing different segments, since it is a stack you can add and pop(save a time_point and pop a time_point then print the diff) */
    std::stack<std::chrono::time_point<std::chrono::steady_clock>> m_time_segments;
    /* color that will be shown while benchmarking */
    EPrintColor m_color;
};

/**
 * @brief The first time point is the construction time
 */
inline BenchMarkExecution::BenchMarkExecution() noexcept : m_color(EPrintColor::LightRed)
{
    m_begin_time = std::chrono::steady_clock::now();
}

/**
 * @brief The first time point is the construction time
 */
inline BenchMarkExecution::BenchMarkExecution(EPrintColor _color) noexcept : m_color(_color)
{
    m_begin_time = std::chrono::steady_clock::now();
}

inline BenchMarkExecution::~BenchMarkExecution() noexcept
{
}

/**
 * @brief Save the current time point
 *
 * @return void time passed from last time point
 */
inline void BenchMarkExecution::Save_Time_Point() noexcept
{
    m_time_segments.emplace(std::chrono::steady_clock::now());
}

/**
 * @brief Get the time from the last timed point, the cunstruction time is the first time point
 *
 * Simply returns the time from the last time point
 *
 * @return std::chrono::milliseconds time passed from last time point
 */
inline std::chrono::milliseconds BenchMarkExecution::Get_Time_From_Last_Point() const noexcept
{
    auto end_time = std::chrono::steady_clock::now();
    auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_time_segments.top());
    return time_passed;
}

/**
 * @brief Get the time from the last timed point, the cunstruction time is the first time point
 *
 * Simply returns the time from the last time point
 *
 * @return void
 */
inline void BenchMarkExecution::Print_Time_From_Last_Point() const noexcept
{
    auto end_time = std::chrono::steady_clock::now();
    auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_time_segments.top());
    Debug_Log(m_color, "Time passed is: ", time_passed.count(), "ms");
}

/**
 * @brief Pop the last time point and return the time passed.
 *
 * @return std::chrono::milliseconds: time passed
 */
inline std::chrono::milliseconds BenchMarkExecution::Pop_Last_Point() noexcept
{
    auto end_time = std::chrono::steady_clock::now();
    auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_time_segments.top());
    m_time_segments.pop();
    return time_passed;
}

inline EPrintColor BenchMarkExecution::Get_Print_Color() const noexcept
{
    return m_color;
}

inline void BenchMarkExecution::Change_Print_Color(const EPrintColor color) noexcept
{
    m_color = color;
}
