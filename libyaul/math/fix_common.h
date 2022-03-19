/*-
 * Copyright (c) Romulo Fernandes
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _YAUL_MATH_FIX_COMMON_H_
#define _YAUL_MATH_FIX_COMMON_H_

#include "fix8.h"
#include "fix16.h"

__BEGIN_DECLS

/// @addtogroup MATH
/// @{

#define FIXMATH_FUNC_ATTRS __attribute__ ((leaf, nothrow, const))

static inline fix8_t __always_inline
fix8_fix16_from(const fix16_t value)
{
        return value >> 8;
}

static inline fix16_t __always_inline
fix8_fix16_to(const fix8_t value)
{
        return ((fix16_t)value) << 8;
}

#undef FIXMATH_FUNC_ATTRS

/// @}

__END_DECLS

#endif /* !_YAUL_MATH_FIX_COMMON_H_ */
