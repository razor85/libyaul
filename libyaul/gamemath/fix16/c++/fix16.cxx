/*-
 * Copyright (c) Authors of libfixmath
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

#include <assert.h>

#include <cpu/divu.h>
#include <gamemath/angle.h>
#include <gamemath/fix16.h>
#include <stdbool.h>

namespace yaul {

angle
fix16::rad_to_angle() const
{
    constexpr fix16 OneOver2Pi { FIX16(1.0 / (2.0 * M_PI)) };
    return angle { static_cast<::angle_t>((*this * OneOver2Pi).value) };
}

angle
fix16::deg_to_angle() const
{
    constexpr fix16 OneOver2Pi { FIX16(1.0 / (2.0 * M_PI)) };
    return angle { static_cast<::angle_t>((deg_to_rad() * OneOver2Pi).value) };
}

} // namespace yaul