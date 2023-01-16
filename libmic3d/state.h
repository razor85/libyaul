#ifndef _MIC3D_STATE_H_
#define _MIC3D_STATE_H_

#include <fix16.h>
#include <mat_stack.h>

#include "mic3d.h"

typedef struct render render_t;
typedef struct sort sort_t;
typedef struct tlist tlist_t;
typedef struct light light_t;
typedef struct gst gst_t;

typedef struct perf perf_t;

typedef struct {
        render_t *render;
        sort_t *sort;
        tlist_t *tlist;
        mat_stack_t *mat_stack;
        light_t *light;
        gst_t *gst;
        perf_t *perf;
} state_t;

extern state_t __state;

#endif /* _MIC3D_STATE_H_ */
