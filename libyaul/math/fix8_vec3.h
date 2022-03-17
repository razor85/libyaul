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

#define FIX8_VEC3_INITIALIZER(x, y, z)                                        \
    {                                                                         \
            {                                                                 \
                    FIX8(x),                                                  \
                    FIX8(y),                                                  \
                    FIX8(z)                                                   \
            }                                                                 \
    }

// TODO: Romulo - align on 4 bytes? Don't think so.
typedef union fix8_vec3 {
        struct {
                fix8_t x;
                fix8_t y;
                fix8_t z;
        };

        fix8_t comp[3];
} __packed fix8_vec3_t;

static inline void __always_inline
fix8_vec3_zero(fix8_vec3_t *result)
{
        result->x = FIX8(0.0f);
        result->y = FIX8(0.0f);
        result->z = FIX8(0.0f);
}

static inline void __always_inline
fix8_vec3_set(fix8_vec3_t *result, fix8_t x, fix8_t y, fix8_t z)
{
        result->x = x;
        result->y = y;
        result->z = z;
}

static inline void __always_inline
fix8_vec3_dup(const fix8_vec3_t * __restrict v0,
    fix8_vec3_t * __restrict result)
{
        result->x = v0->x;
        result->y = v0->y;
        result->z = v0->z;
}

static inline void __always_inline
fix8_vec3_add(const fix8_vec3_t * __restrict v0,
    const fix8_vec3_t * __restrict v1, fix8_vec3_t * __restrict result)
{
        result->x = v0->x + v1->x;
        result->y = v0->y + v1->y;
        result->z = v0->z + v1->z;
}

static inline void __always_inline
fix8_vec3_sub(const fix8_vec3_t * __restrict v1,
    const fix8_vec3_t * __restrict const v0, fix8_vec3_t * __restrict const result)
{
        result->x = v1->x - v0->x;
        result->y = v1->y - v0->y;
        result->z = v1->z - v0->z;
}

static inline void __always_inline
fix8_vec3_scale(const fix8_t scalar, fix8_vec3_t *result)
{
        result->x = fix8_mul(scalar, result->x);
        result->y = fix8_mul(scalar, result->y);
        result->z = fix8_mul(scalar, result->z);
}

static inline void __always_inline
fix8_vec3_scaled(const fix8_t scalar, const fix8_vec3_t * __restrict v,
    fix8_vec3_t * __restrict result)
{
        result->x = fix8_mul(scalar, v->x);
        result->y = fix8_mul(scalar, v->y);
        result->z = fix8_mul(scalar, v->z);
}

static inline fix8_t __always_inline
fix8_vec3_inline_dot(const fix8_vec3_t *a, const fix8_vec3_t *b)
{
        register uint32_t aux;

        __asm__ volatile ("\tclrmac\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tsts macl, %[aux]\n"
                          "\tshal %[aux]\n"
                          "\tshlr8 %[aux]\n"
            : [a] "+r" (a),
              [b] "+r" (b),
              [aux] "=&r" (aux)
            : "m" (*a),
              "m" (*b)
            : "macl", "memory");

        return (fix8_t)(aux & 0xFFFF);
}

static inline fix8_32_t __always_inline
fix8_32_vec3_inline_dot_precise(const fix8_vec3_t *a, const fix8_vec3_t *b)
{
        register uint32_t aux;

        __asm__ volatile ("\tclrmac\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tmac.w @%[a]+, @%[b]+\n"
                          "\tsts macl, %[aux]\n"
                          "\tshal %[aux]\n"
                          "\tshlr8 %[aux]\n"
            : [a] "+r" (a),
              [b] "+r" (b),
              [aux] "=&r" (aux)
            : "m" (*a),
              "m" (*b)
            : "macl", "memory");

        return aux;
}

extern fix8_t fix8_vec3_length(const fix8_vec3_t *);
extern fix8_t fix8_vec3_length_precise(const fix8_vec3_t *);
extern fix8_32_t fix8_32_vec3_length_precise(const fix8_vec3_t *);
extern fix8_t fix8_vec3_sqr_length(const fix8_vec3_t *);
extern fix8_32_t fix8_32_vec3_sqr_length(const fix8_vec3_t *);
extern void fix8_vec3_normalize(fix8_vec3_t *);
extern void fix8_vec3_normalize_precise(fix8_vec3_t *);
extern void fix8_vec3_normalized(const fix8_vec3_t * __restrict,
    fix8_vec3_t * __restrict);
extern void fix8_vec3_normalized_precise(const fix8_vec3_t * __restrict,
    fix8_vec3_t * __restrict);
extern fix8_t fix8_vec3_dot(const fix8_vec3_t *, const fix8_vec3_t *);
extern fix8_t fix8_vec3_dot_precise(const fix8_vec3_t *, const fix8_vec3_t *);
extern fix8_32_t fix8_32_vec3_dot_precise(const fix8_vec3_t *, const fix8_vec3_t *);
extern void fix8_vec3_cross(const fix8_vec3_t * const __restrict,
    const fix8_vec3_t * const __restrict, fix8_vec3_t * __restrict);

extern fix8_t fix8_vec3_cross_mag(const fix8_vec3_t * __restrict,
    const fix8_vec3_t * __restrict);

extern uint32_t fix8_vec3_str(const fix8_vec3_t *, char *, int);
