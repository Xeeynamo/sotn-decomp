// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "../dra/dra.h"

extern s32 g_CurrentStream;

void func_psp_090FFAB8(void) {
    s32 var_a1 = 0;
    switch (g_CurrentStream) {
    case 0:
        var_a1 = 8;
        break;
    case 1:
        var_a1 = 8;
        break;
    case 2:
        var_a1 = 0x6008;
        break;
    case 3:
        var_a1 = 0x6008;
        break;
    }
    func_psp_08912820(g_CurrentStream, var_a1);
    D_8003C728 = 0;
    g_IsUsingCd = 0;
}
