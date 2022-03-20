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

#define FIX8_LUT_SIN_TABLE_COUNT       (2048)
#define FIX8_LUT_SIN_TABLE_MASK        (FIX8_LUT_SIN_TABLE_COUNT - 1)
#define FIX8_LUT_ATAN_TABLE_COUNT      (256)

extern fix8_t fix8_sin(fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_cos(fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_tan(fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_tan_precise(fix8_t) FIXMATH_FUNC_ATTRS;
extern fix8_t fix8_atan2(fix8_t y, fix8_t x) FIXMATH_FUNC_ATTRS;
