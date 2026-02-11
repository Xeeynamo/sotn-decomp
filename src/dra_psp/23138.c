// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "../dra/dra.h"

extern s32 g_CurrentStream;

void func_psp_090FFAB8(void) {
    s32 skipButton = PAD_NONE;
    switch (g_CurrentStream) {
    case 0:
        skipButton = PAD_START;
        break;
    case 1:
        skipButton = PAD_START;
        break;
    case 2:
        skipButton = PAD_CROSS | PAD_CIRCLE | PAD_START;
        break;
    case 3:
        skipButton = PAD_CROSS | PAD_CIRCLE | PAD_START;
        break;
    }
    func_psp_08912820(g_CurrentStream, skipButton);
    D_8003C728 = 0;
    g_IsUsingCd = 0;
}
