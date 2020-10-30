/*
 * Copyright (c) 2012-2019 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Romulo Fernandes Machado <abra185@gmail.com>
 */

#include <cd-block.h>

#include <cpu/instructions.h>

#include <smpc/smc.h>

#include "cd-block-internal.h"

#define ISO9660_SECTOR_SIZE 2048
#define CD_STATUS_TIMEOUT 0xAA

#ifndef MIN
#define MIN(X,Y) (X < Y ? X : Y)
#endif

#define FAKE_SECTOR_SIZE 2352
#define FAKE_NUM_SECTORS 150

static int
cd_block_get_cd_status_flags(uint8_t *flags)
{
        assert(flags != NULL);

        struct cd_block_status cdStatus;

        int ret;

        if ((ret = cd_block_cmd_get_cd_status(&cdStatus)) != 0) {
                return ret;
        }

        *flags = cdStatus.cdStatus;

        return 0;
}

static int
cd_block_wait_hirq_flag(uint16_t flag)
{
        volatile uint32_t i;

        for (i = 0; i < 0x240000; ++i) {
                if (MEMORY_READ(16, CD_BLOCK(HIRQ)) & flag) {
                        return 0;
                }
        }

        return -1;
}

static int __used
cd_block_auth()
{
        volatile int i;
        struct cd_block_regs regs;
        struct cd_block_regs status;
        uint8_t flags;

        MEMORY_WRITE(16, CD_BLOCK(HIRQ), ~(DCHG | EFLS));

        /* Auth */
        regs.hirq_mask = EFLS;
        regs.cr1 = 0xE000;
        regs.cr2 = 0x0000;
        regs.cr3 = 0x0000;
        regs.cr4 = 0x0000;

        volatile int ret;

        if ((ret = cd_block_cmd_execute(&regs, &status)) != 0) {
                return ret;
        }

        while ((MEMORY_READ(16, CD_BLOCK(HIRQ)) & EFLS) == 0) {
        }

        /* Wait for initial seeking */
        while (true) {
                for (i = 0; i < 131072; ++i) {
                        cpu_instr_nop();
                }

                if ((ret = cd_block_get_cd_status_flags(&flags)) != 0) {
                        return ret;
                }

                if (flags == CD_STATUS_PAUSE) {
                        return 0;
                }

                if (flags == CD_STATUS_FATAL) {
                        return -CD_STATUS_FATAL;
                }

                if (flags == CD_STATUS_REJECT) {
                        return -CD_STATUS_REJECT;
                }
        }

        return 0;
}

int
cd_block_init(int16_t standby)
{
        int ret;

        /* Wait for ESEL */
        while ((MEMORY_READ(16, CD_BLOCK(HIRQ)) & CMOK) == 0) {
        }

        if ((ret = cd_block_cmd_abort_file()) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_init_cd_system(standby)) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_end_data_transfer()) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_reset_selector(0xFC, 0)) != 0) {
                return ret;
        }

        /* Wait for ESEL */
        while ((MEMORY_READ(16, CD_BLOCK(HIRQ)) & ESEL) == 0) {
        }

        // Bypass Auth.
        // if ((ret = cd_block_auth()) != 0)
        //         return ret;

        return 0;
}

int
cd_move_sector_data_cd_auth(uint8_t dstFilter, uint16_t sectorPos,
    uint8_t selNum, uint16_t numSectors)
{
        int i;
        int ret;
        struct cd_block_status cdStatus;
        uint16_t isAuthenticated;

        cd_block_cmd_move_sector_data(dstFilter, sectorPos, selNum,
                                      numSectors);

        // Clear hirq flags
        MEMORY_WRITE(16, CD_BLOCK(HIRQ), ~(DCHG | EFLS));

        // Authenticate disc
        if ((ret = cd_block_cmd_auth_disk()) != 0) {
                return ret;
        }

        // Wait till operation is finished
        while ((MEMORY_READ(16, CD_BLOCK(HIRQ)) & EFLS) == 0)
                ;

        // Wait until drive has finished seeking
        for (;;) {
                // Wait a bit
                for (i = 0; i < 100000; i++)
                        ;

                if (cd_block_cmd_get_cd_status(&cdStatus) != 0) {
                        continue;
                }

                if (cdStatus.cdStatus == CD_STATUS_PAUSE) {
                        break;
                } else if (cdStatus.cdStatus == CD_STATUS_FATAL) {
                        return -CD_STATUS_FATAL;
                }
        }

        // Was Authentication successful?
        if (cd_block_cmd_is_auth(&isAuthenticated) == 0) {
                return -1;
        }

        return 0;
}

