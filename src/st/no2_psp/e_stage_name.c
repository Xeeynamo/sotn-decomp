// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no2/no2.h"

extern s32 g_UserLanguage;
extern u_long* D_pspeu_0925D1E8[];
extern u8* D_pspeu_0925D1F4;
extern u8* D_pspeu_0925D200[];

void func_psp_0923C0C0(void) {
    D_pspeu_0925D1F4 = D_pspeu_0925D200[g_UserLanguage - 1];
    func_91040A0(D_pspeu_0925D1E8);
}

#include "../entity_stage_name_popup_jp.h"
