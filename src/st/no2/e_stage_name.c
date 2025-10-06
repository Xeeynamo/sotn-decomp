// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

#define STAGE_NAME_LOAD_GFX

#ifdef VERSION_PSP
extern s32 g_UserLanguage;

static u8 stage_name_en[] = {
#include "gen/stage_name_en.h"
};
static u8 stage_name_it[] = {
#include "gen/stage_name_it.h"
};
static u8 stage_name_sp[] = {
#include "gen/stage_name_sp.h"
};
static u8 stage_name_ge[] = {
#include "gen/stage_name_ge.h"
};
static u8 stage_name_fr[] = {
#include "gen/stage_name_fr.h"
};

static u_long* gfxBank[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 128, 128, stage_name_en),
    GFX_TERMINATE(),
};

static u8* stage_name_gfx[] = {
    stage_name_en, stage_name_fr, stage_name_sp, stage_name_ge, stage_name_it,
};

void LoadStageNameGraphics(void) {
    gfxBank[3] = (u_long*)stage_name_gfx[g_UserLanguage - 1];
    func_91040A0(gfxBank);
}

#include "../entity_stage_name_popup_jp.h"
#else
#include "../e_stage_name.h"
#endif
