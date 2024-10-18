/*
 * Copyright (c)
 * See LICENSE for details.
 *
 * Mattias Jansson
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Leitao <abra185@gmail.com>
 */

#include <assert.h>

#include <gamemath/fix16/fix16_mat33.h>
#include <gamemath/math3d.h>

namespace yaul {

fix16_mat33
fix16_mat33::look_at(const fix16_vec3 &from, const fix16_vec3 &to,
    const fix16_vec3 &up)
{
    fix16_mat33 result;

    lookat_t lookat;
    lookat.from = from.as_fix16_vec3_t();
    lookat.to = to.as_fix16_vec3_t();
    lookat.up = up.as_fix16_vec3_t();
    lookat.basis_right = result.row[0].as_fix16_vec3_t();
    lookat.basis_up = result.row[1].as_fix16_vec3_t();
    lookat.basis_forward = result.row[2].as_fix16_vec3_t();

    math3d_lookat(&lookat);
    return result;
}

} // namespace yaul
