/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Leitao <abra185@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_FIX16_VEC3_H_
#define _YAUL_GAMEMATH_FIX16_VEC3_H_

#include <assert.h>
#include <cpu/divu.h>

#include <gamemath/fix16.h>

/// @addtogroup MATH_FIX16_VECTOR
/// @defgroup MATH_FIX16_VEC3 3-vector
/// @ingroup MATH_FIX16_VECTOR
/// @{

/// @brief Not yet documented.
///
/// @param x Not yet documented.
/// @param y Not yet documented.
/// @param z Not yet documented.
#define FIX16_VEC3_INITIALIZER(x, y, z)                                        \
{                                                                              \
    FIX16(x),                                                                  \
    FIX16(y),                                                                  \
    FIX16(z)                                                                   \
}                                                                              \

/// @brief Not yet documented.
///
/// @param x Not yet documented.
/// @param y Not yet documented.
/// @param z Not yet documented.
#define FIX16_VEC3(x, y, z)                                                    \
((fix16_vec3_t){                                                               \
    FIX16(x),                                                                  \
    FIX16(y),                                                                  \
    FIX16(z)                                                                   \
})

/// @brief Not yet documented.
typedef struct fix16_vec3 {
    /// @brief Not yet documented.
    fix16_t x;
    /// @brief Not yet documented.
    fix16_t y;
    /// @brief Not yet documented.
    fix16_t z;
} __packed __aligned(4) fix16_vec3_t;

/// @brief Not yet documented.
///
/// @param result Not yet documented.
static inline void __always_inline
fix16_vec3_zero(fix16_vec3_t *result)
{
    result->x = FIX16(0.0);
    result->y = FIX16(0.0);
    result->z = FIX16(0.0);
}

/// @brief Not yet documented.
///
/// @param[out] result Not yet documented.
/// @param      x      Not yet documented.
/// @param      y      Not yet documented.
/// @param      z      Not yet documented.
static inline void __always_inline
fix16_vec3_set(fix16_t x, fix16_t y, fix16_t z, fix16_vec3_t *result)
{
    result->x = x;
    result->y = y;
    result->z = z;
}

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec3_dup(const fix16_vec3_t * __restrict v0,
  fix16_vec3_t * __restrict result)
{
    result->x = v0->x;
    result->y = v0->y;
    result->z = v0->z;
}

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param      v1     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec3_add(const fix16_vec3_t * __restrict v0,
  const fix16_vec3_t * __restrict v1, fix16_vec3_t * __restrict result)
{
    result->x = v0->x + v1->x;
    result->y = v0->y + v1->y;
    result->z = v0->z + v1->z;
}

/// @brief Not yet documented.
///
/// @param      v1     Not yet documented.
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec3_sub(const fix16_vec3_t * __restrict v1,
  const fix16_vec3_t * __restrict const v0, fix16_vec3_t * __restrict const result)
{
    result->x = v1->x - v0->x;
    result->y = v1->y - v0->y;
    result->z = v1->z - v0->z;
}

/// @brief Not yet documented.
///
/// @param      scalar Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec3_scale(fix16_t scalar, fix16_vec3_t *result)
{
    result->x = fix16_mul(scalar, result->x);
    result->y = fix16_mul(scalar, result->y);
    result->z = fix16_mul(scalar, result->z);
}

/// @brief Not yet documented.
///
/// @param      scalar Not yet documented.
/// @param      v      Not yet documented.
/// @param[out] result Not yet documented.
static inline void __always_inline
fix16_vec3_scaled(fix16_t scalar, const fix16_vec3_t *v,
  fix16_vec3_t *result)
{
    result->x = fix16_mul(scalar, v->x);
    result->y = fix16_mul(scalar, v->y);
    result->z = fix16_mul(scalar, v->z);
}

