// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Section Sizes:
//
//         | Data  | RO Data | Text   | BSS  |
//         +-------+---------+--------+------+
//  PSX US | -     | -       | 0x2B0  | -    |
//
#include <stage.h>

char* BlitChar(char* str, u16* xOffset, u8* pix, u16 stride) {
    const u16 MINSCODE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    u16 ch;
    s32 var_s3;
    s32 i, j;
    s32 letterWidth;
    u8* chPix;
    u8* ptr;
    u8* dst;

    // converts the ASCII character into Shift-JIS
    ch = *str++;
    var_s3 = 0;
    if (ch >= 'a' && ch <= 'z') {
        ch += 0x8220;
    } else if (ch >= 'A' && ch <= 'Z') {
        ch += 0x821F;
    } else {
        if (ch == ' ') {
            ch = MINSCODE;
            var_s3 = 2;
        } else {
            ch = *str++ | (ch << 8);
            if (ch == MINSCODE) {
                var_s3 = 2;
            }
        }
    }

    if (ch == RIGHT_DOUBLE_QUOTATION_MARK) {
        str += 2;
    }

    // use the converted Shift-JIS character to retrieve the font data
    chPix = g_api.func_80106A28(ch, 1);
    while (true) {
        if (ch == MINSCODE) {
            break;
        }

        for (i = 0; i < FontHeight; i++) {
            dst = &chPix[i * FontStride];
            if (*dst) {
                break;
            }
        }
        if (i != FontHeight) {
            break;
        }

        // Trim character width from the left-hand side
        for (i = 0; i < FontHeight; i++) {
            ptr = chPix;
            ptr += i * FontStride;
            for (j = 0; j < 5; j++) {
                ptr[0] = ptr[1];
                ptr++;
            }
            *ptr = 0;
        }
    }

    // scroll every pixel of the letter and finds the furthest horizontal pixel
    // to calculate what the width is
    for (i = 0, letterWidth = 0; i < FontHeight; i++) {
        for (j = 0; j < FontStride; j++) {
            if (chPix[i * FontStride + j] && letterWidth < j) {
                letterWidth = j;
            }
        }
    }

    // Check the very last vertical pixel
    for (i = 0; i < FontHeight; i++) {
        if (chPix[letterWidth + i * FontStride] & 0xF0) {
            break;
        }
    }
    if (i != FontHeight) {
        letterWidth++;
    }

    // Adds at least a vertical pixel of padding at the end of the character
    if (letterWidth < FontStride) {
        letterWidth++;
    }

    // Copy content to destination
    for (i = 0; i < FontHeight; i++) {
        ptr = pix;
        ptr += *xOffset + i * stride;
        *ptr++ = *chPix++;
        *ptr++ = *chPix++;
        *ptr++ = *chPix++;
        *ptr++ = *chPix++;
        *ptr++ = *chPix++;
        dst = ptr;
        *dst = *chPix++;
    }

    *xOffset += letterWidth + var_s3;
    return str;
}
