// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_8010E42C(u32 substep) {
    PLAYER.step = Player_Teleport;
    PLAYER.step_s = substep;

    if (substep & 1) {
        SetPlayerAnim(0xF5);
    } else {
        SetPlayerAnim(0xF4);
    }
}

u8 D_800ACF4C[] = {0x00, 0x11, 
                   0x04, 0x15, 
                   0x01, 0x10, 
                   0x03, 0x23};

void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.velocityX = arg1;
    PLAYER.velocityY = 0;
    PLAYER.step = Player_Crouch;
    PLAYER.step_s = (s16)D_800ACF4C[arg0 * 2 + 0];
    SetPlayerAnim(D_800ACF4C[arg0 * 2 + 1]);
}

// This may be the function that turns Alucard into stone
void func_8010E4D0(void) {
    func_80111CC0();

    PLAYER.palette = PAL_OVL(0x100);
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;

    if (g_Player.unk72 == 1 || g_Player.unk72 == 2) {
        SetPlayerAnim(0xC7);
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        SetPlayerStep(Player_AlucardStuck);
        func_80111CC0();
        PlaySfx(SFX_VO_ALU_WHAT);
        return;
    }
    func_80111CC0();
    func_8010E470(0, 0);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010E570);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_091140D8);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114208);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010E83C);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010E940);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", DoGravityJump);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114500);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114590);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114668);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114880);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_091149C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114A38);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010FAF4);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformHellfire);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformDarkMetamorphosis);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSoulSteal);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSummonSpirit);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformTetraSpirit);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSwordBrothers);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010FD88);

// Next func in PSP is SetPlayerStep; next in US is func_8010FDF8. File split.
