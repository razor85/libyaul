/*
 * Copyright (c) 2013-2014
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes <abra185@gmail.com>
 */

#include <string.h>

#include <gamemath/fix16/fix16_mat33.h>
#include <gamemath/fix16/fix16_mat43.h>
#include <gamemath/fix16/fix16_trig.h>
#include <gamemath/math3d.h>

static void _mat43_row_transpose(const fix16_t *arr, fix16_vec3_t *m0);

void
fix16_mat43_zero(fix16_mat43_t *m0)
{
    fix16_t *arr_ptr;
    arr_ptr = m0->arr;

    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;

    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;

    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr   = FIX16_ZERO;
}

void
fix16_mat43_identity(fix16_mat43_t *m0)
{
    fix16_t *arr_ptr;
    arr_ptr = m0->arr;

    *arr_ptr++ = FIX16_ONE;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;

    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ONE;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;

    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ZERO;
    *arr_ptr++ = FIX16_ONE;
    *arr_ptr   = FIX16_ZERO;
}

void
fix16_mat43_dup(const fix16_mat43_t *m0, fix16_mat43_t *result)
{
    const fix16_t *arr_ptr;
    arr_ptr = m0->arr;

    fix16_t *result_arr_ptr;
    result_arr_ptr = result->arr;

    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;

    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;

    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr++ = *arr_ptr++;
    *result_arr_ptr   = *arr_ptr;
}

void
fix16_mat43_invert(const fix16_mat43_t *m0, fix16_mat43_t *result)
{
    fix16_vec3_t * const result_m00 = (fix16_vec3_t *)&result->row[0];
    fix16_vec3_t * const result_m01 = (fix16_vec3_t *)&result->row[1];
    fix16_vec3_t * const result_m02 = (fix16_vec3_t *)&result->row[2];

    const fix16_vec3_t * const m00 = (const fix16_vec3_t *)&m0->row[0];
    const fix16_vec3_t * const m01 = (const fix16_vec3_t *)&m0->row[1];
    const fix16_vec3_t * const m02 = (const fix16_vec3_t *)&m0->row[2];

    const fix16_vec3_t neg_t = {
        .x = -m0->frow[0][3],
        .y = -m0->frow[1][3],
        .z = -m0->frow[2][3]
    };

    _mat43_row_transpose(&m0->arr[0], result_m00);
    result->frow[0][3] = fix16_vec3_dot(m00, &neg_t);

    _mat43_row_transpose(&m0->arr[1], result_m01);
    result->frow[1][3] = fix16_vec3_dot(m01, &neg_t);

    _mat43_row_transpose(&m0->arr[2], result_m02);
    result->frow[2][3] = fix16_vec3_dot(m02, &neg_t);
}

void
fix16_mat43_lookat(const fix16_vec3_t *from, const fix16_vec3_t *to,
    const fix16_vec3_t *up, fix16_mat43_t *result)
{
    const lookat_t lookat = {
        .from          = from,
        .to            = to,
        .up            = up,
        .basis_right   = (fix16_vec3_t *)&result->row[0],
        .basis_up      = (fix16_vec3_t *)&result->row[1],
        .basis_forward = (fix16_vec3_t *)&result->row[2],
    };

    math3d_lookat(&lookat);

    fix16_mat43_translation_set(from, result);
}

void
fix16_mat43_mul(const fix16_mat43_t *m0, const fix16_mat43_t *m1, fix16_mat43_t *result)
{
    fix16_vec3_t transposed_row;

    const fix16_vec3_t * const m00 = (const fix16_vec3_t *)&m0->row[0];
    const fix16_vec3_t * const m01 = (const fix16_vec3_t *)&m0->row[1];
    const fix16_vec3_t * const m02 = (const fix16_vec3_t *)&m0->row[2];

    _mat43_row_transpose(&m1->arr[0], &transposed_row);
    result->frow[0][0] = fix16_vec3_dot(m00, &transposed_row);
    result->frow[1][0] = fix16_vec3_dot(m01, &transposed_row);
    result->frow[2][0] = fix16_vec3_dot(m02, &transposed_row);

    _mat43_row_transpose(&m1->arr[1], &transposed_row);
    result->frow[0][1] = fix16_vec3_dot(m00, &transposed_row);
    result->frow[1][1] = fix16_vec3_dot(m01, &transposed_row);
    result->frow[2][1] = fix16_vec3_dot(m02, &transposed_row);

    _mat43_row_transpose(&m1->arr[2], &transposed_row);
    result->frow[0][2] = fix16_vec3_dot(m00, &transposed_row);
    result->frow[1][2] = fix16_vec3_dot(m01, &transposed_row);
    result->frow[2][2] = fix16_vec3_dot(m02, &transposed_row);

    _mat43_row_transpose(&m1->arr[3], &transposed_row);
    result->frow[0][3] = fix16_vec3_dot(m00, &transposed_row) + m0->frow[0][3];
    result->frow[1][3] = fix16_vec3_dot(m01, &transposed_row) + m0->frow[1][3];
    result->frow[2][3] = fix16_vec3_dot(m02, &transposed_row) + m0->frow[2][3];
}