int
cd_block_bypass_copy_protection()
{
        int i, j, ret;
        struct cd_block_regs regs __unused;
        struct cd_block_regs status __unused;

        if ((ret = cd_block_cmd_set_sector_length(SECTOR_LENGTH_2352)) != 0) {
                return ret;
        }

        // Write 150 x 2353 sectors.
        if ((ret = cd_block_cmd_put_sector_data(0, 150)) != 0) {
                return ret;
        }

        for (j = 0; j < 150; ++j) {
                for (i = 0; i < (2352 / 4); i += 4) {
                        MEMORY_WRITE(32, CD_BLOCK(DTR), 0x00020002);
                }
        }

        if ((ret = cd_block_cmd_end_data_transfer()) != 0) {
                return ret;
        }

        while ((MEMORY_READ(16, CD_BLOCK(HIRQ)) & EHST) == 0)
                ;

        cd_move_sector_data_cd_auth(0, 0, 0, 50);

        cd_block_cmd_is_auth(NULL);

        while (MEMORY_READ(16, CD_BLOCK(HIRQ) & ECPY) == 0)
                ;

        if ((ret = cd_block_cmd_end_data_transfer()) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_set_sector_length(SECTOR_LENGTH_2048)) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_reset_selector(0xFC, 0)) != 0) {
                return ret;
        }

        return 0;
}

int
cd_block_data_transfer(uint16_t offset, uint16_t buffer_number, uint8_t *output_buffer)
{
        assert(output_buffer != NULL);

        /* Start transfer */
        int ret;
        ret = cd_block_cmd_get_then_delete_sector_data(offset, buffer_number, 1);
        if (ret != 0) {
                return ret;
        }

        /* Wait for data */
        if ((cd_block_wait_hirq_flag(DRDY | EHST)) != 0) {
                return CD_STATUS_TIMEOUT;
        }

        /* Transfer from register to user space */
        uint16_t *read_buffer;
        read_buffer = (uint16_t *)output_buffer;

        for (uint32_t i = 0; i < (ISO9660_SECTOR_SIZE / 2); i++) {
                *read_buffer = MEMORY_READ(16, CD_BLOCK(DTR));
                read_buffer++;
        }

        if ((ret = cd_block_cmd_end_data_transfer()) != 0) {
                return ret;
        }

        return 0;
}

int
cd_block_sector_read(uint32_t fad, uint8_t *output_buffer)
{
        const int32_t num_sectors = 1;

        assert(output_buffer != NULL);
        assert(fad >= 150);

        int ret;

        if ((ret = cd_block_cmd_set_sector_length(SECTOR_LENGTH_2048)) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_reset_selector(0, 0)) != 0) {
                return ret;
        }

        if ((ret = cd_block_cmd_set_cd_device_connection(0)) != 0) {
                return ret;
        }

        /* Start reading */
        if ((ret = cd_block_cmd_play_disk(0, fad, num_sectors)) != 0) {
                return ret;
        }

        /* If at least one sector has transferred, we copy it */
        while ((cd_block_cmd_get_sector_number(0)) == 0) {
        }

        if ((ret = cd_block_data_transfer(0, 0, output_buffer)) != 0) {
                return ret;
        }

        return 0;
}

