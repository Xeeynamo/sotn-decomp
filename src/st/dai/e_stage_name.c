// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 g_UserLanguage;
extern u_long* D_pspeu_0925BC00[];
extern u8* D_pspeu_0925BC0C;
extern u8* D_pspeu_0925BC18[];

void func_psp_0923C0C0(void) {
    D_pspeu_0925BC0C = D_pspeu_0925BC18[g_UserLanguage - 1];
    func_91040A0(D_pspeu_0925BC00);
}

#include "../entity_stage_name_popup_jp.h"
#else
#include "../e_stage_name.h"
#endif
