/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Leitao <abra185@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_FIX16_VEC2_H_
#define _YAUL_GAMEMATH_FIX16_VEC2_H_

#include <assert.h>
#include <gamemath/fix16.h>

/// @addtogroup MATH_FIX16_VECTOR
/// @defgroup MATH_FIX16_VEC2 2-vector
/// @ingroup MATH_FIX16_VECTOR
/// @{

/// @brief Not yet documented.
///
/// @param x Not yet documented.
/// @param y Not yet documented.
#define FIX16_VEC2_INITIALIZER(x, y)                                           \
{                                                                              \
        FIX16(x),                                                              \
        FIX16(y)                                                               \
}

/// @brief Not yet documented.
///
/// @param x Not yet documented.
/// @param y Not yet documented.
#define FIX16_VEC2(x, y)                                                       \
((fix16_vec2_t){                                                               \
        FIX16(x),                                                              \
        FIX16(y)                                                               \
})

/// @param x Not yet documented.
typedef struct fix16_vec2 {
    /// @param x Not yet documented.
    fix16_t x;
    /// @param x Not yet documented.
    fix16_t y;
} __packed __aligned(4) fix16_vec2_t;

/// @brief Not yet documented.
///
/// @param result Not yet documented.
static inline void __always_inline
fix16_vec2_zero(fix16_vec2_t *result)
{
    result->x = FIX16(0.0);
    result->y = FIX16(0.0);
}

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec2_dup(const fix16_vec2_t * __restrict v0,
  fix16_vec2_t * __restrict result)
{
    result->x = v0->x;
    result->y = v0->y;
}

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param      v1     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec2_add(const fix16_vec2_t * __restrict v0,
  const fix16_vec2_t * __restrict v1, fix16_vec2_t * __restrict result)
{
    result->x = v0->x + v1->x;
    result->y = v0->y + v1->y;
}

/// @brief Not yet documented.
///
/// @param      v1     Not yet documented.
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec2_sub(const fix16_vec2_t * __restrict v1,
  const fix16_vec2_t * __restrict v0, fix16_vec2_t * __restrict result)
{
    result->x = v1->x - v0->x;
    result->y = v1->y - v0->y;
}

/// @brief Not yet documented.
///
/// @param      scalar Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec2_scale(fix16_t scalar, fix16_vec2_t *result)
{
    result->x = fix16_mul(scalar, result->x);
    result->y = fix16_mul(scalar, result->y);
}

/// @brief Not yet documented.
///
/// @param      scalar Not yet documented.
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec2_scaled(fix16_t scalar, const fix16_vec2_t * __restrict v0,
  fix16_vec2_t * __restrict result)
{
    result->x = fix16_mul(scalar, v0->x);
    result->y = fix16_mul(scalar, v0->y);
}

/// @brief Not yet documented.
///
/// @param a Not yet documented.
/// @param b Not yet documented.
///
/// @returns The value.
__BEGIN_ASM
static inline fix16_t __always_inline
fix16_vec2_inline_dot(const fix16_vec2_t *a, const fix16_vec2_t *b)
{
    __register uint32_t aux0;
    __register uint32_t aux1;

    __declare_asm("\tclrmac\n"
                  "\tmac.l @%[a]+, @%[b]+\n"
                  "\tmac.l @%[a]+, @%[b]+\n"
                  "\tsts mach, %[aux0]\n"
                  "\tsts macl, %[aux1]\n"
                  "\txtrct %[aux0], %[aux1]\n"
                  : [a] "+r" (a),
                    [b] "+r" (b),
                    [aux0] "=&r" (aux0),
                    [aux1] "=&r" (aux1)
                  : "m" (*a),
                    "m" (*b)
                  : "mach", "macl", "memory");

    return aux1;
}
__END_ASM

__BEGIN_DECLS

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
extern fix16_t fix16_vec2_length(const fix16_vec2_t *v0);

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
extern fix16_t fix16_vec2_sqr_length(const fix16_vec2_t *v0);

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
extern void fix16_vec2_normalize(fix16_vec2_t *v0);

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_vec2_normalized(const fix16_vec2_t * __restrict v0, fix16_vec2_t * __restrict result);

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
/// @param v1 Not yet documented.
///
/// @returns The value.
extern fix16_t fix16_vec2_dot(const fix16_vec2_t *v0, const fix16_vec2_t *v1);

/// @brief Not yet documented.
///
/// @param      v0       Not yet documented.
/// @param[out] buffer   Not yet documented.
/// @param      decimals Not yet documunted.
///
/// @returns The string length, not counting the `NUL` character.
extern size_t fix16_vec2_str(const fix16_vec2_t *v0, char *buffer, int32_t decimals);

__END_DECLS

/// @}

#if defined(__cplusplus)

namespace yaul {

/// @brief Not yet documented.
struct __packed __aligned(4) fix16_vec2
{
    /// @brief Not yet documented.
    fix16 x;
    /// @brief Not yet documented.
    fix16 y;

    fix16_vec2() = default;
    fix16_vec2(fix16_vec2 &&) = default;
    fix16_vec2(const fix16_vec2 &) = default;

    constexpr explicit fix16_vec2(fix16_t x_, fix16_t y_)
        : x { x_ }
        , y { y_ }
    {
    }

