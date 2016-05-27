/*
 * Copyright (c) 2013, 2014-2016
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef TGA_H_
#define TGA_H_

#include <stdio.h>
#include <inttypes.h>

/** @file */
/** @defgroup libtga libtga */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup libtga
 * @brief Basic library to parse Truevision TGA (TARGA) files
 *
 * @{ */

/**
 * @enum tga_status Status
 * @brief TGA status */
typedef enum {
        TGA_FILE_OK, /**< Success */
        TGA_FILE_UNKNOWN_FORMAT, /**< TGA header could not be parsed */
        TGA_FILE_CORRUPTED, /**< TGA header is corrupted */
        TGA_FILE_NOT_SUPPORTED, /**< TGA feature is unsupported */
        TGA_MEMORY_ERROR, /**< TGA memory error */
        TGA_MEMORY_UNALIGNMENT_ERROR /**< TGA address is unaligned (not on a 2 or 4-byte boundary) */
} tga_status;

/**
 * @brief TGA */
typedef struct {
        const void *tga_context; /**< Context */

        /**
         * @brief User modifiable options */
        struct {
                uint32_t transparent_pixel; /**< Determine the transparent pixel color (in RGB555) */
                bool msb; /**< Enable setting MSB bit for transparent pixel color */
        } tga_options;
} tga;

/**
 * @brief Read a valid TGA from a buffer.
 *
 * @param[in] tga TGA opaque pointer
 * @param[in] file Read-only pointer to TGA file buffer
 */
tga_status tga_read(tga *tga, const uint8_t *file);

/**
 * @brief Decode image as a tiles and write each tile sequentially to memory.
 *
 * @param[in] tga TGA opaque pointer
 * @param[out] dst Pointer to buffer to write to
 */
tga_status tga_image_decode_tiled(const tga *tga, void *dst);

/**
 * @brief Decode image and write raw buffer of color pixels to memory.
 *
 * @param[in] tga TGA opaque pointer
 * @param[out] dst Pointer to buffer to write to
 */
tga_status tga_image_decode(const tga *tga, void *dst);

/**
 * @brief Decode color map (palette) and write to memory.
 *
 * @param[in] tga TGA opaque pointer
 * @param[out] dst Pointer to buffer to write to
 *
 * @return Status
 */
tga_status tga_cmap_decode(const tga *tga, uint16_t *dst);

/**
 * @brief Convert TGA status (@ref tga_status) to a string.
 *
 * @param[in] status Status value from @ref tga_status
 *
 * @return Read-only string equivalent of @ref tga_status member
 */
const char *tga_error_stringify(tga_status status);
/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TGA_H_ */
