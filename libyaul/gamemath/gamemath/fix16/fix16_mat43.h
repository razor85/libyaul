/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Leitao <abra185@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_FIX16_MAT43_H_
#define _YAUL_GAMEMATH_FIX16_MAT43_H_

#include <gamemath/angle.h>
#include <gamemath/fix16/fix16_vec3.h>
#include <gamemath/fix16/fix16_mat33.h>

/// @addtogroup MATH_FIX16_MATRIX
/// @defgroup MATH_FIX16_MATRIX4X3 4x3
/// @ingroup MATH_FIX16_MATRIX
/// @{

/// @brief Not yet documented.
#define FIX16_MAT43_ROWS    (4)
/// @brief Not yet documented.
#define FIX16_MAT43_COLUMNS (3)

/// @brief Not yet documented.
#define FIX16_MAT43_ARR_COUNT (FIX16_MAT43_COLUMNS * FIX16_MAT43_ROWS)

/// @cond
// TODO: Remove this
struct fix16_vec3;
// TODO: Remove this
struct fix16_mat33;

// TODO: Remove this
typedef struct fix16_mat33 fix16_mat33_t;
/// @endcond

/// @brief Not yet documented.
///
/// @note Row-major matrix.
typedef struct fix16_mat43 {
    /// @brief Not yet documented.
    fix16_mat33_t rotation;
    /// @brief Not yet documented.
    fix16_vec3_t translation;
} fix16_mat43_t;

__BEGIN_DECLS

/// @brief Not yet documented.
///
/// @param m0 Not yet documented.
extern void fix16_mat43_zero(fix16_mat43_t *m0);

