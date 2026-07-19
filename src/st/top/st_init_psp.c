// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

extern LayoutEntity* D_8D2E380;
extern LayoutEntity* D_8D2E454;

extern Overlay OVL_EXPORT(Overlay);

static u8 cutscene_script_post_fight_it[] = {
#include "gen/cutscene_script_post_fight_it.h"
#include "gen/cutscene_data_post_fight_it.h"
};

static u8 cutscene_script_post_fight_sp[] = {
#include "gen/cutscene_script_post_fight_sp.h"
#include "gen/cutscene_data_post_fight_sp.h"
};
static u8 cutscene_script_post_fight_fr[] = {
#include "gen/cutscene_script_post_fight_fr.h"
#include "gen/cutscene_data_post_fight_fr.h"
};
static u8 cutscene_script_post_fight_ge[] = {
#include "gen/cutscene_script_post_fight_ge.h"
#include "gen/cutscene_data_post_fight_ge.h"
};
static u8 cutscene_script_post_fight_en[] = {
#include "gen/cutscene_script_post_fight_en.h"
#include "gen/cutscene_data_post_fight_en.h"
};

static u8 cutscene_script_talk_it[] = {
#include "gen/cutscene_script_talk_it.h"
#include "gen/cutscene_data_talk_it.h"
};
static u8 cutscene_script_talk_sp[] = {
#include "gen/cutscene_script_talk_sp.h"
#include "gen/cutscene_data_talk_sp.h"
};
static u8 cutscene_script_talk_fr[] = {
#include "gen/cutscene_script_talk_fr.h"
#include "gen/cutscene_data_talk_fr.h"
};
static u8 cutscene_script_talk_ge[] = {
#include "gen/cutscene_script_talk_ge.h"
#include "gen/cutscene_data_talk_ge.h"
};
static u8 cutscene_script_talk_en[] = {
#include "gen/cutscene_script_talk_en.h"
#include "gen/cutscene_data_talk_en.h"
};

s32 D_us_80182E44 = 0x08D30C20;

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_16);
s32 E_ID(STAIR_SWITCH);
s32 E_ID(SECRET_STAIRS);
s32 E_ID(UNK_19);
s32 E_ID(UNK_1A);
s32 E_ID(UNK_1B);
s32 E_ID(UNK_1C);
s32 E_ID(UNK_1D);
s32 E_ID(UNK_1E);
s32 E_ID(UNK_1F);
s32 E_ID(UNK_20);
s32 E_ID(FLEA_RIDER);
s32 E_ID(UNK_22);
s32 E_ID(CUTSCENE);
s32 E_ID(UNK_24);
s32 E_ID(UNK_25);
s32 E_ID(UNK_26);
s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(AXE_KNIGHT_BLUE);
s32 E_ID(AXE_KNIGHT_AXE);
s32 E_ID(AXE_KNIGHT_AXE_2);
s32 E_ID(UNK_ENTITY);

u8* post_fight_script_ptr1;
u8* post_fight_script_ptr2;
u8* talk_script_ptr1;
u8* talk_script_ptr2;
u8* talk_script_ptr3;

#include "../get_lang_at.h"

static void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(UNK_16);
    SET_E_ID(STAIR_SWITCH);
    SET_E_ID(SECRET_STAIRS);
    SET_E_ID(UNK_19);
    SET_E_ID(UNK_1A);
    SET_E_ID(UNK_1B);
    SET_E_ID(UNK_1C);
    SET_E_ID(UNK_1D);
    SET_E_ID(UNK_1E);
    SET_E_ID(UNK_1F);
    SET_E_ID(UNK_20);
    SET_E_ID(FLEA_RIDER);
    SET_E_ID(UNK_22);
    SET_E_ID(CUTSCENE);
    SET_E_ID(UNK_24);
    SET_E_ID(UNK_25);
    SET_E_ID(UNK_26);
    SET_E_ID(BREAKABLE_DEBRIS);
    SET_E_ID(AXE_KNIGHT_BLUE);
    SET_E_ID(AXE_KNIGHT_AXE);
    SET_E_ID(AXE_KNIGHT_AXE_2);
    SET_E_ID(UNK_ENTITY);
}

void OVL_EXPORT(Load)(void) {
    post_fight_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);
    post_fight_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);
    talk_script_ptr1 = GetLangAt(
        4, (u8*)cutscene_script_talk_en, (u8*)cutscene_script_talk_fr,
        (u8*)cutscene_script_talk_sp, (u8*)cutscene_script_talk_ge,
        (u8*)cutscene_script_talk_it);
    talk_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_talk_en, (u8*)cutscene_script_talk_fr,
        (u8*)cutscene_script_talk_sp, (u8*)cutscene_script_talk_ge,
        (u8*)cutscene_script_talk_it);
    talk_script_ptr3 = GetLangAt(
        0, (u8*)cutscene_script_talk_en, (u8*)cutscene_script_talk_fr,
        (u8*)cutscene_script_talk_sp, (u8*)cutscene_script_talk_ge,
        (u8*)cutscene_script_talk_it);

    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2E380;
    g_pStObjLayoutVertical = &D_8D2E454;
    func_psp_0892A018();
    func_psp_08929FA8(D_us_80182E44, 0xC5);
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
