// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DE7D0);

void func_80105408(void) {
    g_Player.padSim = PAD_UP;
    g_Player.D_80072EFC = 1;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_80105428);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFBD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFC68);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFC80);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_800EA538);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_800EA5AC);
