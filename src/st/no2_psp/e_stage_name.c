// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no2/no2.h"

extern s32 g_UserLanguage;

static u8 D_pspeu_0925C670[] = {
#include "../no2/gen/D_pspeu_0925C670.h"
};

static u8 D_pspeu_0925C8A0[] = {
#include "../no2/gen/D_pspeu_0925C8A0.h"
};

static u8 D_pspeu_0925CAF8[] = {
#include "../no2/gen/D_pspeu_0925CAF8.h"
};

static u8 D_pspeu_0925CD88[] = {
#include "../no2/gen/D_pspeu_0925CD88.h"
};

static u8 D_pspeu_0925CF98[] = {
#include "../no2/gen/D_pspeu_0925CF98.h"
};

static u_long* D_pspeu_0925D1E8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 128, 128, D_pspeu_0925C670),
    GFX_TERMINATE(),
};

static u8* D_pspeu_0925D200[] = {
    D_pspeu_0925C670, D_pspeu_0925CF98, D_pspeu_0925CAF8,
    D_pspeu_0925CD88, D_pspeu_0925C8A0,
};

void func_psp_0923C0C0(void) {
    D_pspeu_0925D1E8[3] = (u_long*)D_pspeu_0925D200[g_UserLanguage - 1];
    func_91040A0(D_pspeu_0925D1E8);
}

#include "../entity_stage_name_popup_jp.h"
