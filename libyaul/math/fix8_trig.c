/*
 * Copyright (c) 2012-2014 Israel Jacquez
 * Copyright (c) 2022 Romulo Fernandes
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes <abra185@gmail.com>
 */

#include <assert.h>
#include <stdbool.h>

#include <cpu/divu.h>

#include "math.h"
#include "fix8.h"

#define _FIX8_TRIG_INCLUDE_ONCE
#include "fix8_sin.inc"
// TODO: Romulo
// #include "fix8_atan.inc"
#undef _FIX8_TRIG_INCLUDE_ONCE

static inline int32_t __always_inline
_map_ranges(fix8_t radians)
{
        _Static_assert(FIX8_LUT_SIN_TABLE_COUNT == 2048,
            "Expected sin table to have 2048 elements");
        _Static_assert(FIX8_2PI == 1608,
            "Expected FIX8_2PI to be 1608 = 6.28125");
        _Static_assert(FIX8_ONE == 256,
            "Expected FIX8_ONE to be 256");

        static const fix8_t scale = 326; // 2048 / 1608 * 256
        const fix8_t index = fix8_mul(radians, scale);
        return index & FIX8_LUT_SIN_TABLE_MASK;
}

fix8_t
fix8_sin(fix8_t radians)
{
        return _fix8_sin_table[_map_ranges(radians)];
}

fix8_t
fix8_cos(fix8_t radians)
{
        return _fix8_sin_table[_map_ranges(radians + FIX8_PI_2)];
}

fix8_t
fix8_tan(const fix8_t radians)
{
        // TODO: Romulo
        /*
        const int32_t bradians = _rad2brad_convert(radians);
        const fix8_t cos = fix8_bradians_cos(bradians);

        cpu_divu_fix8_set(FIX8(1.0f), cos);

        const fix8_t sin = fix8_bradians_sin(bradians);

        const fix8_t quotient = cpu_divu_quotient_get();
        const fix8_t result = fix8_mul(sin, quotient);

        return result;
        */
       return 0;
}

fix8_t
fix8_atan2(fix8_t y, fix8_t x)
{
        // TODO: Romulo
        /*
        if (y == 0) {
                return ((x >= 0) ? 0 : FIX8_PI);
        }

        int32_t phi;
        phi = 0;

        if (y < 0) {
                x = -x;
                y = -y;
                phi += 4;
        }

        if (x <= 0) {
                const fix8_t t = x;

                x = y;
                y = -t;
                phi += 2;
        }

        if (x <= y) {
                const fix8_t t = y - x;

                x = x + y;
                y = t;
                phi++;
        }

        cpu_divu_fix8_set(y, x);

        const fix8_t q = cpu_divu_quotient_get();
        const int32_t index = fix8_int32_to(q * FIX8_LUT_ATAN_TABLE_COUNT);
        const fix8_t dphi = _lut_brads_atan[index];

        return ((phi * (FIX8_PI / 4)) + dphi);
        */
       return 0;
}
