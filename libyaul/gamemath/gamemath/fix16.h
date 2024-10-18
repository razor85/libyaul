/*
 * Copyright (c) Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

/*-
 * Copyright (c) Authors of libfixmath
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _YAUL_GAMEMATH_FIX16_H_
#define _YAUL_GAMEMATH_FIX16_H_

#include <sys/cdefs.h>

#include <stdbool.h>
#include <stdint.h>

#include <gamemath/defs.h>

/// @defgroup MATH_FIX16 Fix16
/// @ingroup MATH

/// @defgroup MATH_FIX16_VECTOR Fix16 Vector
/// @ingroup MATH

/// @defgroup MATH_FIX16_MATRIX Fix16 Matrix
/// @ingroup MATH

/// @defgroup MATH_FIX16_PLANES Fix16 Planes
/// @ingroup MATH

/// @defgroup MATH_FIX16_TRIG Fix16 Trigonometry
/// @ingroup MATH

/// @addtogroup MATH_FIX16
/// @{

/// @brief Macro for defininge @p fix16_t constant values.
///
/// @note The argument is evaluated multiple times, and also otherwise you
/// should only use this for constant values. For runtime-conversions, use the
/// inlined functions below.
///
/// @param x The constant value.
#define FIX16(x) ((fix16_t)(((x) >= 0)                                         \
    ? ((double)(x) * 65536.0 + 0.5)                                            \
    : ((double)(x) * 65536.0 - 0.5)))

/// @brief Fixed point Q16.16.
typedef int32_t fix16_t;

/// @brief Not yet documented.
///
/// @param a Operand.
/// @param b Operand.
///
/// @returns The value.
__BEGIN_ASM
static inline int32_t __always_inline
fix16_low_mul(fix16_t a, fix16_t b)
{
    __register int32_t out;

    __declare_asm("\tdmuls.l %[a], %[b]\n"
                  "\tsts macl, %[out]\n"
                  /* Output */
                  : [out] "=&r" (out)
                  /* Input */
                  : [a] "r" (a),
                    [b] "r" (b)
                  : "macl");

    return out;
}
__END_ASM

/// @brief Not yet documented.
///
/// @param a Operand.
/// @param b Operand.
///
/// @returns The value.
__BEGIN_ASM
static inline int32_t __always_inline
fix16_high_mul(fix16_t a, fix16_t b)
{
    __register int16_t out;

    __declare_asm("\tdmuls.l %[a], %[b]\n"
                  "\tsts mach, %[out]\n"
                  /* Output */
                  : [out] "=&r" (out)
                  /* Input */
                  : [a] "r" (a),
                    [b] "r" (b)
                  : "mach");

    return out;
}
__END_ASM

/// @brief Not yet documented.
///
/// @param a Operand.
/// @param b Operand.
///
/// @returns The value.
__BEGIN_ASM
static inline fix16_t __always_inline
fix16_mul(fix16_t a, fix16_t b)
{
    __register int32_t mach;
    __register fix16_t out;

    __declare_asm("\tdmuls.l %[a], %[b]\n"
                  "\tsts mach, %[mach]\n"
                  "\tsts macl, %[out]\n"
                  "\txtrct %[mach], %[out]\n"
                  /* Output */
                  : [mach] "=&r" (mach),
                    [out] "=&r" (out)
                  /* Input */
                  : [a] "r" (a),
                    [b] "r" (b)
                  : "mach", "macl");

    return out;
}
__END_ASM

/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline fix16_t __always_inline
fix16_int32_from(int32_t value)
{
    return (value * FIX16(1.0));
}

/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline int32_t __always_inline
fix16_int32_to(fix16_t value)
{
    return (value >> 16);
}

/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline int32_t __always_inline
fix16_round_int32_to(fix16_t value)
{
    if (value >= 0) {
        return ((value + (FIX16(1.0) / 2)) / FIX16(1.0));
    }

    return ((value - (FIX16(1.0) / 2)) / FIX16(1.0));
}

/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline int32_t __always_inline
fix16_integral(fix16_t value)
{
    return (value & 0xFFFF0000UL);
}

/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline int32_t __always_inline
fix16_fractional(fix16_t value)
{
    return (value & 0x0000FFFFUL);
}

