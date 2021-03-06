/*
 * Copyright (c) 2012-2016
 * See LICENSE for details.
 *
 * Anders Montonen 
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <usb-cartridge.h>

#include "usb-cartridge-internal.h"

#define USB_TXE         0x02

void
usb_cartridge_byte_send(uint8_t c)
{

        while ((MEMORY_READ(8, USB_CARTRIDGE(FLAG)) & USB_TXE) == USB_TXE);
        MEMORY_WRITE(8, USB_CARTRIDGE(FIFO), c);
}
