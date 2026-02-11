// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "../dra/dra.h"

extern s32 g_CurrentStream;

void func_psp_090FFAB8(void) {
    s32 restartButton = PAD_NONE;
    switch (g_CurrentStream) {
    case 0:
        restartButton = PAD_START;
        break;
    case 1:
        restartButton = PAD_START;
        break;
    case 2:
        restartButton = PAD_CROSS | PAD_CIRCLE | PAD_START;
        break;
    case 3:
        restartButton = PAD_CROSS | PAD_CIRCLE | PAD_START;
        break;
    }
    func_psp_08912820(g_CurrentStream, restartButton);
    D_8003C728 = 0;
    g_IsUsingCd = 0;
}