// TODO: Does not compile for C++
/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline fix16_t __always_inline
fix16_floor(fix16_t value)
{
    return (value & 0xFFFF0000);
}

// TODO: Does not compile for C++
/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
static inline fix16_t __always_inline
fix16_ceil(fix16_t value)
{
    return ((value & 0xFFFF0000UL) + ((value & 0x0000FFFFUL) ? FIX16(1.0) : 0));
}

__BEGIN_DECLS

/// @brief Not yet documented.
///
/// @param a        Operand.
/// @param b        Operand.
/// @param sum[out] Sum.
///
/// @returns If overflow occurred.
extern bool fix16_overflow_add(fix16_t a, fix16_t b, fix16_t *sum);

/// @brief Not yet documented.
///
/// @param a         Operand.
/// @param b         Operand.
/// @param diff[out] Sum.
///
/// @returns If overflow occurred.
extern bool fix16_overflow_sub(fix16_t a, fix16_t b, fix16_t *diff);

/// @brief Not yet documented.
///
/// @param dividend Operand.
/// @param divisor  Operand.
///
/// @returns The value.
extern fix16_t fix16_div(fix16_t dividend, fix16_t divisor);

/// @brief Not yet documented.
///
/// @param a Operand.
/// @param b Operand.
/// @param t Operand.
///
/// @returns The value.
extern fix16_t fix16_lerp(fix16_t a, fix16_t b, fix16_t t);

/// @brief Not yet documented.
///
/// @param a Operand.
/// @param b Operand.
/// @param t Operand.
///
/// @returns The value.
extern fix16_t fix16_lerp8(fix16_t a, fix16_t b, const uint8_t t);

/// @brief Not yet documented.
///
/// @param value Operand.
///
/// @returns The value.
extern fix16_t fix16_sqrt(fix16_t value);

/// @brief Not yet documented.
///
/// @param      value    Not yet documented.
/// @param[out] buffer   Not yet documented.
/// @param      decimals Not yet documented.
///
/// @returns The string length, not counting the `NUL` character.
extern size_t fix16_str(fix16_t value, char *buffer, int32_t decimals);

__END_DECLS

#if defined(__cplusplus)

namespace yaul {

struct angle;

/// @brief Fixed point Q16.16.
struct __packed __aligned(4) fix16
{
    fix16_t value;

    fix16() = default;
    fix16(const fix16&) = default;
    fix16(fix16&&) = default;

    constexpr explicit fix16(fix16_t v)
        : value(v)
    {
    }

    fix16 &operator=(const fix16 &) = default;
    fix16 &operator=(fix16 &&) = default;

    // For dealing with C
    constexpr explicit operator fix16_t() const
    {
        return value;
    }

    constexpr fix16 operator+(fix16 other) const
    {
        return fix16 { value + other.value };
    }

    constexpr fix16 operator-(fix16 other) const
    {
        return fix16 { value - other.value };
    }

    constexpr fix16 operator-() const
    {
        return fix16 { -value };
    }

    fix16 operator*(fix16 other) const
    {
        return fix16 { fix16_mul(value, other.value) };
    }

    fix16 operator/(fix16 other) const
    {
        return fix16 { fix16_div(value, other.value) };
    }

    fix16 operator*(fix16_t other) const
    {
        return fix16 { fix16_mul(value, other) };
    }

    fix16 operator/(fix16_t other) const
    {
        return fix16 { fix16_div(value, other) };
    }

    constexpr fix16 operator>>(int32_t i) const
    {
        return fix16 { value >> i };
    }

    constexpr fix16 operator<<(int32_t i) const
    {
        return fix16 { value << i };
    }

    fix16 &operator+=(fix16 rhs)
    {
        value += rhs.value;
        return *this;
    }

    fix16 &operator-=(fix16 rhs)
    {
        value -= rhs.value;
        return *this;
    }

    fix16 &operator*=(fix16 rhs)
    {
        value = fix16_mul(value, rhs.value);
        return *this;
    }

    fix16 &operator/=(fix16 rhs)
    {
        value = fix16_div(value, rhs.value);
        return *this;
    }

    fix16 &operator*=(fix16_t rhs)
    {
        value = fix16_mul(value, rhs);
        return *this;
    }

    fix16 &operator/=(fix16_t rhs)
    {
        value = fix16_div(value, rhs);
        return *this;
    }

