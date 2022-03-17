/*
 * Copyright (c) 2013-2022
 * See LICENSE for details.
 *
 * Mattias Jansson
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes <abra185@gmail.com>
 */

#include <string.h>

#include "fix8.h"

void
fix8_mat3_zero(fix8_mat3_t *m0)
{
        (void)memset(&m0->arr[0], 0, sizeof(fix8_mat3_t));
}

void
fix8_mat3_dup(const fix8_mat3_t *m0, fix8_mat3_t *result)
{
        (void)memcpy(result, m0, sizeof(fix8_mat3_t));
}

void
fix8_mat3_identity(fix8_mat3_t *m0)
{
        fix8_mat3_zero(m0);

        m0->frow[0][0] = FIX8_ONE;
        m0->frow[1][1] = FIX8_ONE;
        m0->frow[2][2] = FIX8_ONE;
}

void
fix8_mat3_transpose(const fix8_mat3_t *m0, fix8_mat3_t *result)
{
        result->frow[0][0] = m0->frow[0][0];
        result->frow[0][1] = m0->frow[1][0];
        result->frow[0][2] = m0->frow[2][0];

        result->frow[1][0] = m0->frow[0][1];
        result->frow[1][1] = m0->frow[1][1];
        result->frow[1][2] = m0->frow[2][1];

        result->frow[2][0] = m0->frow[0][2];
        result->frow[2][1] = m0->frow[1][2];
        result->frow[2][2] = m0->frow[2][2];
}

void
fix8_mat3_str(const fix8_mat3_t *m0, char *buf, int decimals)
{
        for (uint32_t row_idx = 0; row_idx < 3; row_idx++) {
                char *buf_start;
                char *buf_end;

                *buf++ = '|';
                buf_start = buf;
                buf_end = buf;

                fix8_vec3_str(&m0->row[row_idx], buf, decimals);

                for (; *buf_end != '\0'; buf_end++);

                buf += buf_end - buf_start;
                *buf++ = '|';
                *buf++ = '\n';
        }

        *(--buf) = '\0';
}
