// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcen/rcen.h"

#include "../pfn_entity_update.h"

#include <cutscene.h>

extern LayoutEntity* D_8D2DEF0;
extern LayoutEntity* D_8D2DFC4;

extern Overlay g_Overlay;

static u8 cutscene_script_pre_fight_it[] = {
#include <gen/cutscene_script_pre_fight_it.h>
};
static u8 cutscene_script_pre_fight_sp[] = {
#include <gen/cutscene_script_pre_fight_sp.h>
};
static u8 cutscene_script_pre_fight_fr[] = {
#include <gen/cutscene_script_pre_fight_fr.h>
};
static u8 cutscene_script_pre_fight_ge[] = {
#include <gen/cutscene_script_pre_fight_ge.h>
};
static u8 cutscene_script_pre_fight_en[] = {
#include <gen/cutscene_script_pre_fight_en.h>
};

static u8 cutscene_script_post_fight_it[] = {
#include <gen/cutscene_script_post_fight_it.h>
};
static u8 cutscene_script_post_fight_sp[] = {
#include <gen/cutscene_script_post_fight_sp.h>
};
static u8 cutscene_script_post_fight_fr[] = {
#include <gen/cutscene_script_post_fight_fr.h>
};
static u8 cutscene_script_post_fight_ge[] = {
#include <gen/cutscene_script_post_fight_ge.h>
};
static u8 cutscene_script_post_fight_en[] = {
#include <gen/cutscene_script_post_fight_en.h>
};

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(SHAFT);
s32 E_ID(SHAFT_MERIDIAN_RINGS);
s32 E_ID(SHAFT_CRYSTAL_BALL);
s32 E_ID(CUTSCENE_SHAFT);
s32 E_ID(SHAFT_ATTACK_ORB);
s32 E_ID(SHAFT_FLAME_TRAIL);
s32 E_ID(SHAFT_FLAME_PILLAR);
s32 E_ID(SHAFT_LIGHTNING);
s32 E_ID(SHAFT_LIGHTNING_HITBOX);
s32 E_ID(SHAFT_ORBIT_ORB);
s32 E_ID(SHAFT_DEATH_FLAMES);
s32 E_ID(CUTSCENE_DIALOGUE);
s32 E_ID(UNK_22);
s32 E_ID(UNK_23);
s32 E_ID(ELEVATOR_STATIONARY_UNUSED);
s32 E_ID(ELEVATOR_STATIONARY);
s32 E_ID(UNK_26);
s32 E_ID(UNK_27);
s32 E_ID(UNK_28);

u8* cutscene_script;
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
    SET_E_ID(SHAFT_MERIDIAN_RINGS);
    SET_E_ID(SHAFT_CRYSTAL_BALL);
    SET_E_ID(CUTSCENE_SHAFT);
    SET_E_ID(SHAFT_ATTACK_ORB);
    SET_E_ID(SHAFT_FLAME_TRAIL);
    SET_E_ID(SHAFT_FLAME_PILLAR);
    SET_E_ID(SHAFT_LIGHTNING);
    SET_E_ID(SHAFT_LIGHTNING_HITBOX);
    SET_E_ID(SHAFT_ORBIT_ORB);
    SET_E_ID(SHAFT_DEATH_FLAMES);
    SET_E_ID(CUTSCENE_DIALOGUE);
    SET_E_ID(UNK_22);
    SET_E_ID(UNK_23);
    SET_E_ID(ELEVATOR_STATIONARY_UNUSED);
    SET_E_ID(ELEVATOR_STATIONARY);
    SET_E_ID(UNK_26);
    SET_E_ID(UNK_27);
    SET_E_ID(UNK_28);
}

void OvlLoad(void) {
    cutscene_script = GetLangAt(
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
    memcpy(&g_api.o, &g_Overlay, sizeof(Overlay));
}