void
fix16_mat43_pos3_mul(const fix16_mat43_t *m0, const fix16_vec3_t *v, fix16_vec3_t *result)
{
    fix16_mat43_vec3_mul(m0, v, result);

    result->x = result->x + m0->frow[0][3];
    result->y = result->y + m0->frow[1][3];
    result->z = result->z + m0->frow[2][3];
}

void
fix16_mat43_vec3_mul(const fix16_mat43_t *m0, const fix16_vec3_t *v, fix16_vec3_t *result)
{
    result->x = fix16_vec3_dot((const fix16_vec3_t *)&m0->row[0], v);
    result->y = fix16_vec3_dot((const fix16_vec3_t *)&m0->row[1], v);
    result->z = fix16_vec3_dot((const fix16_vec3_t *)&m0->row[2], v);
}

void
fix16_mat43_x_rotate(const fix16_mat43_t *m0, angle_t angle,
    fix16_mat43_t *result)
{
    fix16_t sin_value;
    fix16_t cos_value;

    fix16_sincos(angle, &sin_value, &cos_value);

    const fix16_t m01 = m0->frow[0][1];
    const fix16_t m02 = m0->frow[0][2];
    const fix16_t m11 = m0->frow[1][1];
    const fix16_t m12 = m0->frow[1][2];
    const fix16_t m21 = m0->frow[2][1];
    const fix16_t m22 = m0->frow[2][2];

    result->frow[0][1] =  fix16_mul(m01, cos_value) + fix16_mul(m02, sin_value);
    result->frow[0][2] = -fix16_mul(m01, sin_value) + fix16_mul(m02, cos_value);

    result->frow[1][1] =  fix16_mul(m11, cos_value) + fix16_mul(m12, sin_value);
    result->frow[1][2] = -fix16_mul(m11, sin_value) + fix16_mul(m12, cos_value);

    result->frow[2][1] =  fix16_mul(m21, cos_value) + fix16_mul(m22, sin_value);
    result->frow[2][2] = -fix16_mul(m21, sin_value) + fix16_mul(m22, cos_value);
}

void
fix16_mat43_y_rotate(const fix16_mat43_t *m0, angle_t angle,
    fix16_mat43_t *result)
{
    fix16_t sin_value;
    fix16_t cos_value;

    fix16_sincos(angle, &sin_value, &cos_value);

    const fix16_t m00 = m0->frow[0][0];
    const fix16_t m02 = m0->frow[0][2];
    const fix16_t m10 = m0->frow[1][0];
    const fix16_t m12 = m0->frow[1][2];
    const fix16_t m20 = m0->frow[2][0];
    const fix16_t m22 = m0->frow[2][2];

    result->frow[0][0] = fix16_mul(m00, cos_value) - fix16_mul(m02, sin_value);
    result->frow[0][2] = fix16_mul(m00, sin_value) + fix16_mul(m02, cos_value);
    result->frow[1][0] = fix16_mul(m10, cos_value) - fix16_mul(m12, sin_value);
    result->frow[1][2] = fix16_mul(m10, sin_value) + fix16_mul(m12, cos_value);
    result->frow[2][0] = fix16_mul(m20, cos_value) - fix16_mul(m22, sin_value);
    result->frow[2][2] = fix16_mul(m20, sin_value) + fix16_mul(m22, cos_value);
}