/// @brief Not yet documented.
///
/// @param a Not yet documented.
/// @param b Not yet documented.
///
/// @returns The value.
__BEGIN_ASM
static inline fix16_t __always_inline
fix16_vec3_inline_dot(const fix16_vec3_t *a, const fix16_vec3_t *b)
{
    __register uint32_t aux0;
    __register uint32_t aux1;

    __declare_asm("\tclrmac\n"
                  "\tmac.l @%[a]+, @%[b]+\n"
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
///
/// @returns The value.
extern fix16_t fix16_vec3_length(const fix16_vec3_t *v0);

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
///
/// @returns The value.
extern fix16_t fix16_vec3_sqr_length(const fix16_vec3_t *v0);

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
extern void fix16_vec3_normalize(fix16_vec3_t *v0);

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_vec3_normalized(const fix16_vec3_t * __restrict v0,
  fix16_vec3_t * __restrict result);

/// @brief Not yet documented.
///
/// @param v0 Not yet documented.
/// @param v1 Not yet documented.
///
/// @returns The value.
extern fix16_t fix16_vec3_dot(const fix16_vec3_t *v0, const fix16_vec3_t *v1);

/// @brief Not yet documented.
///
/// @param      v0     Not yet documented.
/// @param      v1     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_vec3_cross(const fix16_vec3_t * const __restrict v0,
  const fix16_vec3_t * const __restrict v1, fix16_vec3_t * __restrict result);

/// @brief Not yet documented.
///
/// @param      v0 Not yet documented.
/// @param      v1 Not yet documented.
///
/// @returns The value.
extern fix16_t fix16_vec3_cross_mag(const fix16_vec3_t * __restrict v0,
  const fix16_vec3_t * __restrict v1);

/// @brief Not yet documented.
///
/// @param      v0       Not yet documented.
/// @param[out] buffer   Not yet documented.
/// @param      decimals Not yet documunted.
///
/// @returns The string length, not counting the `NUL` character.
extern size_t fix16_vec3_str(const fix16_vec3_t *v0, char *buffer, int32_t decimals);

__END_DECLS

#if defined(__cplusplus)

namespace yaul {

// XXX: Forwarding. Nasty, but in order to fix this, we need to restructure the header files
struct fix16_quat;

/// @brief Not yet documented.
struct __packed __aligned(4) fix16_vec3
{
    /// @brief Not yet documented.
    fix16 x;
    /// @brief Not yet documented.
    fix16 y;
    /// @brief Not yet documented.
    fix16 z;

    fix16_vec3() = default;
    fix16_vec3(fix16_vec3 &&) = default;
    fix16_vec3(const fix16_vec3 &) = default;

    ~fix16_vec3() = default;

    constexpr explicit fix16_vec3(const fix16_vec3_t &other)
        : x { fix16 { other.x } }
        , y { fix16 { other.y } }
        , z { fix16 { other.z } }
    {
    }

    constexpr explicit fix16_vec3(fix16 x_, fix16 y_, fix16 z_)
        : x { x_ }
        , y { y_ }
        , z { z_ }
    {
    }

    constexpr explicit fix16_vec3(fix16_t x_, fix16_t y_, fix16_t z_)
        : x { fix16 { x_ } }
        , y { fix16 { y_ } }
        , z { fix16 { z_ } }
    {
    }

    fix16_vec3 &operator=(const fix16_vec3 &other) = default;
    fix16_vec3 &operator=(fix16_vec3 &&other) = default;

    const fix16_vec3 operator+(const fix16_vec3 &other) const
    {
        return fix16_vec3 { x + other.x, y + other.y, z + other.z };
    }

    const fix16_vec3 operator-(const fix16_vec3 &other) const
    {
        return fix16_vec3 { x - other.x, y - other.y, z - other.z };
    }

    const fix16_vec3 operator-() const
    {
        return fix16_vec3 { -x, -y, -z };
    }

    const fix16_vec3 operator*(fix16 scalar) const
    {
        return fix16_vec3 { x * scalar, y * scalar, z * scalar };
    }

    const fix16_vec3 operator*(fix16_t scalar) const
    {
        return fix16_vec3 { x * scalar, y * scalar, z * scalar };
    }

    // Due to the forward declaration this can't be inline
    const fix16_vec3 operator*(const fix16_quat &other) const;

    const fix16_vec3 operator/(const fix16 other) const
    {
        return fix16_vec3 { x / other, y / other, z / other };
    }

    const fix16_vec3 operator/(const fix16_t other) const
    {
        return fix16_vec3 { x / other, y / other, z / other };
    }

    fix16_vec3 &operator+=(const fix16_vec3 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    fix16_vec3 &operator-=(const fix16_vec3 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    fix16_vec3 &operator*=(fix16 rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    fix16_vec3 &operator*=(fix16_t rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    fix16_vec3 &operator/=(fix16 rhs)
    {
        const fix16 inv_value = 1.0_fp / rhs;
        x *= inv_value;
        y *= inv_value;
        z *= inv_value;
        return *this;
    }

    fix16_vec3 &operator/=(fix16_t rhs)
    {
        const fix16 inv_value = 1.0_fp / rhs;
        x *= inv_value;
        y *= inv_value;
        z *= inv_value;
        return *this;
    }

    bool is_near_zero(fix16 epsilon = 0.001_fp) const
    {
        return x.is_near_zero(epsilon) && y.is_near_zero(epsilon) &&
            z.is_near_zero(epsilon);
    }

    fix16_vec3_t *as_fix16_vec3_t()
    {
        return reinterpret_cast<fix16_vec3_t *>(this);
    }

    const fix16_vec3_t *as_fix16_vec3_t() const
    {
        return reinterpret_cast<const fix16_vec3_t *>(this);
    }

    void zero()
    {
        x = 0.0_fp;
        y = 0.0_fp;
        z = 0.0_fp;
    }

    fix16 min() const
    {
        return ::min(::min(x, y), z);
    }

    fix16 max() const
    {
        return ::max(::max(x, y), z);
    }

    fix16 dot(const fix16_vec3 &other) const
    {
        return dot(*this, other);
    }

    fix16_vec3 cross(const fix16_vec3 &other) const
    {
        return cross(*this, other);
    }

    fix16 length() const
    {
        return fix16 { fix16_vec3_length(as_fix16_vec3_t()) };
    }

    fix16 length_squared() const
    {
        return fix16 { fix16_vec3_sqr_length(as_fix16_vec3_t()) };
    }
    
    fix16& operator[](int32_t index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
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
        case 2:
            return z;
        default:
            assert(false);
            return x;
        }
    }

    void normalize()
    {
        fix16_vec3_normalize(as_fix16_vec3_t());
    }

    fix16_vec3 normalized()
    {
        fix16_vec3_t result;
        fix16_vec3_normalized(as_fix16_vec3_t(), &result);

        return fix16_vec3 { result.x, result.y, result.z };
    }

    void start_normalization() const
    {
        cpu_divu_fix16_set(FIX16(1.0), length().value);
    }

    void end_normalization()
    {
        const fix16 scale = fix16 { static_cast<fix16_t>(
            cpu_divu_quotient_get()) };
        x *= scale;
        y *= scale;
        z *= scale;
    }

    static const fix16_vec3 Zero;
    
    static const fix16_vec3 Unit_x;
    
    static const fix16_vec3 Unit_y;
    
    static const fix16_vec3 Unit_z;

    static constexpr fix16_vec3 from_double(double x, double y, double z)
    {
        return fix16_vec3 {
            fix16::from_double(x),
            fix16::from_double(y),
            fix16::from_double(z),
        };
    }

    static fix16 dot(const fix16_vec3 &a, const fix16_vec3 &b)
    {
        return fix16 { fix16_vec3_dot(a.as_fix16_vec3_t(),
            b.as_fix16_vec3_t()) };
    }

    static fix16_vec3 cross(const fix16_vec3 &a, const fix16_vec3 &b)
    {
        fix16_vec3_t result;
        fix16_vec3_cross(a.as_fix16_vec3_t(), b.as_fix16_vec3_t(), &result);

        return fix16_vec3 { result.x, result.y, result.z };
    }

    static fix16_vec3 reflect(const fix16_vec3 &v, const fix16_vec3 &normal)
    {
        const fix16 factor = dot(v, normal) << 1;
        const fix16_vec3 proj = normal * factor;
        return (v - proj);
    }

    size_t to_string(char *buffer, int32_t decimals) const
    {
        return fix16_vec3_str(as_fix16_vec3_t(), buffer, decimals);
    }
};

inline const fix16_vec3 fix16_vec3::Zero { fix16_vec3::from_double(0.0, 0.0, 0.0) };

inline const fix16_vec3 fix16_vec3::Unit_x { fix16_vec3::from_double(1.0, 0.0, 0.0) };

inline const fix16_vec3 fix16_vec3::Unit_y { fix16_vec3::from_double(0.0, 1.0, 0.0) };

inline const fix16_vec3 fix16_vec3::Unit_z { fix16_vec3::from_double(0.0, 0.0, 1.0) };

inline fix16_vec3
operator*(fix16 scalar, const fix16_vec3 &v)
{
    return fix16_vec3 { v.x * scalar, v.y * scalar, v.z * scalar };
}

} // namespace yaul

#endif /* __cplusplus */

/// @}

#endif /* !_YAUL_GAMEMATH_FIX16_VEC3_H_ */
