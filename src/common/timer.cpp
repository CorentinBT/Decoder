#include <ctime>
#include <ratio>

#include "common/common_types.h"
#include "common/timer.h"

namespace Common {

void Timer::Start() {
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_Running = true;
}

void Timer::Stop() {
    m_LastTime = std::chrono::high_resolution_clock::now();
    m_Running = false;
}

void Timer::Update() {
    m_LastTime = std::chrono::high_resolution_clock::now();
}

f64 Timer::GetTimeElapsed() {
    if (!m_Running)
        return std::chrono::duration<double, std::milli>(m_LastTime - m_StartTime).count();

	const auto t = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t - m_StartTime).count();
}

} // Namespace Common
