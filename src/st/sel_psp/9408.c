// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"

extern s32 D_91CE5E8;
extern s32 D_91CE5F0;
extern s32 D_psp_09285EC8;
extern s32 D_psp_09285ED0;
extern s32 D_psp_09285ED8;
extern s32 D_psp_09285EE0;

void func_psp_09240A88(void) {
    switch (g_GameEngineStep) {
    case 0:
        if (g_IsUsingCd) {
            break;
        }
        g_IsTimeAttackUnlocked = 1;
        D_91CE5F0 = 1;
        D_91CE5E8 = 0;
        g_GameEngineStep++;
        break;

    case 1:
        func_90FFAB8();
        if (D_91CE5F0) {
            break;
        }
        g_IsTimeAttackUnlocked = 0;
        D_91CE5E8 = 0;
        func_psp_0923F498();
        g_GameState = Game_Title;
        g_GameEngineStep = 0;
        break;
    }
}

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09240B58);

void func_psp_09241BF8(void) {
    func_913D618();
    D_psp_09285EE0 = 0;
    D_psp_09285ED8 = 0;
    D_psp_09285ED0 = 0;
    D_psp_09285EC8 = 0;
}

s32 func_psp_09241C38(s32 arg0) { return 0; }

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09241C50);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09241F70);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09242010);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_092426B0);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_092426D8);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09242920);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09242B40);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09242BA0);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09243000);

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/9408", func_psp_09243028);
