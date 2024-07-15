#pragma once

#include <chrono>
#include <debug_logger_component.h>

class UnitTest
{
public:
    UnitTest() noexcept;
    ~UnitTest() noexcept;
private:
    std::chrono::time_point<std::chrono::steady_clock> m_begin_time;
};

inline UnitTest::UnitTest() noexcept
{
    m_begin_time = std::chrono::steady_clock::now();
}

inline UnitTest::~UnitTest() noexcept
{
    auto end_time = std::chrono::steady_clock::now();
    auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_begin_time);
    Debug_Log(EDebugColors::LightRed, "Time passed is: ", time_passed.count(), "ms");
}
