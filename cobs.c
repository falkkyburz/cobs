/** @file cobs.c
 *
 * @author Falk Kyburz
 * @brief Consistent Overhead Byte Stuffing library
 *
 */

/*==============================================================================
 INCLUDES
 =============================================================================*/
#include "cobs.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/*==============================================================================
 PRIVATE DEFINES
 =============================================================================*/
#define COBS_BLOCK_SIZE (255U)
#define COBS_FRAME_END (0U)

/*==============================================================================
 PUBLIC FUNCTIONS
 =============================================================================*/

size_t cobs_encode(const void *vp_in, size_t s_in_size,
                   uint8_t *u8p_out, size_t s_out_size)
{
    assert(vp_in && u8p_out);

    const uint8_t *u8p_in = (const uint8_t *)vp_in;    // Input data pointer
    const uint8_t *u8p_in_end = u8p_in + s_in_size;    // Input end pointer
    const uint8_t *u8p_out_end = u8p_out + s_out_size; // Output end pointer
    const uint8_t *u8p_out_start = u8p_out;            // Output start pointer
    uint8_t *u8p_out_code = u8p_out;                   // Code byte pointer
    size_t ret = 0;                                    // Return value

    for (u8p_out++; u8p_out < u8p_out_end; u8p_out++)
    {
        if (u8p_in < u8p_in_end)
        {
            /* Frame ongoing */
            if ((u8p_out - u8p_out_code) < COBS_BLOCK_SIZE)
            {
                /* Encode data. */
                if (*u8p_in == 0)
                {
                    /* Encode zero. */
                    *u8p_out_code = u8p_out - u8p_out_code;
                    u8p_out_code = u8p_out;
                }
                else
                {
                    /* Encode non-zero byte. */
                    *u8p_out = *u8p_in;
                }
                u8p_in++;
            }
            else
            {
                /* Encode end of block. */
                *u8p_out_code = COBS_BLOCK_SIZE;
                u8p_out_code = u8p_out;
            }
        }
        else
        {
            /* Frame End */
            *u8p_out_code = u8p_out - u8p_out_code;
            u8p_out_code = u8p_out;
            *u8p_out_code = COBS_FRAME_END;
            u8p_out++;
            break;
        }
    }
    /* Diangostics */
    if ((u8p_in == u8p_in_end) && (*u8p_out_code == COBS_FRAME_END))
    {
        /* Verify that all data was encoded and the frame end was written. */
        ret = (size_t)(u8p_out - u8p_out_start);
    }

    return ret;
}

size_t cobs_decode(const uint8_t *u8p_in, size_t s_in_size,
                   void *vp_out, size_t s_out_size)
{
    assert(u8p_in && vp_out);

    uint8_t *u8p_out = (uint8_t *)vp_out;              // Output data pointer
    const uint8_t *u8p_in_end = u8p_in + s_in_size;    // Input end pointer
    const uint8_t *u8p_out_end = u8p_out + s_out_size; // Input end pointer
    const uint8_t *u8p_out_start = u8p_out;            // Output start pointer
    const uint8_t *u8p_in_code = u8p_in + *u8p_in;     // Code byte pointer
    uint8_t u8_in_code_mem = *u8p_in;                  // Last code
    size_t ret = 0;                                    // Return value

    for (u8p_in++; u8p_in < u8p_in_end; u8p_in++)
    {
        if ((*u8p_in != COBS_FRAME_END) && (u8p_out < u8p_out_end))
        {
            /* Frame ongoing */
            if ((u8p_in == u8p_in_code) && (*u8p_in_code != COBS_FRAME_END))
            {
                /* Decode code byte. */
                if (u8_in_code_mem != COBS_BLOCK_SIZE)
                {
                    /* Decode zero byte. */
                    *u8p_out = 0;
                    u8p_out++;
                }
                u8p_in_code = u8p_in + *u8p_in;
                u8_in_code_mem = *u8p_in;
            }
            else
            {
                /* Decode non-zero byte. */
                *u8p_out = *u8p_in;
                u8p_out++;
            }
        }
        else
        {
            /* Frame End */
            u8_in_code_mem = *u8p_in;
            u8p_in++;
            break;
        }
    }
    /* Diangostics */
    if ((u8p_in == u8p_in_end) && (u8_in_code_mem == COBS_FRAME_END))
    {
        /* Verify that all data was decoded and the last byte was 0 */
        ret = (size_t)(u8p_out - u8p_out_start);
    }
    return ret;
}

/*
 * @copyright
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source u8_code form or as a compiled
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
