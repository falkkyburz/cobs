/** @file cc_test.c
 *
 * @author Falk Kyburz
 * @brief Tests for CC.
 *
 *
 * Example	Unencoded data (hex)	Encoded with COBS (hex)
 * 1	00	                        01 01 00
 * 2	00 00	                    01 01 01 00
 * 3	00 11 00	                01 02 11 01 00
 * 4	11 22 00 33	                03 11 22 02 33 00
 * 5	11 22 33 44	                05 11 22 33 44 00
 * 6	11 00 00 00	                02 11 01 01 01 00
 * 7	01 02 03 ... FD FE	        FF 01 02 03 ... FD FE 00
 * 8	00 01 02 ... FC FD FE	    01 FF 01 02 ... FC FD FE 00
 * 9	01 02 03 ... FD FE FF	    FF 01 02 03 ... FD FE 02 FF 00
 * 10	02 03 04 ... FE FF 00	    FF 02 03 04 ... FE FF 01 01 00
 * 11	03 04 05 ... FF 00 01	    FE 03 04 05 ... FF 02 01 00
 *
 */

#include "cobs.h"

#include <stdio.h>
#include <string.h>

#include "utest.h"

/*==============================================================================
 HELPER FUNCTIONS
 =============================================================================*/

void memprint(void *mem, size_t size, size_t offset)
{
    for (int i = offset; i < size + offset; i++)
    {
        if (i % 32 == 0)
        {
            printf("\n");
        }
        printf("0x%02X ", ((uint8_t *)mem)[i]);
    }
    printf("\n");
}

/*==============================================================================
 TEST FUNCTIONS
 =============================================================================*/
UTEST(cobs, example_1)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];

    uint8_t u8a_data[] = {0x00};
    uint8_t u8a_code[] = {0x01, 0x01, 0x00};

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_2)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];

    uint8_t u8a_data[] = {0x00, 0x00};
    uint8_t u8a_code[] = {0x01, 0x01, 0x01, 0x00};

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_3)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[] = {0x00, 0x11, 0x00};
    uint8_t u8a_code[] = {0x01, 0x02, 0x11, 0x01, 0x00};

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_4)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[] = {0x11, 0x22, 0x00, 0x33};
    uint8_t u8a_code[] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_5)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t u8a_code[] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_6)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[] = {0x11, 0x00, 0x00, 0x00};
    uint8_t u8a_code[] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_7)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[254] = {0};
    uint8_t u8a_code[256] = {0};

    for (int i = 0; i < sizeof(u8a_data); i++)
    {
        u8a_data[i] = i + 1;
    }
    u8a_code[0] = 0xFF;
    for (int i = 1; i < (sizeof(u8a_code) - 1); i++)
    {
        u8a_code[i] = i;
    }

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);

    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_8)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[255] = {0};
    uint8_t u8a_code[257] = {0};

    for (int i = 0; i < sizeof(u8a_data); i++)
    {
        u8a_data[i] = i;
    }
    u8a_code[0] = 0x01;
    u8a_code[1] = 0xFF;
    for (int i = 2; i < (sizeof(u8a_code) - 1); i++)
    {
        u8a_code[i] = i - 1;
    }

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_9)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[255] = {0};
    uint8_t u8a_code[258] = {0};

    for (int i = 0; i < sizeof(u8a_data); i++)
    {
        u8a_data[i] = i + 1;
    }
    u8a_code[0] = 0xFF;
    for (int i = 1; i < (sizeof(u8a_code) - 3); i++)
    {
        u8a_code[i] = i;
    }
    u8a_code[255] = 0x02;
    u8a_code[256] = 0xFF;

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_10)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[255] = {0};
    uint8_t u8a_code[258] = {0};

    for (int i = 0; i < sizeof(u8a_data); i++)
    {
        u8a_data[i] = i + 2;
    }
    u8a_code[0] = 0xFF;
    for (int i = 1; i < (sizeof(u8a_code) - 3); i++)
    {
        u8a_code[i] = i + 1;
    }
    u8a_code[255] = 0x01;
    u8a_code[256] = 0x01;

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, example_11)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[255] = {0};
    uint8_t u8a_code[257] = {0};

    for (int i = 0; i < sizeof(u8a_data); i++)
    {
        u8a_data[i] = i + 3;
    }
    u8a_code[0] = 0xFE;
    for (int i = 1; i < (sizeof(u8a_code) - 3); i++)
    {
        u8a_code[i] = i + 2;
    }
    u8a_code[254] = 0x02;
    u8a_code[255] = 0x01;

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, encode555zeros)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[555] = {0};
    uint8_t u8a_code[557] = {0};

    for (int i = 0; i < (sizeof(u8a_code) - 1); i++)
    {
        u8a_code[i] = 0x01;
    }

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, encode555ones)
{
    uint8_t u8a_data_mem[1024];
    uint8_t u8a_code_mem[1024];
    uint8_t u8a_data_mem_exp[1024];
    uint8_t u8a_code_mem_exp[1024];
    uint8_t u8a_data[555] = {0};
    uint8_t u8a_code[559] = {0};

    memset(u8a_data, 1, sizeof(u8a_data));
    memset(u8a_code, 1, sizeof(u8a_code));
    u8a_code[0] = 255;
    u8a_code[255] = 255;
    u8a_code[510] = 48;
    u8a_code[558] = 0;

    memset(u8a_data_mem, 0xAA, sizeof(u8a_data_mem));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    memcpy(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_data_mem));
    memcpy(u8a_data_mem_exp, u8a_data, sizeof(u8a_data));
    memcpy(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem));
    memcpy(u8a_code_mem_exp, u8a_code, sizeof(u8a_code));

    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(memcmp(u8a_code_mem_exp, u8a_code_mem, sizeof(u8a_code_mem)), 0);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_mem, sizeof(u8a_data)), sizeof(u8a_data));
    EXPECT_EQ(memcmp(u8a_data_mem_exp, u8a_data_mem, sizeof(u8a_code_mem)), 0);
}

