// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

static u16 D_psp_09186EF8[] = {
    '踪', '眷', '翔', '彷', '徨',
    '苺', '獰', '賤', '贄', '鬱'}; // last one should be a copyright symbol

static u8 D_psp_09186F10[][30] = {
    // clang-format off
    {
        0b00000000, 0b00100000,
        0b01111100, 0b00100000,
        0b01000101, 0b11111110,
        0b01000101, 0b00000010,
        0b01000101, 0b00000010,
        0b01111100, 0b01111000,
        0b00010000, 0b00000000,
        0b00010000, 0b00000000,
        0b01010001, 0b11111110,
        0b01011100, 0b00100000,
        0b01010000, 0b10100100,
        0b01010000, 0b10100010,
        0b01010001, 0b00100010,
        0b01011100, 0b00100000,
        0b11100000, 0b01100000
    },
    {
        0b00000001, 0b00000000,
        0b00010001, 0b00010000,
        0b00101111, 0b11101000,
        0b01000010, 0b10000100,
        0b00000100, 0b01000000,
        0b11111111, 0b11111110,
        0b00001000, 0b00100000,
        0b00010000, 0b00010000,
        0b00111111, 0b11111000,
        0b11010000, 0b00010110,
        0b00011111, 0b11110000,
        0b00010000, 0b00010000,
        0b00011111, 0b11110000,
        0b00010000, 0b00010000,
        0b00011111, 0b11110000
    },
    {
        0b10001000, 0b00000000,
        0b01001011, 0b10111100,
        0b00010000, 0b10000100,
        0b11111000, 0b10000100,
        0b00100100, 0b10100100,
        0b00100010, 0b10010100,
        0b11111000, 0b10000100,
        0b00100000, 0b10000100,
        0b00100001, 0b10001100,
        0b00111010, 0b10010100,
        0b11100100, 0b10100100,
        0b00101000, 0b10000100,
        0b01000000, 0b10000100,
        0b01000000, 0b10000100,
        0b10000011, 0b10011100
    },
    {
        0b00010000, 0b01000000,
        0b00010000, 0b01000000,
        0b00100000, 0b01000000,
        0b01000111, 0b11111110,
        0b10010000, 0b10000000,
        0b00010000, 0b10000000,
        0b00100000, 0b10000000,
        0b00100000, 0b11111100,
        0b01100000, 0b10000100,
        0b10100001, 0b00000100,
        0b00100001, 0b00000100,
        0b00100001, 0b00000100,
        0b00100010, 0b00001000,
        0b00100010, 0b00001000,
        0b00100100, 0b01110000
    },
    {
        0b00010000, 0b01000000,
        0b00010000, 0b10000000,
        0b00100011, 0b11111000,
        0b01000010, 0b00001000,
        0b10010011, 0b11111000,
        0b00010010, 0b00001000,
        0b00100011, 0b11111000,
        0b00100000, 0b00000000,
        0b01100111, 0b11111100,
        0b10100000, 0b01000000,
        0b00100000, 0b01000000,
        0b00100011, 0b11111100,
        0b00100000, 0b01000000,
        0b00100000, 0b01000000,
        0b00101111, 0b11111110
    },
    {
        0b00001000, 0b01000000,
        0b11111111, 0b11111110,
        0b00001000, 0b01000000,
        0b00000000, 0b00000000,
        0b00011111, 0b11110000,
        0b00010001, 0b00010000,
        0b00010000, 0b10010000,
        0b00010000, 0b00010000,
        0b11111111, 0b11111110,
        0b00100010, 0b00010000,
        0b00100001, 0b00010000,
        0b00100000, 0b00010000,
        0b01111111, 0b11111100,
        0b01000000, 0b00100000,
        0b00000001, 0b11000000
    },
    {
        0b00001000, 0b01000000,
        0b10001111, 0b11111110,
        0b01010100, 0b00000010,
        0b00100101, 0b01000010,
        0b01100011, 0b00010100,
        0b10100101, 0b11110010,
        0b00010000, 0b00000000,
        0b00010011, 0b11111100,
        0b00110010, 0b10100100,
        0b01010111, 0b11111110,
        0b10010000, 0b00000000,
        0b00010111, 0b11111110,
        0b00010000, 0b01000000,
        0b00010000, 0b01000000,
        0b01100001, 0b11000000
    },
    {
        0b00000000, 0b01001000,
        0b01111100, 0b01001110,
        0b01000101, 0b11110000,
        0b01000100, 0b00100100,
        0b01111100, 0b00011000,
        0b01000100, 0b01101010,
        0b01000101, 0b10000110,
        0b01111100, 0b01010000,
        0b01000100, 0b01001000,
        0b01000100, 0b01011110,
        0b01000101, 0b11100000,
        0b01111100, 0b00100100,
        0b00000000, 0b00011000,
        0b01001000, 0b01101010,
        0b10000101, 0b10000110
    },
    {
        0b00010000, 0b00100000,
        0b01111100, 0b00100000,
        0b00010000, 0b11111000,
        0b11111110, 0b00101000,
        0b00101000, 0b01101010,
        0b01111100, 0b01011010,
        0b00010000, 0b10001110,
        0b00011111, 0b11110000,
        0b00010000, 0b00010000,
        0b00011111, 0b11110000,
        0b00010000, 0b00010000,
        0b00011111, 0b11110000,
        0b00010000, 0b00010000,
        0b00011111, 0b11110000,
        0b01110000, 0b00011100
    },
    {
        0b00000111, 0b11000000,
        0b00011000, 0b00110000,
        0b00100000, 0b00001000,
        0b01000111, 0b11000100,
        0b01001000, 0b01000100,
        0b10010000, 0b00010010,
        0b10010000, 0b00000010,
        0b10010000, 0b00000010,
        0b10010000, 0b00000010,
        0b10010000, 0b00010010,
        0b01001000, 0b01000100,
        0b01000111, 0b11000100,
        0b00100000, 0b00001000,
        0b00011000, 0b00110000,
        0b00000111, 0b11000000
    },
    // clang-format on
};

