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

/**
 * @file
 * @defgroup libtga libtga
 * @brief Basic library to parse Truevision TGA (TARGA) files */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup libtga
 * @brief Basic library to parse Truevision TGA (TARGA) files
 * @{ */

/**
 * @enum tga_status TGA Status */
typedef enum {
        TGA_OP_SUCCESS = 0, /**< TGA operation was successful */
        TGA_OP_FAILURE = -1, /**< TGA unknown operation failure */
        TGA_FILE_UNKNOWN_FORMAT = -2, /**< TGA header could not be parsed in file */
        TGA_FILE_CORRUPTED = -3, /**< TGA header is corrupted in file */
        TGA_FILE_NOT_SUPPORTED = -4, /**< TGA feature is unsupported in file*/
        TGA_MEMORY_ERROR = -5, /**< TGA memory error (ran out of memory) */
        TGA_MEMORY_UNALIGNMENT_ERROR = -6 /**< TGA address is unaligned (not on a 2 or 4-byte boundary) */
} tga_status;

/**
 * @brief TGA state */
typedef struct {
        const void *tga_context; /**< Context opaque pointer */

        /**
         * @brief User modifiable options
         *
         * The options must be set prior to calling tga_read() */
         */
        struct {
                uint32_t transparent_pixel; /**< Determine the transparent pixel color (in RGB 555) */
                bool msb; /**< Enable setting MSB bit for transparent pixel color */
        } tga_options;
} tga;

/**
 * @brief Read TGA from a file buffer.
 *
 * Parses buffer and allocates a private TGA context.
 *
 * @param tga TGA state pointer
 * @param file Read-only pointer to TGA file buffer
 *
 * @return @ref tga_status.TGA_OP_SUCCESS if reading TGA file buffer was
 *         successful.
 * @return @ref tga_status.TGA_FILE_CORRUPTED if TGA header is corrupted.
 * @return @ref tga_status.TGA_FILE_NOT_SUPPORTED if a feature set in the TGA is
 *         not supported.
 */
tga_status tga_read(tga *tga, const uint8_t *file);

/**
 * @brief Decode image as a tiles (cells) and write each tile sequentially to memory.
 *
 * @note
 *   - Function tga_read() must be called prior to calling this function.
 *   - The image dimensions must be multiples of 8 as the Saturn's smallest tile (cell) dimension is 8x8 pixels.
 *   - The pointer destination can point to another buffer or VDP1/VDP2 VRAM.
 *
 * @details The entire image buffer parsed from the TGA file buffer is subdivided into
 * cells and sequentially written to memory, starting from the top-left corner
 * of the image buffer.
 *
 * @param tga TGA state pointer
 * @param dst Pointer to buffer to write to
 *
 * @return @ref tga_status.TGA_OP_SUCCESS if reading TGA file buffer was
 *         successful.
 * @return @ref tga_status.TGA_FILE_CORRUPTED if TGA header is corrupted.
 * @return @ref tga_status.TGA_FILE_NOT_SUPPORTED if a feature set in the TGA is
 *         not supported.
 */
tga_status tga_image_decode_tiled(const tga *tga, void *dst);

/**
 * @brief Decode image and write raw buffer of color pixels to memory.
 *
 * @note
 *   - Function tga_read() must be called prior to calling this function.
 *   - The pointer destination can point to another buffer or VDP1/VDP2 VRAM.
 *
 * @details The entire image is treated as a bitmap. Specifically, each pixel
 * (whether indexed or RGB) is sequentially written to memory.
 *
 * @param tga TGA state pointer
 * @param dst Pointer to buffer to write to
 *
 * @return @ref tga_status.TGA_OP_SUCCESS if reading TGA file buffer was
 *         successful.
 * @return @ref tga_status.TGA_FILE_CORRUPTED if TGA header is corrupted.
 * @return @ref tga_status.TGA_FILE_NOT_SUPPORTED if a feature set in the TGA is
 *         not supported.
 */
tga_status tga_image_decode(const tga *tga, void *dst);

/**
 * @brief Decode color map (palette) and write to memory.
 *
 * @note
 *   - Function tga_read() must be called prior to calling this function.
 *   - The pointer destination can point to another buffer, CRAM, or VDP1 VRAM.
 *
 * @details The color map (palette) is extracted from the TGA file buffer in is
 * converted from BGR16 to RGB 555.
 *
 * Depending on what options were set in @ref tga.tga_options, the MSB of each
 * color may or may not be set.
 *
 * @param tga TGA state pointer
 * @param dst Pointer to buffer to write to
 *
 * @return @ref tga_status.TGA_OP_SUCCESS if reading TGA file buffer was
 *         successful.
 * @return @ref tga_status.TGA_FILE_CORRUPTED if TGA header is corrupted.
 * @return @ref tga_status.TGA_FILE_NOT_SUPPORTED if a feature set in the TGA is
 *         not supported.
 */
tga_status tga_cmap_decode(const tga *tga, uint16_t *dst);

/**
 * @brief Convert TGA status (@ref tga_status) to a string.
 *
 * @param status Status value from @ref tga_status
 *
 * @return Read-only string equivalent of @ref tga_status member
 */
const char *tga_error_stringify(tga_status status);

/**
 * @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TGA_H_ */
