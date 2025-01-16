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

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09113DE0);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09113E70);

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
