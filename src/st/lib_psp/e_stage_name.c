// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

// these look to be indexed off language,
// but they don't appear to be valid text?
extern char D_psp_0926E170[]; // eng
extern char D_psp_0926EB00[]; // fr
extern char D_psp_0926E5F0[]; // es
extern char D_psp_0926E870[]; // de
extern char D_psp_0926E368[]; // it

extern s32 g_UserLanguage;
extern u_long* D_psp_0926EDD8[];
extern u8* D_psp_0926EDE4;
extern u8* D_psp_0926EDF0[];

void func_psp_0923C0C0(void) {
    D_psp_0926EDE4 = D_psp_0926EDF0[g_UserLanguage - 1];
    func_91040A0(D_psp_0926EDD8);
}

#include "../entity_stage_name_popup_jp.h"
