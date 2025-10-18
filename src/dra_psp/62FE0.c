// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern u16 D_800AC910[];
extern u8 D_800AC914[10][30];
extern u16 D_800AC934[];

static char D_psp_09187068[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789\" .+-=_'?/![]\":;,()";
static char D_psp_091870C0[] =
    "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ"
    "ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ"
    "０１２３４５６７８９”　．＋−＝＿’？／！［］”：；，（）";
static char* D_psp_09187168 = D_psp_091870C0;
static char* D_psp_09187170 = D_psp_09187068;
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

extern u16 D_80137EF8[];

u16 func_psp_0913F960(char* str, u8* type) {
    u32 i;
    u16 ret;
    char* ptr;

    ptr = D_psp_09187170;
    for (i = 0; i < 0x52; i++) {
        if (str[0] == *ptr) {
            char* ch = &D_psp_09187168[i * 2];
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
        srcPtr = D_800AC910;
        for (i = 0; i < LEN(D_800AC914); i++) {
            if (ch == *srcPtr++) {
                bitmap = D_800AC914[i];
            }
        }
        if (bitmap == (u8*)-1) {
            ch = 0x819A;
            bitmap = (u8*)Krom2RawAdd(ch);
        }
    }

    srcPtr = D_80137EF8;
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
        dest = val1; // fake

        *srcPtr++ = val0;
        *srcPtr++ = val1;
        *srcPtr++ = val2;
        bitmap++;
    }

    destPtr = D_80137EF8;
    srcPtr = D_80137EF8;
    switch (kind) {
    case 0:
    case 3:
        for (i = 0; i < 45; i++) {
            val0 = *srcPtr++;
            dest = D_800AC934[(val0 >> 0xC & 0xF) * 4] << 0xC;
            dest |= D_800AC934[(val0 >> 0x8 & 0xF) * 4] << 0x8;
            dest |= D_800AC934[(val0 >> 0x4 & 0xF) * 4] << 0x4;
            dest |= D_800AC934[(val0 >> 0x0 & 0xF) * 4] << 0x0;
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
                    dest = D_800AC934[((val0 >> 0xC & 0xF) * k +
                                       (val2 >> 0xC & 0xF) * (8 - k)) /
                                      2]
                           << 0xC;
                    dest |= D_800AC934[((val0 >> 0x8 & 0xF) * k +
                                        (val2 >> 0x8 & 0xF) * (8 - k)) /
                                       2]
                            << 0x8;
                    dest |= D_800AC934[((val0 >> 0x4 & 0xF) * k +
                                        (val2 >> 0x4 & 0xF) * (8 - k)) /
                                       2]
                            << 0x4;
                    dest |= D_800AC934[((val0 >> 0x0 & 0xF) * k +
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
                    dest = D_800AC934[(val0 >> 0xC & 0xF) * k +
                                      (val2 >> 0xC & 0xF) * (4 - k)]
                           << 0xC;
                    dest |= D_800AC934[(val0 >> 0x8 & 0xF) * k +
                                       (val2 >> 0x8 & 0xF) * (4 - k)]
                            << 0x8;
                    dest |= D_800AC934[(val0 >> 0x4 & 0xF) * k +
                                       (val2 >> 0x4 & 0xF) * (4 - k)]
                            << 0x4;
                    dest |= D_800AC934[(val0 >> 0x0 & 0xF) * k +
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
            dest2 = D_80137EF8[i];
            if (dest2 & 4) {
                if ((D_80137EF8[i] & 0xF0) == 0) {
                    D_80137EF8[i] |= 0x10;
                }
            }
            if (dest2 & 0x40) {
                if ((D_80137EF8[i] & 0xF00) == 0) {
                    D_80137EF8[i] |= 0x100;
                }
            }
            if (dest2 & 0x400) {
                if ((D_80137EF8[i] & 0xF000) == 0) {
                    D_80137EF8[i] |= 0x1000;
                }
            }
            if ((dest2 & 0x4000) && (i < 0x41)) {
                if ((D_80137EF8[i + 1] & 0xF) == 0) {
                    D_80137EF8[i + 1] |= 1;
                }
            }
        }
    }
    return D_80137EF8;
}