void
fix16_mat43_z_rotate(const fix16_mat43_t *m0, angle_t angle,
    fix16_mat43_t *result)
{
    fix16_t sin_value;
    fix16_t cos_value;

    fix16_sincos(angle, &sin_value, &cos_value);

    const fix16_t m00 = m0->frow[0][0];
    const fix16_t m01 = m0->frow[0][1];
    const fix16_t m10 = m0->frow[1][0];
    const fix16_t m11 = m0->frow[1][1];
    const fix16_t m20 = m0->frow[2][0];
    const fix16_t m21 = m0->frow[2][1];

    result->frow[0][0] =  fix16_mul(m00, cos_value) + fix16_mul(m01, sin_value);
    result->frow[0][1] = -fix16_mul(m00, sin_value) + fix16_mul(m01, cos_value);
    result->frow[1][0] =  fix16_mul(m10, cos_value) + fix16_mul(m11, sin_value);
    result->frow[1][1] = -fix16_mul(m10, sin_value) + fix16_mul(m11, cos_value);
    result->frow[2][0] =  fix16_mul(m20, cos_value) + fix16_mul(m21, sin_value);
    result->frow[2][1] = -fix16_mul(m20, sin_value) + fix16_mul(m21, cos_value);
}

void
fix16_mat43_rotation_create(angle_t rx, angle_t ry, angle_t rz,
    fix16_mat43_t *result)
{
    fix16_t sx;
    fix16_t cx;

    fix16_sincos(rx, &sx, &cx);

    fix16_t sy;
    fix16_t cy;

    fix16_sincos(ry, &sy, &cy);

    fix16_t sz;
    fix16_t cz;

    fix16_sincos(rz, &sz, &cz);

    const fix16_t sxsy = fix16_mul(sx, sy);
    const fix16_t cxsy = fix16_mul(cx, sy);

    result->frow[0][0] = fix16_mul(   cy, cz);
    result->frow[0][1] = fix16_mul( sxsy, cz) + fix16_mul(cx, sz);
    result->frow[0][2] = fix16_mul(-cxsy, cz) + fix16_mul(sx, sz);
    result->frow[1][0] = fix16_mul(  -cy, sz);
    result->frow[1][1] = fix16_mul(-sxsy, sz) + fix16_mul(cx, cz);
    result->frow[1][2] = fix16_mul( cxsy, sz) + fix16_mul(sx, cz);
    result->frow[2][0] = sy;
    result->frow[2][1] = fix16_mul(  -sx, cy);
    result->frow[2][2] = fix16_mul(   cx, cy);
}

void
fix16_mat43_rotation_set(const fix16_mat33_t *r, fix16_mat43_t *result)
{
    const fix16_t *r_arr_ptr;
    r_arr_ptr = r->arr;

    fix16_t *result_arr_ptr;
    result_arr_ptr = result->arr;

    *result_arr_ptr++ = *r_arr_ptr++;
    *result_arr_ptr++ = *r_arr_ptr++;
    *result_arr_ptr++ = *r_arr_ptr++;
    result_arr_ptr++;

    *result_arr_ptr++ = *r_arr_ptr++;
    *result_arr_ptr++ = *r_arr_ptr++;
    *result_arr_ptr++ = *r_arr_ptr++;
    result_arr_ptr++;

    *result_arr_ptr++ = *r_arr_ptr++;
    *result_arr_ptr++ = *r_arr_ptr++;
    *result_arr_ptr   = *r_arr_ptr;
}

size_t
fix16_mat43_str(const fix16_mat43_t *m0, char *buffer, int32_t decimals)
{
    char *buffer_ptr;
    buffer_ptr = buffer;

    for (uint32_t i = 0; i < 3; i++) {
        *buffer_ptr++ = '|';
        buffer_ptr += fix16_vec4_str(&m0->row[i], buffer_ptr, decimals);
        *buffer_ptr++ = '|';
        *buffer_ptr++ = '\n';
    }
    *buffer_ptr = '\0';

    return (buffer_ptr - buffer);
}

static void
_mat43_row_transpose(const fix16_t *arr, fix16_vec3_t *m0)
{
    m0->x = arr[0];
    m0->y = arr[4];
    m0->z = arr[8];
}
