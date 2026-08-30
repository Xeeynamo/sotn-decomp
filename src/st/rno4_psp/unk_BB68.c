// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_BB68", EntityImp);

#include "../e_imp_smoke.h"

static u8 func_psp_0923C2F8(u8 arg0) {
    if (arg0 & 0x100) {
        return func_psp_0923C2F8(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_psp_0923C2F8((arg0 & 0x7F) + 3);
    }
    return arg0 * 0x10;
}

static void func_psp_0923C390(s32 posX, s32 posY) {
    extern u8* g_ImpSmokePixels;
    extern s32 g_ImpSmokePosX;
    extern s32 g_ImpSmokePosY;

    g_ImpSmokePixels = g_Pix[0];
    g_ImpSmokePosX = posX;
    g_ImpSmokePosY = posY;
}
