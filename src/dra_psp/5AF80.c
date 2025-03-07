// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012D3E8);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012DBBC);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012DF04);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E040);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E550);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E7A4);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E9C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012EAD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012ED30);

void func_8012EF2C(void) {
    s32 i;
    s32 xSpeed;
    s32 var_s0;

    PLAYER.palette = 0x104;
    PLAYER.drawMode = DRAW_DEFAULT;
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
#endif
    if (WolfFormFinished()) {
        return;
    }
    if (D_8013842C != 0) {
        D_8013842C--;
    }
    if (D_80138440 != 0) {
        D_80138440--;
    }
    D_80138444 = 0;
    func_8012C97C();
    D_800B0920 = 14;
    switch (PLAYER.step_s) {
    case 0:
        func_8012E7A4();
        break;
    case 1:
        func_8012D024();
        break;
    case 2:
        func_8012D3E8();
        break;
    case 3:
        func_8012E550();
        break;
    case 4:
        func_8012E040();
        break;
    case 5:
        func_8012DBBC();
        break;
    case 7:
        func_8012D178();
        break;
    case 6:
        func_8012DF04();
        break;
    case 8:
        func_8012E9C0();
        break;
    case 9:
        func_8012ED30();
    }
    D_80138438 = g_Player.unk04;
    for (i = 0; i < 8; i++) {
        var_s0 = 4;
        xSpeed = abs(PLAYER.velocityX);
        if (xSpeed >= FIX(4)) {
            var_s0--;
        }
        if (xSpeed >= FIX(5)) {
            var_s0--;
        }
        if (xSpeed >= FIX(6)) {
            var_s0--;
        }
        // Might be misusing D_800AFFB8 here
        D_800AFFB8[i * 2] = var_s0;
    }
    if (D_80138430 < 0x600) {
        D_80138430 = 0x600;
    }
    if (D_80138430 > 0xA00) {
        D_80138430 = 0xA00;
    }
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
#endif
}

// func_8012F178
INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_psp_09139B50);
// func_8012F83C
INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_psp_0913A3A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012F894);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130264);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130618);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_801309B4);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130E94);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8013136C);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", EntityGiantSpinningCross);