UTEST(cobs, encode_out_size65)
{
    uint8_t u8a_data[65] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data))] = {0};
    uint8_t u8a_code_mem[1024];

    memset(u8a_data, 1, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    memset(u8a_data, 0, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < sizeof(u8a_data); i++)
        {
            u8a_data[i] = rand();
        }
        memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
        EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    }
}

UTEST(cobs, encode_out_size256)
{
    uint8_t u8a_data[256] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data))] = {0};
    uint8_t u8a_code_mem[1024];

    memset(u8a_data, 1, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    memset(u8a_data, 0, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code) - 1);
    EXPECT_EQ(u8a_code_mem[sizeof(u8a_code)], 0xBB);
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < sizeof(u8a_data); i++)
        {
            u8a_data[i] = rand();
        }
        memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
        EXPECT_LE(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    }
}

UTEST(cobs, encode_out_size333)
{
    uint8_t u8a_data[333] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data))] = {0};
    uint8_t u8a_code_mem[1024];

    memset(u8a_data, 1, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    memset(u8a_data, 0, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code) - 1);
    EXPECT_EQ(u8a_code_mem[sizeof(u8a_code)], 0xBB);
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < sizeof(u8a_data); i++)
        {
            u8a_data[i] = rand();
        }
        memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
        EXPECT_LE(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    }
}

UTEST(cobs, encode_out_size512)
{
    uint8_t u8a_data[512] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data))] = {0};
    uint8_t u8a_code_mem[1024];

    memset(u8a_data, 1, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    memset(u8a_data, 0, sizeof(u8a_data));
    memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
    EXPECT_EQ(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code) - 2);
    EXPECT_EQ(u8a_code_mem[sizeof(u8a_code) - 1], 0xBB);
    EXPECT_EQ(u8a_code_mem[sizeof(u8a_code)], 0xBB);
    // memprint(u8a_code_mem, sizeof(u8a_code), 0);
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < sizeof(u8a_data); i++)
        {
            u8a_data[i] = rand();
        }
        memset(u8a_code_mem, 0xBB, sizeof(u8a_code_mem));
        EXPECT_LE(cobs_encode(u8a_data, sizeof(u8a_data), u8a_code_mem, sizeof(u8a_code)), sizeof(u8a_code));
    }
}

