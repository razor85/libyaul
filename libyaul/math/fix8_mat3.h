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

union fix8_vec3;

typedef union fix8_vec3 fix8_vec3_t;

// TODO: Romulo - aligned to 4?

/* Row-major matrix */
typedef union fix8_mat3 {
        struct {
                fix8_t m00, m01, m02; /* Row 0 */
                fix8_t m10, m11, m12; /* Row 1 */
                fix8_t m20, m21, m22; /* Row 2 */
        } comp;

        fix8_t arr[9];
        fix8_t frow[3][3];
        fix8_vec3_t row[3];
} __packed fix8_mat3_t;

extern void fix8_mat3_dup(const fix8_mat3_t *, fix8_mat3_t *);
extern void fix8_mat3_identity(fix8_mat3_t *);
extern void fix8_mat3_str(const fix8_mat3_t *, char *, int);
extern void fix8_mat3_transpose(const fix8_mat3_t * __restrict,
    fix8_mat3_t * __restrict);
extern void fix8_mat3_zero(fix8_mat3_t *);
