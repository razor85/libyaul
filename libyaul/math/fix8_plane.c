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

uint32_t
fix8_plane_str(const fix8_plane_t *plane, char *buf, int decimals)
{
        char *buf_ptr;
        buf_ptr = buf;

        const uint32_t normal_len =
            fix8_vec3_str(&plane->normal, buf_ptr, decimals);

        buf_ptr += normal_len - 1;

        const uint32_t d_len =
            fix8_vec3_str(&plane->d, buf_ptr, decimals);

        return (normal_len + d_len);
}
