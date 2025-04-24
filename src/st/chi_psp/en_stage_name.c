// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../chi/chi.h"

// these look to be indexed off language,
// but they don't appear to be valid text?
extern char D_psp_09254E10[]; // eng
extern char D_psp_09255D48[]; // fr
extern char D_psp_09255608[]; // es
extern char D_psp_09255948[]; // de
extern char D_psp_092552A8[]; // it

extern s32 g_UserLanguage;
extern u16 D_psp_092560A8[];
extern u8* D_psp_092560B4;
extern u8* D_psp_092560C0[];

void func_psp_0923C0C0(void) {
    D_psp_092560B4 = D_psp_092560C0[g_UserLanguage - 1];
    func_91040A0(D_psp_092560A8);
}

// clang-format off
INCLUDE_ASM("st/chi_psp/nonmatchings/chi_psp/en_stage_name", EntityStageNamePopup);
// clang-format on
