#pragma once

#include <chrono>
#include <iostream>
#include <type_traits>

#include "common/common_types.h"

namespace Common {

class Timer {
public:
    Timer() = default;

    void Start();
    void Stop();
    void Update();

    f64 GetTimeElapsed();

private:
    std::chrono::high_resolution_clock::time_point m_LastTime;
    std::chrono::high_resolution_clock::time_point m_StartTime;
    bool m_Running = false;
};

// clang-format off

template <class Fn, class... Args>
auto TimeFunction(Fn fn, Args && ... args) -> typename std::enable_if< 
    // First template argument is the enable condition
    !std::is_same< 
            decltype(fn( std::forward<Args>(args) ... )), 
            void >::value,
    // Second argument is the actual return type
    std::pair<f64, decltype(fn(std::forward<Args>(args)...))> >::type
{
    Timer timer;

    timer.Start();
    const auto res = std::forward<Fn>(fn)(std::forward<Args>(args)...);
    timer.Stop();

	return {timer.GetTimeElapsed(), res};
}

template <class Fn, class... Args>
auto TimeFunction(Fn fn, Args &&... args) -> typename std::enable_if< 
    std::is_same< 
            decltype(fn(std::forward<Args>(args) ... )), 
            void >::value,
    f64>::type
{
    Timer timer;

    timer.Start();
    std::forward<Fn>(fn)(std::forward<Args>(args)...);
    timer.Stop();

	return timer.GetTimeElapsed();
}

// clang-format on

} // Namespace Common
