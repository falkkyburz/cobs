/** @file cobs.h
 *
 * @author Falk Kyburz
 * @brief Consistent Overhead Byte Stuffing library
 *
 */

#ifndef COBS_H
#define COBS_H

/*==============================================================================
 INCLUDES
 =============================================================================*/
#include <stdint.h>

/*==============================================================================
 DEFINES
 =============================================================================*/
#define COBS_ENCODE_OUT_SIZE_MIN(IN_SIZE) \
    (((IN_SIZE) == 0U) ? 2U : (IN_SIZE) + 2U + (IN_SIZE) / 256U)
#define COBS_DECODE_OUT_SIZE_MIN(IN_SIZE) \
    (((IN_SIZE) < 3U) ? 0u : (IN_SIZE)-2U)

/*==============================================================================
 PUBLIC FUNCTIONS
 =============================================================================*/

/**
 * @brief COBS encode data to buffer
 * @param vp_in Pointer to input data to encode
 * @param s_in_size Size of input data
 * @param u8p_out Pointer to encoded output buffer
 * @param s_out_size Size of output data
 * @return Encoded buffer size in bytes
 * @note Returns zero if not all data was encoded.
 */
size_t cobs_encode(const void *vp_in, size_t s_in_size,
                   uint8_t *u8p_out, size_t s_out_size);

/**
 * @brief COBS decode data from buffer
 * @param u8p_in Pointer to encoded input bytes
 * @param s_in_size Size of input data
 * @param vp_out Pointer to encoded output buffer
 * @param s_out_size Size of output data
 * @return Number of bytes successfully decoded
 * @note Returns zero if not all data was decoded.
 */
size_t cobs_decode(const uint8_t *u8p_in, size_t s_in_size,
                   void *vp_out, size_t s_out_size);

#endif /* COBS_H */

/*
 * @copyright
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <https://unlicense.org>
 */
