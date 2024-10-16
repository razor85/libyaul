/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Leitao <abra185@gmail.com>
 */

#ifndef _YAUL_GAMEMATH_FIX16_VEC2_H_
#define _YAUL_GAMEMATH_FIX16_VEC2_H_

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
struct fix16_vec2 {
    /// @brief Not yet documented.
    fix16_t x;
    /// @brief Not yet documented.
    fix16_t y;

    fix16_vec2() { }
    fix16_vec2(fix16_vec2&&) = default;
    fix16_vec2(const fix16_vec2&) = default;
};

static_assert(sizeof(fix16_vec2) == sizeof(::fix16_vec2_t));

} // namespace yaul

#endif /* __cplusplus */

#endif /* !_YAUL_GAMEMATH_FIX16_VEC2_H_ */
