#pragma once

#include <chrono>
#include <debug_logger_component.h>

class BenchMark
{
public:
    BenchMark() noexcept;
    explicit BenchMark(EDebugColors color) noexcept;
    ~BenchMark() noexcept;
private:
    std::chrono::time_point<std::chrono::steady_clock> m_begin_time;
    EDebugColors m_color;
};

inline BenchMark::BenchMark() noexcept : m_color(EDebugColors::LightRed)
{
    m_begin_time = std::chrono::steady_clock::now();
}

inline BenchMark::BenchMark(EDebugColors _color) noexcept : m_color(_color)
{
    m_begin_time = std::chrono::steady_clock::now();
}

inline BenchMark::~BenchMark() noexcept
{
    auto end_time = std::chrono::steady_clock::now();
    auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_begin_time);
    Debug_Log(m_color, "Time passed is: ", time_passed.count(), "ms");
}
