/*
 * Copyright (c) Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_ANGLE_H_
#define _YAUL_GAMEMATH_ANGLE_H_

#include <sys/cdefs.h>

#include <limits.h>
#include <stdint.h>

#include <gamemath/defs.h>
#include <gamemath/fix16.h>
#include <gamemath/float.h>

/// @addtogroup MATH
/// @defgroup MATH_ANGLE Angle
/// @ingroup MATH
/// @{

/// @brief Not yet documented.
///
/// @param d Not yet documented.
#define RAD2ANGLE(d) ((angle_t)((65536.0 * (d)) / (2.0 * M_PI)))

/// @brief Not yet documented.
///
/// @param d Not yet documented.
#define DEG2ANGLE(d) ((angle_t)((65536.0 * (d)) / 360.0))

/// @brief Not yet documented.
typedef int16_t angle_t;

/// @brief Not yet documented.
typedef struct euler {
    /// @brief Not yet documented.
    angle_t pitch;
    /// @brief Not yet documented.
    angle_t yaw;
    /// @brief Not yet documented.
    angle_t roll;
} __packed __aligned(2) euler_t;

/// @brief Not yet documented.
///
/// @param angle Not yet documented.
///
/// @returns Not yet documented.
static inline fix16_t __always_inline
angle_deg_to(angle_t angle)
{
    return (angle * 360);
}

/// @brief Not yet documented.
///
/// @param angle Not yet documented.
///
/// @returns Not yet documented.
static inline fix16_t __always_inline
angle_rad_to(angle_t angle)
{
    return fix16_mul(angle, FIX16(2.0 * M_PI));
}

static inline int32_t
angle_int32_to(angle_t angle)
{
    return (angle <= SHRT_MIN) ? (uint16_t)angle : angle;
}

#if defined(__cplusplus)

__BEGIN_DECLS

extern fix16_t fix16_cos(angle_t);

extern fix16_t fix16_sin(angle_t);

extern fix16_t fix16_tan(angle_t);

extern void fix16_sincos(angle_t, fix16_t *, fix16_t *);

__END_DECLS

namespace yaul {

/// @brief Not yet documented.
struct __packed angle {
    /// @brief Not yet documented.
    angle_t value;

    angle() = default;
    
    constexpr explicit angle(angle_t v) : value(v) {}

    angle operator+(angle other) const
    {
        return angle{ static_cast<angle_t>(value + other.value) };
    }

    inline angle operator-(angle other) const
    {
        return angle { static_cast<angle_t>(value - other.value) };
    }

    constexpr angle operator-() const { return angle { static_cast<angle_t>(-value) }; }

    angle operator>>(int32_t other) const
    {
        return angle { static_cast<angle_t>((value <= SHRT_MIN) ?
                (static_cast<uint16_t>(value) >> other) :
                (value >> other)) };
    }

    angle operator<<(int32_t other) const
    {
        return angle { static_cast<angle_t>((value <= SHRT_MIN) ?
                (static_cast<int32_t>(value & 0xFFFF) << other) :
                (value << other)) };
    }

    angle &operator+=(angle rhs)
    {
        value += rhs.value;
        return *this;
    }

    angle &operator-=(angle rhs)
    {
        value -= rhs.value;
        return *this;
    }

    bool operator<(angle other) const { return value < other.value; }
    bool operator>(angle other) const { return value > other.value; }
    bool operator<=(angle other) const { return value <= other.value; }
    bool operator>=(angle other) const { return value >= other.value; }
    bool operator==(angle other) const { return value == other.value; }

    bool operator<(int32_t other) const { return value < other; }
    bool operator>(int32_t other) const { return value > other; }
    bool operator<=(int32_t other) const { return value <= other; }
    bool operator>=(int32_t other) const { return value >= other; }
    bool operator==(int32_t other) const { return value == other; }

    angle from_deg(fix16 degree)
    {
        constexpr fix16 scale { fix16::from_double(1.0 / 360.0) };
        return angle { static_cast<int16_t>((scale * degree).value) };
    }

    angle from_rad(fix16 rad)
    {
        constexpr fix16 scale { fix16::from_double(1.0 / (2.0 * M_PI)) };
        return angle { static_cast<int16_t>((scale * rad).value) };
    }

    fix16 to_rad() const
    {
        constexpr fix16 toRadians = fix16::from_double(2.0 * M_PI);
        return fix16(static_cast<int32_t>(value)) * toRadians;
    }

    fix16 to_deg() const
    {
        constexpr fix16 toDeg = fix16::from_double(360.0);
        return fix16(static_cast<int32_t>(value)) * toDeg;
    }

    fix16 cos() const { return fix16{::fix16_cos(value)}; }

    fix16 sin() const { return fix16{::fix16_sin(value)}; }

    fix16 tan() const { return fix16{::fix16_tan(value)}; }
    
    void sincos(fix16_t &out_sin, fix16_t &out_cos) const
    {
        fix16_sincos(value, &out_sin, &out_cos);
    }

    void sincos(fix16 &out_sin, fix16 &out_cos) const
    {
        fix16_sincos(value, &out_sin.value, &out_cos.value);
    }

    static constexpr angle from_rad_double(double rad)
    {
        constexpr double _2pi = 2.0 * M_PI;
        return angle {
            fix16::from_double(fmod(rad + _2pi, _2pi) / _2pi).fractional()
        };
    }

    static constexpr angle from_deg_double(double value)
    {
        return angle {
            fix16::from_double(fmod(value + 360.0, 360.0) / 360.0).fractional()
        };
    }

    size_t to_string(char *buffer, int32_t decimals) const
    {
        return fix16 { static_cast<int32_t>(value) }.to_string(buffer,
            decimals);
    }
};

static_assert(sizeof(angle) == sizeof(::angle_t));

/// @brief Not yet documented.
struct __packed __aligned(2) euler {
    /// @brief Not yet documented.
    angle pitch;
    /// @brief Not yet documented.
    angle yaw;
    /// @brief Not yet documented.
    angle roll;
};

static_assert(sizeof(euler) == sizeof(::euler_t));

} // namespace yaul

constexpr yaul::angle
operator"" _deg(long double v)
{
    return yaul::angle::from_deg_double(v);
}

constexpr yaul::angle
operator"" _rad(long double v)
{
    return yaul::angle::from_rad_double(v);
}

#endif /* !__cplusplus */

/// @}

#endif /* !_YAUL_GAMEMATH_ANGLE_H_ */
