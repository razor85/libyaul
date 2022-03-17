/*
 * Copyright (c) 2012-2014 Israel Jacquez
 * Copyright (c) 2022 Romulo Fernandes
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes <abra185@gmail.com>
 */

#ifndef _FIX8_INCLUDE_ONCE
#error "Header file must not be directly included"
#endif /* !_FIX8_INCLUDE_ONCE */

#define FIX8_PLANE_INITIALIZER(nx, ny, nz, dx, dy, dz)                        \
    {                                                                         \
            .normal = {                                                       \
                    FIX8(nx),                                                 \
                    FIX8(ny),                                                 \
                    FIX8(nz)                                                  \
            },                                                                \
            .d = {                                                            \
                    FIX8(dx),                                                 \
                    FIX8(dy),                                                 \
                    FIX8(dz)                                                  \
            }                                                                 \
    }

typedef struct fix8_plane {
        fix8_vec3_t normal;
        fix8_vec3_t d;
} __packed __aligned(4) fix8_plane_t;

extern uint32_t fix8_plane_str(const fix8_plane_t *, char *, int);