    fix16 &operator>>=(int32_t i)
    {
        value >>= i;
        return *this;
    }

    fix16 &operator<<=(int32_t i)
    {
        value <<= i;
        return *this;
    }

    bool operator<(fix16 other) const
    {
        return value < other.value;
    }

    bool operator>(fix16 other) const
    {
        return value > other.value;
    }

    bool operator<=(fix16 other) const
    {
        return value <= other.value;
    }

    bool operator>=(fix16 other) const
    {
        return value >= other.value;
    }

    bool operator==(fix16 other) const
    {
        return value == other.value;
    }

    bool operator<(fix16_t other) const
    {
        return value < other;
    }

    bool operator>(fix16_t other) const
    {
        return value > other;
    }

    bool operator<=(fix16_t other) const
    {
        return value <= other;
    }

    bool operator>=(fix16_t other) const
    {
        return value >= other;
    }

    bool operator==(fix16_t other) const
    {
        return value == other;
    }

    void to_minimum_value()
    {
        value = INT32_MIN;
    }

    void to_maximum_value()
    {
        value = INT32_MAX;
    }

    void negate()
    {
        value = -value;
    }

    fix16 negated() const
    {
        return fix16 { -value };
    }

    fix16 abs() const
    {
        return fix16 { ::abs(value) };
    }

    fix16 sqrt() const
    {
        return fix16 { fix16_sqrt(value) };
    }

    fix16 deg_to_rad() const
    {
        constexpr fix16_t scale { FIX16(M_PI / 180.0) };
        return fix16 { fix16_mul(value, scale) };
    }

    fix16 rad_to_deg() const
    {
        constexpr fix16_t scale { FIX16(180.0 / M_PI) };
        return fix16 { fix16_mul(value, scale) };
    }

    angle rad_to_angle() const;

    angle deg_to_angle() const;

    fix16 approximate_distance(fix16 other) const
    {
        const fix16 dx { abs() };
        const fix16 dy { other.abs() };
        if (dx < dy)
            return dx + dy - (dx >> 1);
        else
            return dx + dy - (dy >> 1);
    }

    int32_t mul_to_int32(fix16 other) const
    {
        return static_cast<int32_t>(
            (static_cast<int64_t>(value) * static_cast<int64_t>(other.value)) >>
            32);
    }

    constexpr int16_t fractional() const
    {
        return (value & 0x0000FFFF);
    }

    bool is_near_zero(fix16 epsilon) const
    {
        return ::abs(value) <= epsilon.value;
    }

    bool is_near_zero(fix16_t epsilon) const
    {
        return ::abs(value) <= epsilon;
    }

    bool is_near(fix16 other, fix16 epsilon) const
    {
        return ::abs(value - other.value) <= epsilon.value;
    }

    bool is_near(fix16_t other, fix16_t epsilon) const
    {
        return ::abs(value - other) <= epsilon;
    }

    constexpr bool is_negative() const
    {
        return (value < 0);
    }

    constexpr bool is_positive() const
    {
        return (value >= 0);
    }

    constexpr int32_t to_int() const
    {
        return (value >> 16);
    }

    size_t to_string(char *buffer, int32_t decimals) const
    {
        return fix16_str(value, buffer, decimals);
    }

    static constexpr fix16 from_int(int32_t i)
    {
        return fix16 { i * FIX16(1.0) };
    }

    static constexpr fix16 from_double(double value)
    {
        return fix16 { FIX16(value) };
    }

    static void start_divu_1_over_value(fix16 v);

    static void start_divu(fix16 num, fix16 denom);

    static fix16 get_divu_quotient();

    static const fix16 Zero;

    static const fix16 One;

    static const fix16 Minus_one;
};
    
inline const fix16 fix16::Zero{ fix16::from_double(0.0) };

inline const fix16 fix16::One{ fix16::from_double(1.0) };

inline const fix16 fix16::Minus_one{ fix16::from_double(-1.0) };

static_assert(sizeof(fix16) == sizeof(::fix16_t));

} // namespace yaul

constexpr yaul::fix16
operator"" _fp(long double v)
{
    return yaul::fix16::from_double(v);
}

#endif /* __cplusplus */

/// @}

#endif /* !_YAUL_GAMEMATH_FIX16_H_ */
