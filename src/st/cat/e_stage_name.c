// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

#define STAGE_NAME_LOAD_GFX

#ifdef VERSION_PSP
extern s32 g_UserLanguage;

// data
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

static u_long* stage_name[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 64, 128, 128, stage_name_en),
    GFX_TERMINATE(),
};

static u8* get_lang[] = {
    stage_name_en, stage_name_fr, stage_name_sp, stage_name_ge, stage_name_it};
static void LoadStageNameGraphics(void) {
    stage_name[3] = (u_long*)get_lang[g_UserLanguage - 1];
    func_91040A0(stage_name);
}

#include "../entity_stage_name_popup_jp.h"
#else
#include "../e_stage_name.h"
#endif
