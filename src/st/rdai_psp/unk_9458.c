// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

static u8 func_psp_0923C2F8(u8 arg0) {
    if (arg0 & 0x100) {
        return func_psp_0923C2F8(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_psp_0923C2F8((arg0 & 0x7F) + 3);
    }
    return arg0 * 0x10;
}

extern u8* D_pspeu_09283978;
extern s32 D_pspeu_09283970;
extern s32 D_pspeu_09283968;

static void func_psp_0923C390(s32 posX, s32 posY) {
    D_pspeu_09283978 = g_Pix[0];
    D_pspeu_09283970 = posX;
    D_pspeu_09283968 = posY;
}
