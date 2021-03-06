/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <vdp2/scrn.h>

#include <assert.h>

#include "vdp2-internal.h"

void
vdp2_scrn_reduction_y_set(uint8_t scrn, q0_3_8_t scale)
{
#ifdef DEBUG
        /* Check if the background passed is valid */
        assert((scrn == SCRN_NBG0) ||
               (scrn == SCRN_NBG1));
#endif /* DEBUG */

        switch (scrn) {
        case SCRN_NBG0:
                vdp2_state.buffered_regs.zmyin0 = Q0_3_8_INT(scale);
                vdp2_state.buffered_regs.zmydn0 = Q0_3_8_FRAC(scale) << 8;
                break;
        case SCRN_NBG1:
                vdp2_state.buffered_regs.zmyin1 = Q0_3_8_INT(scale);
                vdp2_state.buffered_regs.zmydn1 = Q0_3_8_FRAC(scale) << 8;
                break;
        default:
                return;
        }
}
