#pragma once

#include <array>
#include <cstdint>

#include <boost/numeric/ublas/matrix.hpp>

using u8 = std::uint8_t;   ///< 8-bit unsigned byte
using u16 = std::uint16_t; ///< 16-bit unsigned short
using u32 = std::uint32_t; ///< 32-bit unsigned word
using u64 = std::uint64_t; ///< 64-bit unsigned int

using s8 = std::int8_t;   ///< 8-bit signed byte
using s16 = std::int16_t; ///< 16-bit signed short
using s32 = std::int32_t; ///< 32-bit signed word
using s64 = std::int64_t; ///< 64-bit signed int

using f32 = float;  ///< 32-bit floating point
using f64 = double; ///< 64-bit floating point

template <typename T>
using Vector = boost::numeric::ublas::vector<T>;
template <typename T>
using Matrix = boost::numeric::ublas::matrix<T>;

// An inheritable class to disallow the copy constructor and operator= functions
class NonCopyable {
protected:
    constexpr NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};