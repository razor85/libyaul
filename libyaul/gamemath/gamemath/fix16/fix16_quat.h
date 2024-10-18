/*
 * Copyright (c) Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_FIX16_QUAT_H_
#define _YAUL_GAMEMATH_FIX16_QUAT_H_

#include <sys/cdefs.h>

#include <stdbool.h>
#include <stdint.h>

#include <gamemath/fix16.h>
#include <gamemath/fix16/fix16_vec3.h>
#include <gamemath/angle.h>

/// @addtogroup MATH_FIX16_VECTOR
/// @defgroup MATH_FIX16_QUAT quaternions
/// @ingroup MATH_FIX16_VECTOR
/// @{

/// @brief Macro for defininge @p fix16_quat_t constant values.
///
/// @note The argument is evaluated multiple times, and also otherwise you
/// should only use this for constant values. For runtime-conversions, use the
/// inlined functions below.
///
/// @param w The constant value.
/// @param x The constant value.
/// @param y The constant value.
/// @param z The constant value.
#define FIX16_QUAT_INITIALIZER(x, y, z, w)                                     \
{                                                                              \
    {                                                                          \
        FIX16(x),                                                              \
        FIX16(y),                                                              \
        FIX16(z)                                                               \
    },                                                                         \
    FIX16(w)                                                                   \
}

/// @brief Fixed point Q16.16.
typedef struct {
    fix16_vec3_t comp;
    /// @brief Not yet documented.
    fix16_t w;
} __packed __aligned(4) fix16_quat_t;

__BEGIN_DECLS

/// @brief Convert Euler angles to a quaternion in XYZ order.
///
/// @param      rx     Not yet documented.
/// @param      ry     Not yet documented.
/// @param      rz     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_quat_euler(angle_t rx, angle_t ry, angle_t rz,
  fix16_quat_t *result);

/// @brief Convert an axis-angle representation to a quaternion.
///
/// @param      axis   Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_quat_axis_angle(const fix16_vec3_t *axis, angle_t angle,
  fix16_quat_t *result);

/// @brief Not yet documented.
///
/// @param      q0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_quat_conjugate(const fix16_quat_t *q0, fix16_quat_t *result);

/// @brief Not yet documented.
///
/// @param      q0     Not yet documented.
/// @param      q1     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_quat_mul(const fix16_quat_t *q0, const fix16_quat_t *q1,
  fix16_quat_t *result);

/// @brief Not yet documented.
///
/// @param      q0     Not yet documented.
/// @param      v0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_quat_vec3_mul(const fix16_quat_t *q0,
  const fix16_vec3_t *v0, fix16_vec3_t *result);

/// @brief Not yet documented.
///
/// @param      q0       Not yet documented.
/// @param[out] buffer   Not yet documented.
/// @param      decimals Not yet documented.
///
/// @returns The string length, not counting the `NUL` character.
extern size_t fix16_quat_str(const fix16_quat_t *q0, char *buffer,
  int32_t decimals);

__END_DECLS

#if defined(__cplusplus)

namespace yaul {

/// @brief Fixed point Q16.16.
struct __packed __aligned(4) fix16_quat {
    /// @brief Not yet documented.
    fix16_vec3 comp;
    /// @brief Not yet documented.
    fix16 w;

    fix16_quat() = default;
    fix16_quat(fix16_quat&&)      = default;
    fix16_quat(const fix16_quat&) = default;

    constexpr explicit fix16_quat(const fix16_quat_t& other)
        : comp(other.comp)
        , w(other.w)
    {
    }

    constexpr explicit fix16_quat(fix16 x_, fix16 y_, fix16 z_, fix16 w_)
        : comp(x_, y_, z_)
        , w(w_)
    {
    }

    constexpr explicit fix16_quat(const fix16_vec3 &comp_, fix16 w_)
        : comp(comp_)
        , w(w_)
    {
    }

    fix16_quat &operator=(const fix16_quat &other) = default;
    fix16_quat &operator=(fix16_quat &&other) = default;

    fix16_quat_t* as_fix16_quat_t()
    {
      return reinterpret_cast<fix16_quat_t*>(this);
    }

    const fix16_quat_t* as_fix16_quat_t() const
    {
      return reinterpret_cast<const fix16_quat_t*>(this);
    }

    void identity()
    {
        comp.zero();
        w = fix16::One;
    }

    const fix16_quat operator*(const fix16_quat &other) const
    {
        fix16_quat_t result;
        fix16_quat_mul(as_fix16_quat_t(), other.as_fix16_quat_t(), &result);

        return fix16_quat { result };
    }

    size_t to_string(char *buffer, int32_t decimals) const
    {
        return fix16_quat_str(as_fix16_quat_t(), buffer, decimals);
    }

    fix16_quat from_euler(const euler &angles)
    {
        fix16_quat_t result;
        fix16_quat_euler(angles.pitch.value, angles.yaw.value,
            angles.roll.value, &result);

        return fix16_quat{ result };
    }

    fix16_quat from_axis_angle(const fix16_vec3 &axis, angle angle)
    {
        fix16_quat_t result;
        fix16_quat_axis_angle(axis.as_fix16_vec3_t(), angle.value, &result);

        return fix16_quat { result };
    }

    static constexpr fix16_quat from_double(double x, double y, double z, double w)
    {
        return fix16_quat { fix16::from_double(x), fix16::from_double(y),
            fix16::from_double(z), fix16::from_double(w) };
    }

    static fix16_quat conjugate(const fix16_quat &q)
    {
        fix16_quat_t result;
        fix16_quat_conjugate(q.as_fix16_quat_t(), &result);

        return fix16_quat { result };
    }
};

static_assert(sizeof(fix16_quat) == sizeof(::fix16_quat_t));

} // namespace yaul

#endif /* __cplusplus */

/// @}

#endif /* !_YAUL_GAMEMATH_FIX16_QUAT_H_ */
