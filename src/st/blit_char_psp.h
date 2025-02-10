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

extern u8* D_psp_0924BC78;
extern s32 D_psp_0924BC70;
extern s32 D_psp_0924BC68;

// PSP unique?
void func_psp_0923C390(s32 arg0, s32 arg1) {
    D_psp_0924BC78 = (u8*)&g_Pix;
    D_psp_0924BC70 = arg0;
    D_psp_0924BC68 = arg1;
}

u8 func_psp_0923C2F8(u8 arg0);

char* BlitChar(char* str, s32 xOffset, s32 posX, s32 posY) {
    const u16 MINSCODE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    u8 ch;
    s32 var_s3;
    s32 i, j;
    s32 letterWidth;
    u8* chPix;
    u8* ptr;
    u32 ch16;

    s32 size;
    s32 sp38;
    s32 sp34;

    u8 sp3f;
    s32 pos;

    ch = 0;
    func_psp_0923C390(posX, posY);

    size = 0x90;
    for (i = 0; i < size * 16; i++) {
        D_psp_0924BC78[i] = 0;
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

    for (; *str;) {
        sp38 = 0;

        ch16 = g_api.func_ptr_91CF870(str, &sp3f);
        ch = *str++;
        if (ch != 1) {
            if (ch >= 'a' && ch <= 'z') {
                ch16 = ch + 0x8220;
            } else if (ch >= 'A' && ch <= 'Z') {
                ch16 = ch + 0x821F;
            } else if (ch == 0x20) {
                ch16 = 0x8140;
                sp38 = 2;
            } else {
                if (sp3f > 1) {
                    str = &str[sp3f - 1];
                }
                sp38 = sp3f;

                if (ch16 == 0x8140) {
                    ch = 0x20;
                }
            }

            chPix = (u8*)g_api.func_ptr_91CF86C(ch16, 0);

            while (true) {
                if (ch == 0x20) {
                    break;
                }

                for (i = 0; i < FontHeight; i++) {
                    if (chPix[i * (FontStride << 1) / 2]) {
                        break;
                    }
                }
                if (i != FontHeight) {
                    break;
                }

                for (i = 0; i < FontHeight; i++) {
                    ptr = chPix + (i * (FontStride << 1)) / 2;
                    for (j = 0; j < 5; j++) {
                        ptr[0] = ptr[1];
                        ptr++;
                    }
                    *ptr = 0;
                }
            }

            for (i = 0, letterWidth = 0; i < FontHeight; i++) {

                for (j = 0; j < FontStride; j++) {

                    if (chPix[i * (FontStride << 1) / 2 + j] &&
                        letterWidth < j) {

                        letterWidth = j;
                    }
                }
            }

            for (i = 0; i < FontHeight; i++) {
                if (chPix[letterWidth + i * (FontStride << 1) / 2] & 0xF0) {
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
                ptr = &D_psp_0924BC78[(i * size + pos)];
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
            }

            pos += letterWidth + sp38;

            if (pos >= size) {
                break;
            }
        } else {
            break;
        }
    }

    LoadTPage((u_long*)D_psp_0924BC78, 0, 0, D_psp_0924BC70 + sp34,
              D_psp_0924BC68 + xOffset, size << 1, 0x10);
    D_psp_0924BC78 += size * 0x10;

    if (ch == 1) {
        BlitChar(str, xOffset + 0x10, posX, posY + 0x10);
    }
}
