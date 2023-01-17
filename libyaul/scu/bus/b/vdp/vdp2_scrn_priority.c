/*
 * Copyright (c) 2012-2019 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <vdp2/scrn.h>

#include "vdp-internal.h"

void
vdp2_scrn_priority_set(vdp2_scrn_t scroll_screen, uint8_t priority)
{
        /* When priority is zero, scroll screen is transparent */
        priority &= 0x07;

        switch (scroll_screen) {
        case VDP2_SCRN_NBG0:
                _state_vdp2()->shadow_regs.prina &= 0xFFF8;
                _state_vdp2()->shadow_regs.prina |= priority;
                break;
        case VDP2_SCRN_NBG1:
                _state_vdp2()->shadow_regs.prina &= 0xF8FF;
                _state_vdp2()->shadow_regs.prina |= priority << 8;
                break;
        case VDP2_SCRN_NBG2:
                _state_vdp2()->shadow_regs.prinb &= 0xFFF8;
                _state_vdp2()->shadow_regs.prinb |= priority;
                break;
        case VDP2_SCRN_NBG3:
                _state_vdp2()->shadow_regs.prinb &= 0xF8FF;
                _state_vdp2()->shadow_regs.prinb |= priority << 8;
                break;
        case VDP2_SCRN_RBG0:
                _state_vdp2()->shadow_regs.prir &= 0xFFF8;
                _state_vdp2()->shadow_regs.prir |= priority;
                break;
        default:
                return;
        }
}

uint8_t
vdp2_scrn_priority_get(vdp2_scrn_t scroll_screen)
{
        switch (scroll_screen) {
        case VDP2_SCRN_NBG0:
                return _state_vdp2()->shadow_regs.prina & 0x0007;
        case VDP2_SCRN_NBG1:
                return (_state_vdp2()->shadow_regs.prina & 0x0700) >> 8;
        case VDP2_SCRN_NBG2:
                return _state_vdp2()->shadow_regs.prinb & 0x0007;
        case VDP2_SCRN_NBG3:
                return (_state_vdp2()->shadow_regs.prinb & 0x0700) >> 8;
        case VDP2_SCRN_RBG0:
        case VDP2_SCRN_RBG0_PA:
        case VDP2_SCRN_RBG0_PB:
                return _state_vdp2()->shadow_regs.prir & 0x0007;
        default:
                return -1;
        }
}
