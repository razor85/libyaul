/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Leitao <abra185@gmail.com>
 */

#include <string.h>

#include <gamemath/fix16/fix16_mat33.h>
#include <gamemath/fix16/fix16_mat43.h>
#include <gamemath/fix16/fix16_trig.h>
#include <gamemath/math3d.h>
#include "gamemath/fix16/fix16_vec3.h"

void
fix16_mat43_zero(fix16_mat43_t *m0)
{
    fix16_mat33_zero(&m0->rotation);
    fix16_vec3_zero(&m0->translation);
}

void
fix16_mat43_identity(fix16_mat43_t *m0)
{
    fix16_mat33_identity(&m0->rotation);
    fix16_vec3_zero(&m0->translation);
}

void
fix16_mat43_dup(const fix16_mat43_t *m0, fix16_mat43_t *result)
{
    fix16_mat33_dup(&m0->rotation, &result->rotation);
    fix16_vec3_dup(&m0->translation, &result->translation);
}

void
fix16_mat43_invert(const fix16_mat43_t *m0, fix16_mat43_t *result)
{
    const fix16_vec3_t * const m00 = &m0->rotation.row[0];
    const fix16_vec3_t * const m01 = &m0->rotation.row[1];
    const fix16_vec3_t * const m02 = &m0->rotation.row[2];

    fix16_mat33_transpose(&m0->rotation, &result->rotation);

    result->translation.x = -fix16_vec3_dot(m00, &m0->translation);
    result->translation.y = -fix16_vec3_dot(m01, &m0->translation);
    result->translation.z = -fix16_vec3_dot(m02, &m0->translation);
}

void
fix16_mat43_inplace_invert(fix16_mat43_t *m0)
{
    const fix16_vec3_t * const m00 = &m0->rotation.row[0];
    const fix16_vec3_t * const m01 = &m0->rotation.row[1];
    const fix16_vec3_t * const m02 = &m0->rotation.row[2];

    /* Invert translation before transpose */
    m0->translation.x = -fix16_vec3_dot(m00, &m0->translation);
    m0->translation.y = -fix16_vec3_dot(m01, &m0->translation);
    m0->translation.z = -fix16_vec3_dot(m02, &m0->translation);

    fix16_mat33_inplace_transpose(&m0->rotation);
}

void
fix16_mat43_lookat(const fix16_vec3_t *from, const fix16_vec3_t *to,
    const fix16_vec3_t *up, fix16_mat43_t *result)
{
    fix16_mat33_lookat(from, to, up, &result->rotation);
    fix16_vec3_dup(from, &result->translation);
}

void
fix16_mat43_mul(const fix16_mat43_t *m0, const fix16_mat43_t *m1, fix16_mat43_t *result)
{
    fix16_mat33_mul(&m0->rotation, &m1->rotation, &result->rotation);
    fix16_mat43_pos3_mul(m0, &m1->translation, &result->translation);
}

void
fix16_mat43_pos3_mul(const fix16_mat43_t *m0, const fix16_vec3_t *v, fix16_vec3_t *result)
{
    fix16_mat43_vec3_mul(m0, v, result);

    result->x = result->x + m0->translation.x;
    result->y = result->y + m0->translation.y;
    result->z = result->z + m0->translation.z;
}

void
fix16_mat43_vec3_mul(const fix16_mat43_t *m0, const fix16_vec3_t *v, fix16_vec3_t *result)
{
    fix16_mat33_vec3_mul(&m0->rotation, v, result);
}

void
fix16_mat43_x_rotate(const fix16_mat43_t *m0, angle_t angle,
    fix16_mat43_t *result)
{
    fix16_mat33_x_rotate(&m0->rotation, angle, &result->rotation);
    fix16_mat43_pos3_mul(result, &m0->translation, &result->translation);
}

void
fix16_mat43_y_rotate(const fix16_mat43_t *m0, angle_t angle,
    fix16_mat43_t *result)
{
    fix16_mat33_y_rotate(&m0->rotation, angle, &result->rotation);
    fix16_mat43_pos3_mul(result, &m0->translation, &result->translation);
}

void
fix16_mat43_z_rotate(const fix16_mat43_t *m0, angle_t angle,
    fix16_mat43_t *result)
{
    fix16_mat33_z_rotate(&m0->rotation, angle, &result->rotation);
    fix16_mat43_pos3_mul(result, &m0->translation, &result->translation);
}

void
fix16_mat43_x_rotation_set(angle_t rx, fix16_mat43_t *result)
{
    fix16_mat33_x_rotation_create(rx, &result->rotation);
}

void
fix16_mat43_y_rotation_set(angle_t ry, fix16_mat43_t *result)
{
    fix16_mat33_y_rotation_create(ry, &result->rotation);
}

void
fix16_mat43_z_rotation_set(angle_t rz, fix16_mat43_t *result)
{
    fix16_mat33_z_rotation_create(rz, &result->rotation);
}

void
fix16_mat43_rotation_set(angle_t rx, angle_t ry, angle_t rz,
    fix16_mat43_t *result)
{
    fix16_mat33_rotation_create(rx, ry, rz, &result->rotation);
}

size_t
fix16_mat43_str(const fix16_mat43_t *m0, char *buffer, int32_t decimals)
{
    char *buffer_ptr;
    buffer_ptr = buffer;

    buffer_ptr += fix16_mat33_str(&m0->rotation, buffer_ptr, decimals);

    *buffer_ptr++ = '\n';
    *buffer_ptr++ = '|';
    buffer_ptr += fix16_vec3_str(&m0->translation, buffer_ptr, decimals);
    *buffer_ptr++ = '|';

    *buffer_ptr = '\0';

    return (buffer_ptr - buffer);
}
