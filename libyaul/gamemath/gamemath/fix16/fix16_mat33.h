/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes <abra185@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_FIX16_MAT33_H_
#define _YAUL_GAMEMATH_FIX16_MAT33_H_

#include <sys/cdefs.h>

#include <gamemath/angle.h>
#include <gamemath/fix16/fix16_vec3.h>

/// @addtogroup MATH_FIX16_MATRIX
/// @defgroup MATH_FIX16_MATRIX3X3 3x3
/// @ingroup MATH_FIX16_MATRIX
/// @{

/// @brief Not yet documented.
#define FIX16_MAT33_COLUMNS (3)

/// @brief Not yet documented.
#define FIX16_MAT33_ROWS    (3)

/// @brief Not yet documented.
#define FIX16_MAT33_ARR_COUNT (FIX16_MAT33_COLUMNS * FIX16_MAT33_ROWS)

/// @brief Not yet documented.
///
/// @note Row-major matrix.
typedef struct fix16_mat33 {
    /// @brief Not yet documented.
    fix16_vec3_t row[FIX16_MAT33_ROWS];
} __packed __aligned(4) fix16_mat33_t;

__BEGIN_DECLS

/// @brief Not yet documented.
///
/// @param m0 Not yet documented.
extern void fix16_mat33_zero(fix16_mat33_t *m0);

/// @brief Not yet documented.
///
/// @param m0 Not yet documented.
extern void fix16_mat33_identity(fix16_mat33_t *m0);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_dup(const fix16_mat33_t *m0, fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_transpose(const fix16_mat33_t * __restrict m0,
  fix16_mat33_t * __restrict result);

/// @brief Not yet documented.
///
/// @param m0 Not yet documented.
extern void fix16_mat33_inplace_transpose(fix16_mat33_t *m0);

/// @brief Not yet documented.
///
/// @param      from   Not yet documented.
/// @param      to     Not yet documented.
/// @param      up     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_lookat(const fix16_vec3_t *from, const fix16_vec3_t *to,
  const fix16_vec3_t *up, fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      m1     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_mul(const fix16_mat33_t *m0, const fix16_mat33_t *m1,
  fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      v      Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_vec3_mul(const fix16_mat33_t *m0, const fix16_vec3_t *v,
  fix16_vec3_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_x_rotate(const fix16_mat33_t *m0, angle_t angle,
  fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_y_rotate(const fix16_mat33_t *m0, angle_t angle,
  fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      m0     Not yet documented.
/// @param      angle  Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_z_rotate(const fix16_mat33_t *m0, angle_t angle,
  fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      rx     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_x_rotation_create(angle_t rx, fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      ry     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_y_rotation_create(angle_t ry, fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      rz     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_z_rotation_create(angle_t rz, fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      rx     Not yet documented.
/// @param      ry     Not yet documented.
/// @param      rz     Not yet documented.
/// @param[out] result Not yet documented.
extern void fix16_mat33_rotation_create(angle_t rx, angle_t ry, angle_t rz,
  fix16_mat33_t *result);

/// @brief Not yet documented.
///
/// @param      m0       Not yet documented.
/// @param[out] buffer   Not yet documented.
/// @param      decimals Not yet documunted.
///
/// @returns The string length, not counting the `NUL` character.
extern size_t fix16_mat33_str(const fix16_mat33_t *m0, char *buffer,
  int32_t decimals);

__END_DECLS

#ifdef __cplusplus

namespace yaul {

struct __packed __aligned(4) fix16_mat33 {
    fix16_vec3 row[FIX16_MAT33_ROWS];

    fix16_mat33() = default;
    fix16_mat33(fix16_mat33 &&) = default;
    fix16_mat33(const fix16_mat33 &) = default;

    constexpr explicit fix16_mat33(const fix16_mat33_t &other)
        : row({
              fix16_vec3 { other.row[0] },
              fix16_vec3 { other.row[1] },
              fix16_vec3 { other.row[2] },
          })
    {
    }

    constexpr explicit fix16_mat33(
        // Row 0
        fix16 m00, fix16 m01, fix16 m02,
        // Row 1
        fix16 m10, fix16 m11, fix16 m12,
        // Row 2
        fix16 m20, fix16 m21, fix16 m22)
        : row({
              // Row 0
              fix16_vec3{ m00, m01, m02 },
              // Row 1
              fix16_vec3{ m10, m11, m12 },
              // Row 2
              fix16_vec3{ m20, m21, m22 },
          })
    {
    }

    fix16_mat33_t *as_fix16_mat33_t()
    {
        return reinterpret_cast<fix16_mat33_t *>(this);
    }

    const fix16_mat33_t *as_fix16_mat33_t() const
    {
        return reinterpret_cast<const fix16_mat33_t *>(this);
    }

    fix16_mat33 operator*(const fix16_mat33 &other) const
    {
        fix16_mat33_t result;
        fix16_mat33_mul(as_fix16_mat33_t(), other.as_fix16_mat33_t(), &result);

        return fix16_mat33 { result };
    }

    static constexpr fix16_mat33 from_double(
        // Row 0
        double m00, double m01, double m02,
        // Row 1
        double m10, double m11, double m12,
        // Row 2
        double m20, double m21, double m22)
    {
        return fix16_mat33 {
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
        };
    }

    void identity() { fix16_mat33_identity(as_fix16_mat33_t()); }

    void zero() { fix16_mat33_zero(as_fix16_mat33_t()); }

    void transpose() { fix16_mat33_inplace_transpose(as_fix16_mat33_t()); }

    void invert() { transpose(); }

    size_t to_string(char *buffer, int32_t decimals) const
    {
        return fix16_mat33_str(as_fix16_mat33_t(), buffer, decimals);
    }

    void create_rotx(const fix16_mat33 &m0, angle x, fix16_mat33 &result)
    {
        fix16_mat33_x_rotate(m0.as_fix16_mat33_t(), x.value, result.as_fix16_mat33_t());
    }

    void create_roty(const fix16_mat33 &m0, angle y, fix16_mat33 &result)
    {
        fix16_mat33_y_rotate(m0.as_fix16_mat33_t(), y.value, result.as_fix16_mat33_t());
    }

    void create_rotz(const fix16_mat33 &m0, angle z, fix16_mat33 &result)
    {
        fix16_mat33_z_rotate(m0.as_fix16_mat33_t(), z.value, result.as_fix16_mat33_t());
    }

    void create_rot(const euler &angles, fix16_mat33 &result)
    {
        fix16_mat33_rotation_create(angles.pitch.value, angles.yaw.value,
            angles.roll.value, result.as_fix16_mat33_t());
    }

    fix16_vec3 transform_vector(const fix16_mat33 &m0, const fix16_vec3 &v)
    {
        fix16_vec3_t result;
        fix16_mat33_vec3_mul(m0.as_fix16_mat33_t(), v.as_fix16_vec3_t(),
            &result);

        return fix16_vec3 { result };
    }
};

static_assert(sizeof(fix16_mat33) == sizeof(fix16_mat33_t));

} // namespace yaul

#endif /* __cplusplus */

/// @}

#endif /* !_YAUL_GAMEMATH_FIX16_MAT33_H_ */
