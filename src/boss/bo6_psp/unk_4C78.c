// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../bo6/bo6.h"

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

static u8* pixPtr;

static s32 frameBufferX;

static s32 frameBufferY;

void func_psp_0923C390(s32 posX, s32 posY) {
    pixPtr = g_Pix[0];
    frameBufferX = posX;
    frameBufferY = posY;
}
