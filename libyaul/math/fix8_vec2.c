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
#include "fix16.h"

void
fix8_vec2_normalize(fix8_vec2_t *result __unused)
{
        const fix8_t length = fix8_vec2_length(result);

        cpu_divu_fix16_set(FIX8(1.0f), length);

        const fix8_t scale = cpu_divu_quotient_get();

        fix8_vec2_scale(scale, result);
}

void
fix8_vec2_normalize_precise(fix8_vec2_t *result __unused)
{
        fix16_vec2_t f16 = {
                .x = ((fix16_t)result->x) << 9,
                .y = ((fix16_t)result->y) << 9
        };

        const fix16_t length = fix16_vec2_length(&f16);

        cpu_divu_fix16_set(FIX16(1.0f), length);

        const fix16_t scale = cpu_divu_quotient_get();

        fix16_vec2_scale(scale, &f16);
        result->x = f16.x >> 9;
        result->y = f16.y >> 9;
}

void
fix8_vec2_normalized(const fix8_vec2_t * __restrict v0, fix8_vec2_t * __restrict result)
{
        const fix8_t length = fix8_vec2_length(v0);

        cpu_divu_fix16_set(FIX8(1.0f), length);

        const fix8_t scale = cpu_divu_quotient_get();

        fix8_vec2_scaled(scale, v0, result);
}

void
fix8_vec2_normalized_precise(const fix8_vec2_t * __restrict v0, fix8_vec2_t * __restrict result)
{
        fix16_vec2_t f16 = {
                .x = ((fix16_t)v0->x) << 9,
                .y = ((fix16_t)v0->y) << 9
        };

        const fix16_t length = fix16_vec2_length(&f16);

        cpu_divu_fix16_set(FIX16(1.0f), length);

        const fix16_t scale = cpu_divu_quotient_get();

        fix16_vec2_scale(scale, &f16);
        result->x = f16.x >> 9;
        result->y = f16.y >> 9;
}

fix8_t
fix8_vec2_length(const fix8_vec2_t *v0)
{
        const fix8_t r = fix8_vec2_inline_dot(v0, v0);
        const fix8_t sqrt = fix8_sqrt(r);

        return sqrt;
}

fix8_t
fix8_vec2_length_precise(const fix8_vec2_t *v0)
{
        const fix8_32_t r = fix8_vec2_dot_precise(v0, v0);
        const fix8_t sqrt = fix8_32_sqrt(r);

        return sqrt;
}

fix8_t
fix8_vec2_sqr_length(const fix8_vec2_t *v0)
{
        const fix8_t r = fix8_vec2_inline_dot(v0, v0);

        return r;
}

fix8_t
fix8_vec2_dot(const fix8_vec2_t *a, const fix8_vec2_t *b)
{
        return fix8_vec2_inline_dot(a, b);
}

fix8_32_t
fix8_vec2_dot_precise(const fix8_vec2_t *a, const fix8_vec2_t *b)
{
        return fix8_vec2_inline_dot_precise(a, b);
}

void
fix8_vec2_str(const fix8_vec2_t *v0, char *buf, int decimals)
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
        *buf_ptr++ = ')';

        *buf_ptr = '\0';
}