UTEST(cobs, decode_out_size0)
{
    uint8_t u8a_data_in[65] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data_in))] = {0};
    uint8_t u8a_data_out[COBS_DECODE_OUT_SIZE_MIN(sizeof(u8a_code))] = {0};

    memset(u8a_data_in, 1, sizeof(u8a_data_in));
    memset(u8a_code, 0xBB, sizeof(u8a_code));
    EXPECT_EQ(cobs_encode(u8a_data_in, 0, u8a_code, 2), 2);
    EXPECT_EQ(cobs_decode(u8a_code, 2, u8a_data_out, 0), 0);
    // memprint(u8a_code, 10, 0);
}

UTEST(cobs, decode_out_size65)
{
    uint8_t u8a_data_in[65] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data_in))] = {0};
    uint8_t u8a_data_out[COBS_DECODE_OUT_SIZE_MIN(sizeof(u8a_code))] = {0};

    memset(u8a_data_in, 1, sizeof(u8a_data_in));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)), sizeof(u8a_data_out));
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
    memset(u8a_data_in, 0, sizeof(u8a_data_in));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)), sizeof(u8a_data_out));
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
}

UTEST(cobs, decode_out_size512)
{
    uint8_t u8a_data_in[512] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data_in))] = {0};
    uint8_t u8a_data_out[COBS_DECODE_OUT_SIZE_MIN(sizeof(u8a_code))] = {0};

    memset(u8a_data_in, 1, sizeof(u8a_data_in));
    memset(u8a_data_out, 0xBB, sizeof(u8a_data_out));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)), sizeof(u8a_data_out) - 2);
    // UTEST_PRINTF("%d\n", (int)cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)));
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
    memset(u8a_data_in, 0, sizeof(u8a_data_in));
    memset(u8a_data_out, 0xBB, sizeof(u8a_data_out));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code) - 2);
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code) - 2, u8a_data_out, sizeof(u8a_data_out)), sizeof(u8a_data_out) - 2);
    // UTEST_PRINTF("%d\n", (int)cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)));
    // memprint(u8a_code, sizeof(u8a_code), 0);
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
}

UTEST(cobs, overflow)
{
    uint8_t u8a_data_in[65] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data_in))] = {0};
    uint8_t u8a_data_out[COBS_DECODE_OUT_SIZE_MIN(sizeof(u8a_code))] = {0};

    memset(u8a_data_in, 1, sizeof(u8a_data_in));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code) - 10), 0);
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
    memset(u8a_data_in, 0, sizeof(u8a_data_in));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code));
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out) - 10), 0);
    // UTEST_PRINTF("%d\n", (int)cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out) - 10));
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
}

UTEST(cobs, protocol_issue)
{
    uint8_t u8a_data_in[65] = {0};
    uint8_t u8a_code[COBS_ENCODE_OUT_SIZE_MIN(sizeof(u8a_data_in))] = {0};
    uint8_t u8a_data_out[COBS_DECODE_OUT_SIZE_MIN(sizeof(u8a_code))] = {0};

    memset(u8a_data_in, 1, sizeof(u8a_data_in));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code));
    u8a_code[10] = 0;
    EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)), 0);
    // UTEST_PRINTF("%d\n", (int)cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)));
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);

    memset(u8a_data_in, 1, sizeof(u8a_data_in));
    EXPECT_EQ(cobs_encode(u8a_data_in, sizeof(u8a_data_in), u8a_code, sizeof(u8a_code)), sizeof(u8a_code));
    u8a_code[0] = 255;
    // EXPECT_EQ(cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)), 0);
    // UTEST_PRINTF("%d\n", (int)cobs_decode(u8a_code, sizeof(u8a_code), u8a_data_out, sizeof(u8a_data_out)));
    // memprint(u8a_data_in, sizeof(u8a_data_in), 0);
    // memprint(u8a_code, sizeof(u8a_code), 0);
    // memprint(u8a_data_out, sizeof(u8a_data_out), 0);
}

/*==============================================================================
 TEST MAIN
 =============================================================================*/

UTEST_MAIN();