    constexpr explicit fix16_vec2(fix16 x_, fix16 y_)
        : x { x_ }
        , y { y_ }
    {
    }

    fix16_vec2 operator>>(int i) const
    {
        return fix16_vec2 { x >> i, y >> i };
    }

    fix16_vec2 operator<<(int i) const
    {
        return fix16_vec2 { x << i, y << i };
    }

    fix16_vec2 &operator=(const fix16_vec2 &other) = default;

    fix16_vec2 &operator=(fix16_vec2 &&other) = default;

    const fix16_vec2 operator+(const fix16_vec2 &other) const
    {
        return fix16_vec2 { x + other.x, y + other.y };
    }

    const fix16_vec2 operator-(const fix16_vec2 &other) const
    {
        return fix16_vec2 { x - other.x, y - other.y };
    }

    const fix16_vec2 operator-() const
    {
        return fix16_vec2 { -x, -y };
    }

    const fix16_vec2 operator*(fix16 scalar) const
    {
        return fix16_vec2 { x * scalar, y * scalar };
    }

    const fix16_vec2 operator*(fix16_t scalar) const
    {
        return fix16_vec2 { x * scalar, y * scalar };
    }

    const fix16_vec2 operator/(const fix16 other) const
    {
        return fix16_vec2 { x / other, y / other };
    }

    const fix16_vec2 operator/(const fix16_t other) const
    {
        return fix16_vec2 { x / other, y / other };
    }

    fix16_vec2 &operator+=(const fix16_vec2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    fix16_vec2 &operator-=(const fix16_vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    fix16_vec2 &operator*=(fix16 value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    fix16_vec2 &operator/=(fix16 value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    bool is_zero() const
    {
        return x == 0 && y == 0;
    }

    bool is_near_zero(const fix16 epsilon = 0.001_fp) const
    {
        return x.is_near_zero(epsilon) && y.is_near_zero(epsilon);
    }

    fix16_vec2_t *as_fix16_vec2_t()
    {
        return reinterpret_cast<fix16_vec2_t *>(this);
    }

    const fix16_vec2_t *as_fix16_vec2_t() const
    {
        return reinterpret_cast<const fix16_vec2_t *>(this);
    }

    void zero()
    {
        x = 0.0_fp;
        y = 0.0_fp;
    }

    fix16 dot(const fix16_vec2 &other) const
    {
        return dot(*this, other);
    }

    fix16 cross(const fix16_vec2 &other) const
    {
        return cross(*this, other);
    }

    fix16 length_squared() const
    {
        return dot(*this, *this);
    }

    fix16 length() const
    {
        return dot(*this, *this).sqrt();
    }

    void start_normalization() const
    {
        fix16::start_divu_1_over_value(length());
    }

    void normalize()
    {
        start_normalization();
        finish_normalization(*this);
    }

    fix16 approximate_distance(const fix16_vec2 &other) const
    {
        const fix16 first { x - other.x };
        const fix16 second { y - other.y };
        return first.approximate_distance(second);
    }

    fix16_vec2 reflect(const fix16_vec2 &normal) const
    {
        return reflect(*this, normal);
    }

    fix16 &operator[](int32_t index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            assert(false);
            return x;
        }
    }

    fix16 operator[](int32_t index) const
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            assert(false);
            return x;
        }
    }

    static void finish_normalization(fix16_vec2 & result)
    {
        const fix16 denom { fix16::get_divu_quotient() };
        result.x *= denom;
        result.y *= denom;
    }

    static fix16 dot(const fix16_vec2 &a, const fix16_vec2 &b)
    {
        return fix16 { fix16_vec2_dot(a.as_fix16_vec2_t(),
            b.as_fix16_vec2_t()) };
    }

    static fix16 cross(const fix16_vec2 &a, const fix16_vec2 &b)
    {
        return fix16 { (a.x * b.y) - (a.y * b.x) };
    }

    static fix16_vec2 reflect(const fix16_vec2 &v, const fix16_vec2 &normal)
    {
        // v - 2 * proj(v, normal)
        const fix16 factor { dot(v, normal).value << 1 };
        const fix16_vec2 proj {
            factor * normal.x,
            factor * normal.y,
        };

        return fix16_vec2 {
            v.x - proj.x,
            v.y - proj.y,
        };
    }

    static constexpr fix16_vec2 from_double(double x, double y)
    {
        return fix16_vec2 {
            fix16::from_double(x),
            fix16::from_double(y),
        };
    }

    static const fix16_vec2 Zero;

    static const fix16_vec2 Unit_x;

    static const fix16_vec2 Unit_y;
};

inline const fix16_vec2 fix16_vec2::Zero { fix16_vec2::from_double(0.0, 0.0) };

inline const fix16_vec2 fix16_vec2::Unit_x { fix16_vec2::from_double(1.0,
    0.0) };

inline const fix16_vec2 fix16_vec2::Unit_y { fix16_vec2::from_double(0.0,
    1.0) };

inline fix16_vec2
operator*(fix16 scalar, const fix16_vec2 &v)
{
    return fix16_vec2 { v.x * scalar, v.y * scalar };
}

static_assert(sizeof(fix16_vec2) == sizeof(::fix16_vec2_t));

} // namespace yaul

#endif /* __cplusplus */

#endif /* !_YAUL_GAMEMATH_FIX16_VEC2_H_ */