static u16 D_psp_09187040[] = {
    0, 1, 1, 2, 2, 3, 3, 4, 4,
    5, 5, 6, 6, 7, 7, 8, 8}; // LUT of ceil(index / 2)

static char D_psp_09187068[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstu"
    "vwxyz0123456789\" .+-=_'?/![]\":;,()";
static char D_psp_091870C0[] =
    "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺａｂｃｄｅｆｇｈｉｊｋ"
    "ｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ０１２３４５６７８９”　．＋−＝＿’？／！［］”"
    "：；，（）";
static char* D_psp_09187168[] = {D_psp_091870C0};
static char* D_psp_09187170[] = {D_psp_09187068};
static char D_psp_09187178[] =
    "ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜｦﾝｧｨｩｪｫｬｭｮ";
static u16 D_psp_091871B0[] = {
    0x8146, 0x8634, 0x8635, 0x858A, 0x858B, 0x858D, 0x858C, 0x8597,
    0x859B, 0x859A, 0x859D, 0x859C, 0x85A8, 0x85A7, 0x85AA, 0x85A9,
    0x85B8, 0x85BA, 0x85B9, 0x85BC, 0x85BB, 0x85CB, 0x85CA, 0x85CD,
    0x85CC, 0x83C0, 0x85E1, 0x85E0, 0x85E3, 0x85E2, 0x85ED, 0x85F1,
    0x85F0, 0x85F3, 0x85F2, 0x85FE, 0x85FD, 0x8600, 0x85FF, 0x860D,
    0x860F, 0x860E, 0x8611, 0x8610, 0x8620, 0x861F, 0x8622, 0x8621,
    0x8577, 0x8586, 0x814E, 0x8636, 0x8147, 0x8621, 0x0000};

extern u16 D_psp_092367D0[];

u16 func_psp_0913F960(char* str, u8* type) {
    u32 i;
    u16 ret;
    char* ptr;

    ptr = D_psp_09187170[0];
    for (i = 0; i < LEN(D_psp_09187068); i++) {
        if (str[0] == *ptr) {
            char* ch = &D_psp_09187168[0][i * 2];
            ret = ch[0] << 8;
            ret |= ch[1];
            *type = 1;
            return ret;
        }
        ptr++;
    }
    ptr = D_psp_09187178;
    for (i = 0; i < LEN(D_psp_091871B0); i++) {
        if (str[0] == *ptr) {
            ret = D_psp_091871B0[i];
            *type = 1;
            return ret;
        }
        ptr++;
    }
    ret = str[0] << 8;
    ret |= str[1];
    *type = 2;
    return ret;
}

#define ExtractBit(x)                                                          \
    x & 1;                                                                     \
    x >>= 1

u16* func_psp_0913FA28(u16 ch, u16 kind) {
    u8* bitmap;
    u16* srcPtr;
    u16* destPtr;
    u16 i, j, k;
    u16 val0, val1, val2;
    u16 b0, b1, b2, b3;
    u16 dest, dest2;
    u8 row;

    // Krom2RawAdd returns a pointer to 30 bytes: 15 rows of 2 bytes for a
    // bitmap of size 16x15.
    bitmap = (u8*)Krom2RawAdd(ch);
    if (bitmap == (u8*)-1) {
        srcPtr = D_psp_09186EF8;
        for (i = 0; i < LEN(D_psp_09186F10); i++) {
            if (ch == *srcPtr++) {
                bitmap = D_psp_09186F10[i];
            }
        }
        if (bitmap == (u8*)-1) {
            ch = 0x819A;
            bitmap = (u8*)Krom2RawAdd(ch);
        }
    }

    srcPtr = D_psp_092367D0;
    for (i = 0; i < 15; i++) {
        val0 = val2 = val1 = 0;

        row = *bitmap;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val1 |= (b0 * 3 + b1) << 0x4;
        val1 |= (b1 * 2 + b2 * 2);
        val0 |= (b2 + b3 * 3) << 0xC;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val0 |= (b0 * 3 + b1) << 0x8;
        val0 |= (b1 * 2 + b2 * 2) << 0x4;
        val0 |= b2 + b3 * 3;

        bitmap++;

        row = *bitmap;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val2 |= (b0 * 3 + b1) << 0xC;
        val2 |= (b1 * 2 + b2 * 2) << 0x8;
        val2 |= (b2 + b3 * 3) << 0x4;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val2 |= b0 * 3 + b1;
        val1 |= (b1 * 2 + b2 * 2) << 0xC;
        val1 |= (b2 + b3 * 3) << 0x8;

        *srcPtr++ = val0;
        *srcPtr++ = val1;
        *srcPtr++ = val2;
        bitmap++;
    }

    destPtr = D_psp_092367D0;
    srcPtr = D_psp_092367D0;
    switch (kind) {
    case 0:
    case 3:
        for (i = 0; i < 45; i++) {
            val0 = *srcPtr++;
            dest = D_psp_09187040[(val0 >> 0xC & 0xF) * 4] << 0xC;
            dest |= D_psp_09187040[(val0 >> 0x8 & 0xF) * 4] << 0x8;
            dest |= D_psp_09187040[(val0 >> 0x4 & 0xF) * 4] << 0x4;
            dest |= D_psp_09187040[(val0 >> 0x0 & 0xF) * 4] << 0x0;
            *destPtr++ = dest;
        }
        for (i = 0; i < 3; i++) {
            *destPtr++ = 0;
        }
        break;

    case 1:
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 3; j++) {
                for (k = 7; k > 0; k--) {
                    val0 = *srcPtr;
                    srcPtr += 3;
                    val2 = *srcPtr;
                    dest = D_psp_09187040[((val0 >> 0xC & 0xF) * k +
                                           (val2 >> 0xC & 0xF) * (8 - k)) /
                                          2]
                           << 0xC;
                    dest |= D_psp_09187040[((val0 >> 0x8 & 0xF) * k +
                                            (val2 >> 0x8 & 0xF) * (8 - k)) /
                                           2]
                            << 0x8;
                    dest |= D_psp_09187040[((val0 >> 0x4 & 0xF) * k +
                                            (val2 >> 0x4 & 0xF) * (8 - k)) /
                                           2]
                            << 0x4;
                    dest |= D_psp_09187040[((val0 >> 0x0 & 0xF) * k +
                                            (val2 >> 0x0 & 0xF) * (8 - k)) /
                                           2]
                            << 0x0;
                    *destPtr = dest;
                    destPtr += 3;
                }
                srcPtr -= 20;
                destPtr -= 20;
            }
            srcPtr += 21;
            destPtr += 18;
        }
        for (i = 0; i < 6; i++) {
            *destPtr++ = 0;
        }
        break;

    case 2:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                for (k = 3; k > 0; k--) {
                    val0 = *srcPtr;
                    srcPtr += 3;
                    val2 = *srcPtr;
                    dest = D_psp_09187040[(val0 >> 0xC & 0xF) * k +
                                          (val2 >> 0xC & 0xF) * (4 - k)]
                           << 0xC;
                    dest |= D_psp_09187040[(val0 >> 0x8 & 0xF) * k +
                                           (val2 >> 0x8 & 0xF) * (4 - k)]
                            << 0x8;
                    dest |= D_psp_09187040[(val0 >> 0x4 & 0xF) * k +
                                           (val2 >> 0x4 & 0xF) * (4 - k)]
                            << 0x4;
                    dest |= D_psp_09187040[(val0 >> 0x0 & 0xF) * k +
                                           (val2 >> 0x0 & 0xF) * (4 - k)]
                            << 0x0;
                    *destPtr = dest;
                    destPtr += 3;
                }
                srcPtr -= 8;
                destPtr -= 8;
            }
            srcPtr += 9;
            destPtr += 6;
        }
        for (i = 0; i < 12; i++) {
            *destPtr++ = 0;
        }
        break;
    }
    if (kind == 3) {
        for (i = 0; i < 0x42; i++) {
            dest2 = D_psp_092367D0[i]; // for each 4 bits, if 3rd bit is set and
                                       // next group of 4 bits is empty, set
                                       // first bit in next group of 4 bits
            if (dest2 & 4) {
                if ((D_psp_092367D0[i] & 0xF0) == 0) {
                    D_psp_092367D0[i] |= 0x10;
                }
            }
            if (dest2 & 0x40) {
                if ((D_psp_092367D0[i] & 0xF00) == 0) {
                    D_psp_092367D0[i] |= 0x100;
                }
            }
            if (dest2 & 0x400) {
                if ((D_psp_092367D0[i] & 0xF000) == 0) {
                    D_psp_092367D0[i] |= 0x1000;
                }
            }
            if ((dest2 & 0x4000) && (i < 0x41)) {
                if ((D_psp_092367D0[i + 1] & 0xF) == 0) {
                    D_psp_092367D0[i + 1] |= 1;
                }
            }
        }
    }
    return D_psp_092367D0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_09140588);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_091405C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_091405E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_09140600);
