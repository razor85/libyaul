/*
 * Copyright (c) 2013-2022
 * See LICENSE for details.
 *
 * Mattias Jansson
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes <abra185@gmail.com>
 */

#include <string.h>

#include <cpu/divu.h>

#include "fix8.h"

void
fix8_vec3_normalize(fix8_vec3_t *result)
{
        const fix8_t length = fix8_vec3_length(result);

        cpu_divu_fix16_set(FIX8(1.0f), length);

        const fix8_t scale = cpu_divu_quotient_get();

        fix8_vec3_scale(scale, result);
}

void
fix8_vec3_normalize_precise(fix8_vec3_t *result __unused)
{
        fix16_vec3_t f16 = {
                .x = ((fix16_t)result->x) << 9,
                .y = ((fix16_t)result->y) << 9,
                .z = ((fix16_t)result->z) << 9
        };

        const fix16_t length = fix16_vec3_length(&f16);

        cpu_divu_fix16_set(FIX16(1.0f), length);

        const fix16_t scale = cpu_divu_quotient_get();

        fix16_vec3_scale(scale, &f16);
        result->x = f16.x >> 9;
        result->y = f16.y >> 9;
        result->z = f16.z >> 9;
}

void
fix8_vec3_normalized(const fix8_vec3_t * __restrict v0,
    fix8_vec3_t * __restrict result)
{
        const fix8_t length = fix8_vec3_length(v0);

        cpu_divu_fix16_set(FIX8(1.0f), length);

        const fix8_t scale = cpu_divu_quotient_get();

        fix8_vec3_scaled(scale, v0, result);
}

void
fix8_vec3_normalized_precise(const fix8_vec3_t * __restrict v0,
    fix8_vec3_t * __restrict result)
{
        fix16_vec3_t f16 = {
                .x = ((fix16_t)v0->x) << 9,
                .y = ((fix16_t)v0->y) << 9,
                .z = ((fix16_t)v0->z) << 9
        };

        const fix16_t length = fix16_vec3_length(&f16);

        cpu_divu_fix16_set(FIX16(1.0f), length);

        const fix16_t scale = cpu_divu_quotient_get();

        fix16_vec3_scale(scale, &f16);
        result->x = f16.x >> 9;
        result->y = f16.y >> 9;
        result->z = f16.z >> 9;
}

fix8_t
fix8_vec3_length(const fix8_vec3_t *v0)
{
        const fix8_t r = fix8_vec3_sqr_length(v0);
        return fix8_sqrt(r);
}

fix8_t
fix8_vec3_length_precise(const fix8_vec3_t *v0)
{
        const fix8_32_t r = fix8_32_vec3_dot_precise(v0, v0);
        return fix8_sqrt_precise(r);
}

fix8_32_t
fix8_32_vec3_length_precise(const fix8_vec3_t *v0)
{
        const fix8_32_t r = fix8_32_vec3_dot_precise(v0, v0);
        return fix8_32_sqrt_precise(r);
}

fix8_t
fix8_vec3_sqr_length(const fix8_vec3_t *v0)
{
        const fix8_t r = fix8_vec3_inline_dot(v0, v0);

        return r;
}

fix8_32_t
fix8_32_vec3_sqr_length(const fix8_vec3_t *v0)
{
        return fix8_32_vec3_inline_dot_precise(v0, v0);
}

fix8_t
fix8_vec3_dot(const fix8_vec3_t *a, const fix8_vec3_t *b)
{
        return fix8_vec3_inline_dot(a, b);
}

fix8_t
fix8_vec3_dot_precise(const fix8_vec3_t *a, const fix8_vec3_t *b)
{
        return fix8_32_vec3_inline_dot_precise(a, b);
}

fix8_32_t
fix8_32_vec3_dot_precise(const fix8_vec3_t *a, const fix8_vec3_t *b)
{
        return fix8_32_vec3_inline_dot_precise(a, b);
}

void
fix8_vec3_cross(const fix8_vec3_t * const __restrict v0,
    const fix8_vec3_t * const __restrict v1, fix8_vec3_t * __restrict result)
{
        result->x = fix8_mul(v0->y, v1->z) - fix8_mul(v0->z, v1->y);
        result->y = fix8_mul(v0->z, v1->x) - fix8_mul(v0->x, v1->z);
        result->z = fix8_mul(v0->x, v1->y) - fix8_mul(v0->y, v1->x);
}

fix8_t
fix8_vec3_cross_mag(const fix8_vec3_t * __restrict v0,
    const fix8_vec3_t * __restrict v1)
{
        const fix8_t t1 = fix8_mul(v0->x, v1->y) - fix8_mul(v0->y, v1->x);
        const fix8_t t2 = fix8_mul(v0->y, v1->z) - fix8_mul(v0->z, v1->y);
        const fix8_t t3 = fix8_mul(v0->z, v1->x) - fix8_mul(v0->x, v1->z);

        const fix8_t t1_2 = fix8_mul(t1, t1);
        const fix8_t t2_2 = fix8_mul(t2, t2);
        const fix8_t t3_2 = fix8_mul(t3, t3);

        const fix8_t result = t1_2 + t2_2 + t3_2;

        return result;
}

uint32_t
fix8_vec3_str(const fix8_vec3_t *v0, char *buf, int decimals)
{
        char component_buf[13] __aligned(16);
        size_t component_buf_len;

        char *buf_ptr;
        buf_ptr = buf;

        *buf_ptr++ = '(';
        fix8_str(v0->x, component_buf, decimals);
        component_buf_len = strlen(component_buf);
        memcpy(buf_ptr, component_buf, component_buf_len);
        buf_ptr += component_buf_len;
        *buf_ptr++ = ',';

        fix8_str(v0->y, component_buf, decimals);
        component_buf_len = strlen(component_buf);
        memcpy(buf_ptr, component_buf, component_buf_len);
        buf_ptr += component_buf_len;
        *buf_ptr++ = ',';

        fix8_str(v0->z, component_buf, decimals);
        component_buf_len = strlen(component_buf);
        memcpy(buf_ptr, component_buf, component_buf_len);
        buf_ptr += component_buf_len;
        *buf_ptr++ = ')';

        *buf_ptr = '\0';

        return (buf_ptr - buf);
}
