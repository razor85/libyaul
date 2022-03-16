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

#define FIX8_VEC2_INITIALIZER(x, y)                                           \
    {                                                                         \
            {                                                                 \
                    FIX8(x),                                                  \
                    FIX8(y)                                                   \
            }                                                                 \
    }

typedef union fix8_vec2 {
        struct {
                fix8_t x;
                fix8_t y;
        };

        fix8_t comp[2];
} __packed __aligned(4) fix8_vec2_t;

static inline void __always_inline
fix8_vec2_zero(fix8_vec2_t *result)
{
        result->x = FIX8(0.0f);
        result->y = FIX8(0.0f);
}

static inline void __always_inline
fix8_vec2_dup(const fix8_vec2_t * __restrict v0,
    fix8_vec2_t * __restrict result)
{
        result->x = v0->x;
        result->y = v0->y;
}

static inline void __always_inline
fix8_vec2_add(const fix8_vec2_t * __restrict v0,
    const fix8_vec2_t * __restrict v1, fix8_vec2_t * __restrict result)
{
        result->x = v0->x + v1->x;
        result->y = v0->y + v1->y;
}

static inline void __always_inline
fix8_vec2_sub(const fix8_vec2_t * __restrict v0,
    const fix8_vec2_t * __restrict v1, fix8_vec2_t * __restrict result)
{
        result->x = v0->x - v1->x;
        result->y = v0->y - v1->y;
}

static inline void __always_inline
fix8_vec2_scale(const fix8_t scalar, fix8_vec2_t *result)
{
        result->x = fix8_mul(scalar, result->x);
        result->y = fix8_mul(scalar, result->y);
}

static inline void __always_inline
fix8_vec2_scaled(const fix8_t scalar, const fix8_vec2_t * __restrict v0,
    fix8_vec2_t * __restrict result)
{
        result->x = fix8_mul(scalar, v0->x);
        result->y = fix8_mul(scalar, v0->y);
}

static inline fix8_t __always_inline
fix8_vec2_inline_dot(const fix8_vec2_t *a, const fix8_vec2_t *b)
{
        register uint32_t aux0;

        __asm__ volatile ("\tclrmac\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tsts macl, %[aux0]\n"
                          "\tshal %[aux0]\n"
                          "\tshlr8 %[aux0]\n"
            : [a] "+r" (a),
              [b] "+r" (b),
              [aux0] "=&r" (aux0)
            : "m" (*a),
              "m" (*b)
            : "macl", "memory");

        return (fix8_t)(aux0 & 0xFFFF);
}

static inline fix8_32_t __always_inline
fix8_vec2_inline_dot_precise(const fix8_vec2_t *a, const fix8_vec2_t *b)
{
        register uint32_t aux0;

        __asm__ volatile ("\tclrmac\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tsts macl, %[aux0]\n"
                          "\tshal %[aux0]\n"
                          "\tshlr8 %[aux0]\n"
            : [a] "+r" (a),
              [b] "+r" (b),
              [aux0] "=&r" (aux0)
            : "m" (*a),
              "m" (*b)
            : "macl", "memory");

        return aux0;
}

extern fix8_t fix8_vec2_length(const fix8_vec2_t *);
extern fix8_t fix8_vec2_length_precise(const fix8_vec2_t *);
extern fix8_t fix8_vec2_sqr_length(const fix8_vec2_t *);
extern void fix8_vec2_normalize(fix8_vec2_t *);
extern void fix8_vec2_normalize_precise(fix8_vec2_t *);
extern void fix8_vec2_normalized(const fix8_vec2_t * __restrict, fix8_vec2_t * __restrict);
extern void fix8_vec2_normalized_precise(const fix8_vec2_t * __restrict, fix8_vec2_t * __restrict);
extern fix8_t fix8_vec2_dot(const fix8_vec2_t *, const fix8_vec2_t *);
extern fix8_32_t fix8_vec2_dot_precise(const fix8_vec2_t *, const fix8_vec2_t *);
extern void fix8_vec2_str(const fix8_vec2_t *, char *, int);
