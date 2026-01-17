// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

void OVL_EXPORT(Init)() {
    switch (g_GameEngineStep) {
    case Upd_Eng_Init:
        if (g_IsUsingCd) {
            break;
        }
        g_GameClearFlag = SAVE_FLAG_CLEAR;
        D_8003C728 = 1;
        g_CurrentStream = 0;
        g_GameEngineStep++;
        break;

    case Upd_Eng_MenuFadeIn:
#ifdef VERSION_PSP
        func_psp_090FFAB8();
#else
        func_801B9C80();
#endif
#ifndef VERSION_PC // skip Konami logo
        if (D_8003C728) {
            break;
        }
#endif
        g_GameClearFlag = SAVE_FLAG_NORMAL;
        g_CurrentStream = 0;
        func_801B18F4();
        g_GameState = Game_Title;
        g_GameEngineStep = Upd_Eng_Init;
        break;
    }
}