/// @brief Not yet documented.
///
/// @param m0 Not yet documented.
extern void fix16_mat43_identity(fix16_mat43_t *m0);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_dup(const fix16_mat43_t *m0, fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// The expectation is that the rotation part of the matrix is orthogonal.
///
/// It's then possible to just transpose the 3x3 rotation matrix within the 4x3
/// matrix and negate the translation vector.
///
/// @param      m0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_invert(const fix16_mat43_t *m0, fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// The expectation is that the rotation part of the matrix is orthogonal.
///
/// It's then possible to just transpose the 3x3 rotation matrix within the 4x3
/// matrix and negate the translation vector.
///
/// @param m0 Not yet documented.
extern void fix16_mat43_inplace_invert(fix16_mat43_t *m0);

/// @brief Not yet documented.
///
/// @param      from   Not yet documented.
/// @param      to     Not yet documented.
/// @param      up     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_lookat(const fix16_vec3_t *from, const fix16_vec3_t *to,
  const fix16_vec3_t *up, fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      m1     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_mul(const fix16_mat43_t *m0, const fix16_mat43_t *m1,
  fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      v      Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_pos3_mul(const fix16_mat43_t *m0, const fix16_vec3_t *v,
  fix16_vec3_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      v      Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_vec3_mul(const fix16_mat43_t *m0, const fix16_vec3_t *v,
  fix16_vec3_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_x_rotate(const fix16_mat43_t *m0, angle_t angle,
  fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_y_rotate(const fix16_mat43_t *m0, angle_t angle,
  fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_z_rotate(const fix16_mat43_t *m0, angle_t angle,
  fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      rx     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_x_rotation_set(angle_t rx, fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      ry     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_y_rotation_set(angle_t ry, fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      rz     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_z_rotation_set(angle_t rz, fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      rx     Not yet documented.
/// @param      ry     Not yet documented.
/// @param      rz     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat43_rotation_set(angle_t rx, angle_t ry, angle_t rz,
  fix16_mat43_t *result);

/// @brief Not yet documented.
///
/// @param      m0       Not yet documented.
/// @param[out] buffer   Not yet documented.
/// @param      decimals Not yet documunted.
///
/// @returns The string length, not counting the `NUL` character.
extern size_t fix16_mat43_str(const fix16_mat43_t *m0, char *buffer,
  int32_t decimals);

__END_DECLS

#ifdef __cplusplus

namespace yaul {

struct fix16_vec3;
struct fix16_mat33;

struct __packed __aligned(4) fix16_mat43 {
    /// @brief Not yet documented.
    fix16_mat33 rotation;
    /// @brief Not yet documented.
    fix16_vec3 translation;

    fix16_mat43() = default;
    fix16_mat43(fix16_mat43 &&) = default;
    fix16_mat43(const fix16_mat43 &) = default;

    constexpr explicit fix16_mat43(const fix16_mat43_t &other)
        : rotation(fix16_mat33 { other.rotation })
        , translation(fix16_vec3 { other.translation })
    {
    }

    constexpr explicit fix16_mat43(
        // Row 0
        fix16_t m00, fix16_t m01, fix16_t m02,
        // Row 1
        fix16_t m10, fix16_t m11, fix16_t m12,
        // Row 2
        fix16_t m20, fix16_t m21, fix16_t m22,
        // Row 3
        fix16_t m30, fix16_t m31, fix16_t m32)
        : rotation( // Row 0
              fix16 { m00 }, fix16 { m01 }, fix16 { m02 },
              // Row 1
              fix16 { m10 }, fix16 { m11 }, fix16 { m12 },
              // Row 2
              fix16 { m20 }, fix16 { m21 }, fix16 { m22 })
        , translation(fix16 { m30 }, fix16 { m31 }, fix16 { m32 })
    {
    }

    constexpr fix16_mat43(
        // Row 0
        fix16 m00, fix16 m01, fix16 m02,
        // Row 1
        fix16 m10, fix16 m11, fix16 m12,
        // Row 2
        fix16 m20, fix16 m21, fix16 m22,
        // Row 3
        fix16 m30, fix16 m31, fix16 m32)
        : rotation( // Row 0
              m00, m01, m02,
              // Row 1
              m10, m11, m12,
              // Row 2
              m20, m21, m22)
        , translation(m30, m31, m32)
    {
    }

    fix16_mat43_t *as_fix16_mat43_t()
    {
        return reinterpret_cast<fix16_mat43_t *>(this);
    }

    const fix16_mat43_t *as_fix16_mat43_t() const
    {
        return reinterpret_cast<const fix16_mat43_t *>(this);
    }

    fix16_mat43 operator*(const fix16_mat43 &other) const
    {
        fix16_mat43_t result;
        fix16_mat43_mul(as_fix16_mat43_t(), other.as_fix16_mat43_t(), &result);

        return fix16_mat43 { result };
    }

    static constexpr fix16_mat43 identity()
    {
        return fix16_mat43 {
            // Row 0
            1.0_fp,
            0.0_fp,
            0.0_fp,
            // Row 1
            0.0_fp,
            1.0_fp,
            0.0_fp,
            // Row 2
            0.0_fp,
            0.0_fp,
            1.0_fp,
            // Row 3
            0.0_fp,
            0.0_fp,
            0.0_fp,
        };
    }

    static constexpr fix16_mat43 zero()
    {
        return fix16_mat43 {
            // Row 0
            0.0_fp,
            0.0_fp,
            0.0_fp,
            // Row 1
            0.0_fp,
            0.0_fp,
            0.0_fp,
            // Row 2
            0.0_fp,
            0.0_fp,
            0.0_fp,
            // Row 3
            0.0_fp,
            0.0_fp,
            0.0_fp,
        };
    }

    static constexpr fix16_mat43 from_double(
        // Row 0
        double m00, double m01, double m02,
        // Row 1
        double m10, double m11, double m12,
        // Row 2
        double m20, double m21, double m22,
        // Row 3
        double m30, double m31, double m32)
    {
        return fix16_mat43 {
            // Row 0
            fix16::from_double(m00),
            fix16::from_double(m01),
            fix16::from_double(m02),
            // Row 1
            fix16::from_double(m10),
            fix16::from_double(m11),
            fix16::from_double(m12),
            // Row 2
            fix16::from_double(m20),
            fix16::from_double(m21),
            fix16::from_double(m22),
            // Row 3
            fix16::from_double(m30),
            fix16::from_double(m31),
            fix16::from_double(m32),
        };
    }

    inline void set_identity() { fix16_mat43_identity(as_fix16_mat43_t()); }

    inline void set_zero() { fix16_mat43_zero(as_fix16_mat43_t()); }

    inline void invert() { fix16_mat43_inplace_invert(as_fix16_mat43_t()); }

    inline void rotate_x(angle pitch)
    {
        fix16_mat43_x_rotate(as_fix16_mat43_t(), pitch.value, as_fix16_mat43_t());
    }

    inline void rotate_y(angle yaw)
    {
        fix16_mat43_y_rotate(as_fix16_mat43_t(), yaw.value, as_fix16_mat43_t());
    }

    inline void rotate_z(angle roll)
    {
        fix16_mat43_z_rotate(as_fix16_mat43_t(), roll.value,
            as_fix16_mat43_t());
    }

    inline size_t to_string(char *buffer, int32_t decimals) const
    {
        return fix16_mat43_str(as_fix16_mat43_t(), buffer, decimals);
    }

    inline void create_rotx(angle pitch, fix16_mat43 & result)
    {
        fix16_mat43_x_rotation_set(pitch.value, result.as_fix16_mat43_t());
    }

    inline void create_roty(angle yaw, fix16_mat43 & result)
    {
        fix16_mat43_y_rotation_set(yaw.value, result.as_fix16_mat43_t());
    }

    inline void create_rotz(angle roll, fix16_mat43 & result)
    {
        fix16_mat43_z_rotation_set(roll.value, result.as_fix16_mat43_t());
    }

    inline void create_rot(const euler &angles, fix16_mat43 &result)
    {
        fix16_mat43_rotation_set(angles.pitch.value, angles.yaw.value,
            angles.roll.value, result.as_fix16_mat43_t());
    }

    inline fix16_vec3 transform_vector(const fix16_mat43 &m0,
        const fix16_vec3 &v)
    {
        fix16_vec3_t result;
        fix16_mat43_vec3_mul(m0.as_fix16_mat43_t(), v.as_fix16_vec3_t(),
            &result);

        return fix16_vec3 { result };
    }

    inline fix16_vec3 transform_position(const fix16_mat43 &m0,
        const fix16_vec3 &v)
    {
        fix16_vec3_t result;
        fix16_mat43_pos3_mul(m0.as_fix16_mat43_t(), v.as_fix16_vec3_t(), &result);

        return fix16_vec3{result};
    }
};

static_assert(sizeof(fix16_mat43) == (sizeof(fix16_t) * FIX16_MAT43_ARR_COUNT));

} // namespace yaul

#endif /* __cplusplus */

/// @}

#endif /* !_YAUL_GAMEMATH_FIX16_MAT43_H_ */
