// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

extern u8* D_pspeu_092645F8;
extern s32 D_pspeu_092645F0;
extern s32 D_pspeu_092645E8;

u8 func_psp_0923C2F8(u8 arg0) {
    if (arg0 & 0x100) {
        return func_psp_0923C2F8(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_psp_0923C2F8((arg0 & 0x7F) + 3);
    }
    return arg0 * 0x10;
}

void func_psp_0923C390(s32 posX, s32 posY) {
    D_pspeu_092645F8 = g_Pix[0];
    D_pspeu_092645F0 = posX;
    D_pspeu_092645E8 = posY;
}
