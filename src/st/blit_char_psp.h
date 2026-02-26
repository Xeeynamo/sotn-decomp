// SPDX-License-Identifier: AGPL-3.0-or-later
u8 func_psp_0923C2F8(u8 arg0) {
    if (arg0 & 0x100) {
        return func_psp_0923C2F8(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_psp_0923C2F8((arg0 & 0x7F) + 3);
    }
    return arg0 * 0x10;
}

// bss
static u8* pixPtr;
static s32 frameBufferX;
static s32 frameBufferY;

void func_psp_0923C390(s32 posX, s32 posY) {
    pixPtr = g_Pix[0];
    frameBufferX = posX;
    frameBufferY = posY;
}

char* BlitChar(char* str, s32 xOffset, s32 posX, s32 posY) {
    const u16 DOUBLE_SPACE = 0x8140;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    u8 ch;
    s32 i, j;
    s32 letterWidth;
    u8* chPix;
    u8* ptr;
    u32 ch16;

    s32 stride;
    s32 chSize;
    s32 sp34;

    u8 sp3f;
    s32 pos;

    ch = 0;
    func_psp_0923C390(posX, posY);

    stride = 0x90;
    for (i = 0; i < stride * 16; i++) {
        pixPtr[i] = 0;
    }
    pos = 0;
    sp34 = 0;
    if (xOffset & 0x100) {
        sp34 = 0x40;
    }
    if (xOffset & 0x200) {
        sp34 += 0x20;
        xOffset &= ~0x200;
    }

    xOffset = func_psp_0923C2F8(xOffset);

    while (*str) {
        chSize = 0;
        ch16 = g_api.func_psp_0913F960(str, &sp3f);
        ch = *str++;
        if (ch == 1) {
            break;
        }
        if (ch >= 'a' && ch <= 'z') {
            ch16 = ch + 0x8220;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch16 = ch + 0x821F;
        } else if (ch == ' ') {
            ch16 = DOUBLE_SPACE;
            chSize = 2;
        } else {
            if (sp3f > 1) {
                str = &str[sp3f - 1];
            }
            chSize = sp3f;

            if (ch16 == DOUBLE_SPACE) {
                ch = ' ';
            }
        }

        // use the converted Shift-JIS character to retrieve the font data
        chPix = (u8*)g_api.func_psp_0913FA28(ch16, 0);
        while (true) {
            if (ch == ' ') {
                break;
            }

            for (i = 0; i < FontHeight; i++) {
                if (chPix[i * (FontStride * 2) / 2]) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }

            // Trim character width from the left-hand side
            for (i = 0; i < FontHeight; i++) {
                ptr = &chPix[(i * (FontStride * 2)) / 2];
                for (j = 0; j < 5; j++) {
                    ptr[0] = ptr[1];
                    ptr++;
                }
                *ptr = 0;
            }
        }

        // scroll every pixel of the letter and finds the furthest horizontal
        // pixel to calculate what the width is
        for (i = 0, letterWidth = 0; i < FontHeight; i++) {
            for (j = 0; j < FontStride; j++) {
                if (chPix[i * (FontStride * 2) / 2 + j] && letterWidth < j) {
                    letterWidth = j;
                }
            }
        }

        // Check the very last vertical pixel
        for (i = 0; i < FontHeight; i++) {
            if (chPix[letterWidth + i * (FontStride * 2) / 2] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            letterWidth++;
        }

        if (letterWidth < FontStride) {
            letterWidth++;
        }

        for (i = 0; i < FontHeight; i++) {
            ptr = &pixPtr[pos + i * stride];
            *ptr++ = *chPix++;
            *ptr++ = *chPix++;
            *ptr++ = *chPix++;
            *ptr++ = *chPix++;
            *ptr++ = *chPix++;
            *ptr++ = *chPix++;
        }

        pos += letterWidth + chSize;

        if (pos >= stride) {
            break;
        }
    }

    LoadTPage((u_long*)pixPtr, 0, 0, frameBufferX + sp34,
              frameBufferY + xOffset, stride * 2, 0x10);
    pixPtr += stride * 0x10;

    if (ch == 1) {
        BlitChar(str, xOffset + 0x10, posX, posY + 0x10);
    }
}
