// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcen/rcen.h"

#include "../pfn_entity_update.h"

#include <cutscene.h>

extern LayoutEntity* D_8D2DEF0;
extern LayoutEntity* D_8D2DFC4;

extern Overlay OVL_EXPORT(Overlay);

static u8 cutscene_script_pre_fight_it[] = {
#include "gen/cutscene_script_pre_fight_it.h"
};
static u8 cutscene_script_pre_fight_sp[] = {
#include "gen/cutscene_script_pre_fight_sp.h"
};
static u8 cutscene_script_pre_fight_fr[] = {
#include "gen/cutscene_script_pre_fight_fr.h"
};
static u8 cutscene_script_pre_fight_ge[] = {
#include "gen/cutscene_script_pre_fight_ge.h"
};
static u8 cutscene_script_pre_fight_en[] = {
#include "gen/cutscene_script_pre_fight_en.h"
};

static u8 cutscene_script_post_fight_it[] = {
#include "gen/cutscene_script_post_fight_it.h"
};
static u8 cutscene_script_post_fight_sp[] = {
#include "gen/cutscene_script_post_fight_sp.h"
};
static u8 cutscene_script_post_fight_fr[] = {
#include "gen/cutscene_script_post_fight_fr.h"
};
static u8 cutscene_script_post_fight_ge[] = {
#include "gen/cutscene_script_post_fight_ge.h"
};
static u8 cutscene_script_post_fight_en[] = {
#include "gen/cutscene_script_post_fight_en.h"
};

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(SHAFT);
s32 E_ID(UNK_17);
s32 E_ID(UNK_18);
s32 E_ID(UNK_19);
s32 E_ID(UNK_1A);
s32 E_ID(UNK_1B);
s32 E_ID(UNK_1C);
s32 E_ID(UNK_1D);
s32 E_ID(UNK_1E);
s32 E_ID(UNK_1F);
s32 E_ID(UNK_20);
s32 E_ID(CUTSCENE_DIALOGUE);
s32 E_ID(UNK_22);
s32 E_ID(UNK_23);
s32 E_ID(UNK_24);
s32 E_ID(UNK_ID1B);
s32 E_ID(UNK_26);
s32 E_ID(UNK_27);
s32 E_ID(UNK_28);

u8* OVL_EXPORT(cutscene_script);
u8* pre_fight_script_ptr1;
u8* pre_fight_script_ptr2;
u8* post_fight_script_ptr1;
u8* post_fight_script_ptr2;

#include "../get_lang_at.h"

static void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(SHAFT);
    SET_E_ID(UNK_17);
    SET_E_ID(UNK_18);
    SET_E_ID(UNK_19);
    SET_E_ID(UNK_1A);
    SET_E_ID(UNK_1B);
    SET_E_ID(UNK_1C);
    SET_E_ID(UNK_1D);
    SET_E_ID(UNK_1E);
    SET_E_ID(UNK_1F);
    SET_E_ID(UNK_20);
    SET_E_ID(CUTSCENE_DIALOGUE);
    SET_E_ID(UNK_22);
    SET_E_ID(UNK_23);
    SET_E_ID(UNK_24);
    SET_E_ID(UNK_ID1B);
    SET_E_ID(UNK_26);
    SET_E_ID(UNK_27);
    SET_E_ID(UNK_28);
}

void OVL_EXPORT(Load)(void) {
    OVL_EXPORT(cutscene_script) = GetLangAt(
        4, (u8*)cutscene_script_pre_fight_en, (u8*)cutscene_script_pre_fight_fr,
        (u8*)cutscene_script_pre_fight_sp, (u8*)cutscene_script_pre_fight_ge,
        (u8*)cutscene_script_pre_fight_it);
    pre_fight_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_pre_fight_en, (u8*)cutscene_script_pre_fight_fr,
        (u8*)cutscene_script_pre_fight_sp, (u8*)cutscene_script_pre_fight_ge,
        (u8*)cutscene_script_pre_fight_it);
    pre_fight_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_pre_fight_en, (u8*)cutscene_script_pre_fight_fr,
        (u8*)cutscene_script_pre_fight_sp, (u8*)cutscene_script_pre_fight_ge,
        (u8*)cutscene_script_pre_fight_it);
    post_fight_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);
    post_fight_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);

    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DEF0;
    g_pStObjLayoutVertical = &D_8D2DFC4;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
