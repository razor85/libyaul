/*-
 * Copyright (c) Authors of libfixmath
 * Copyright (c) Romulo Fernandes
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

#ifndef _YAUL_MATH_FIX8_H_
#define _YAUL_MATH_FIX8_H_

#include <sys/cdefs.h>

#include <stdint.h>

__BEGIN_DECLS

/// @addtogroup MATH
/// @{

#define FIXMATH_FUNC_ATTRS __attribute__ ((leaf, nothrow, const))

/* Macro for defining fix8_t constant values. The functions above can't be used
 * from e.g. global variable initializers, and their names are quite long also.
 * This macro is useful for constants springled alongside code, e.g.
 * FIX8(1.23).
 *
 * Note that the argument is evaluated multiple times, and also otherwise you
 * should only use this for constant values. For runtime-conversions, use the
 * inlined functions below */

#define FIX8(x) ((fix8_t)(((x) >= 0)                                         \
        ? ((x) * 256.0f + 0.5f)                                              \
        : ((x) * 256.0f - 0.5f)))

/// Not yet documented.
typedef int16_t fix8_t;
typedef int32_t fix8_32_t;

#define FIX8_MAX       (fix8_t)(0x7FFF)
#define FIX8_MIN       (fix8_t)(0x8000)
#define FIX8_OVERFLOW  (fix8_t)(0x8000)

#define FIX8_2PI       (fix8_t)(0x0648)
#define FIX8_PI        (fix8_t)(0x0324)
#define FIX8_PI_2      (fix8_t)(0x0192)
#define FIX8_PI_4      (fix8_t)(0x00C9)
#define FIX8_E         (fix8_t)(0x02B8)
#define FIX8_ONE       (fix8_t)(0x0100)
#define FIX8_RAD2DEG   (fix8_t)(0x394C)
#define FIX8_DEG2RAD   (fix8_t)(0x0004)

static inline fix8_t __always_inline
fix8_mul(const fix8_t a, const fix8_t b)
{
        register int32_t out;

        __asm__ volatile ("\tclrmac\n"
                          "\tmuls.w %[a], %[b]\n"
                          "\tsts macl, %[out]\n"
                          "\tshlr8 %[out]\n"
            /* Output */
            : [out] "=&r" (out)
            /* Input */
            : [a] "r" (a),
              [b] "r" (b)
            : "macl", "memory");

        return (fix8_t)(out & 0xFFFF);
}

static inline fix8_t __always_inline
fix8_int16_from(int16_t value)
{
        return (value * FIX8_ONE);
}

static inline int16_t __always_inline
fix8_int16_to(const fix8_t value)
{
        return (value >> 8);
}

static inline int16_t __always_inline
fix8_round_int16_to(const fix8_t value)
{
        if (value >= 0) {
                return ((value + (FIX8_ONE >> 1)) / FIX8_ONE);
        }

        return ((value - (FIX8_ONE >> 1)) / FIX8_ONE);
}

static inline fix8_t __always_inline
fix8_integral(const fix8_t value)
{
        return (value & 0xFF00);
}

static inline fix8_t __always_inline
fix8_fractional(const fix8_t value)
{
        return (value & 0x00FF);
}

static inline fix8_t __always_inline
fix8_abs(const fix8_t value)
{
        return ((value < 0) ? -value : value);
}

static inline fix8_t __always_inline
fix8_sign(const fix8_t value)
{
        return ((value < 0) ? -FIX8_ONE : FIX8_ONE);
}

static inline fix8_t __always_inline
fix8_floor(const fix8_t value)
{
        return (value & 0xFF00U);
}

static inline fix8_t __always_inline
fix8_ceil(const fix8_t value)
{
        return (value & 0xFF00U) + ((value & 0x00FFU) ? FIX8_ONE : 0);
}

static inline fix8_t __always_inline
fix8_min(const fix8_t x, const fix8_t y)
{
        return ((x < y) ? x : y);
}

static inline fix8_t __always_inline
fix8_max(const fix8_t x, const fix8_t y)
{
        return ((x > y) ? x : y);
}

static inline fix8_t __always_inline
fix8_clamp(fix8_t value, fix8_t value_low, fix8_t value_high)
{
        return fix8_min(fix8_max(value, value_low), value_high);
}

static inline fix8_t __always_inline
fix8_rad_deg_to(fix8_t radians)
{
        return fix8_mul(radians, FIX8_RAD2DEG);
}

static inline fix8_t __always_inline
fix8_deg_rad_to(fix8_t degrees)
{
        return fix8_mul(degrees, FIX8_DEG2RAD);
}

extern fix8_t fix8_overflow_add(const fix8_t, const fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_overflow_sub(const fix8_t, const fix8_t) FIXMATH_FUNC_ATTRS;

extern fix8_t fix8_lerp(const fix8_t, const fix8_t, const fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_lerp8(const fix8_t, const fix8_t, const uint8_t) FIXMATH_FUNC_ATTRS;

extern fix8_t fix8_sqrt(const fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_sqrt_precise(const fix8_32_t) FIXMATH_FUNC_ATTRS;
extern fix8_32_t fix8_32_sqrt_precise(const fix8_32_t) FIXMATH_FUNC_ATTRS;

extern uint32_t fix8_str(fix8_t, char *, int);
extern uint32_t fix8_32_str(fix8_32_t, char *, int);

#define _FIX8_INCLUDE_ONCE

// TODO: Romulo
// #include "fix8_trig.h"

#include "fix8_vec2.h"
#include "fix8_vec3.h"

#include "fix8_mat3.h"

#include "fix8_plane.h"

#undef _FIX8_INCLUDE_ONCE

#undef FIXMATH_FUNC_ATTRS

/// @}

__END_DECLS

#endif /* !_YAUL_MATH_FIX8_H_ */
