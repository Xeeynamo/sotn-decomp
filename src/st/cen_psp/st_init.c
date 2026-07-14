// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

extern LayoutEntity* D_pspeu_09266B68;
extern LayoutEntity* D_pspeu_09266C40;

extern Overlay OVL_EXPORT(Overlay);

static u8 cutscene_script_prefight_it[] = {
#include "../cen/gen/cutscene_script_prefight_it.h"
};
static u8 cutscene_script_prefight_sp[] = {
#include "../cen/gen/cutscene_script_prefight_sp.h"
};
static u8 cutscene_script_prefight_fr[] = {
#include "../cen/gen/cutscene_script_prefight_fr.h"
};
static u8 cutscene_script_prefight_ge[] = {
#include "../cen/gen/cutscene_script_prefight_ge.h"
};
static u8 cutscene_script_prefight_en[] = {
#include "../cen/gen/cutscene_script_prefight_en.h"
};

static u8 cutscene_script_postfight_it[] = {
#include "../cen/gen/cutscene_script_postfight_it.h"
};
static u8 cutscene_script_postfight_sp[] = {
#include "../cen/gen/cutscene_script_postfight_sp.h"
};
static u8 cutscene_script_postfight_fr[] = {
#include "../cen/gen/cutscene_script_postfight_fr.h"
};
static u8 cutscene_script_postfight_ge[] = {
#include "../cen/gen/cutscene_script_postfight_ge.h"
};
static u8 cutscene_script_postfight_en[] = {
#include "../cen/gen/cutscene_script_postfight_en.h"
};

static u8 cutscene_script_glasses_it[] = {
#include "../cen/gen/cutscene_script_glasses_it.h"
};
static u8 cutscene_script_glasses_sp[] = {
#include "../cen/gen/cutscene_script_glasses_sp.h"
};
static u8 cutscene_script_glasses_fr[] = {
#include "../cen/gen/cutscene_script_glasses_fr.h"
};
static u8 cutscene_script_glasses_ge[] = {
#include "../cen/gen/cutscene_script_glasses_ge.h"
};
static u8 cutscene_script_glasses_en[] = {
#include "../cen/gen/cutscene_script_glasses_en.h"
};

static u8 cutscene_script_helphim_it[] = {
#include "../cen/gen/cutscene_script_helphim_it.h"
};
static u8 cutscene_script_helphim_sp[] = {
#include "../cen/gen/cutscene_script_helphim_sp.h"
};
static u8 cutscene_script_helphim_fr[] = {
#include "../cen/gen/cutscene_script_helphim_fr.h"
};
static u8 cutscene_script_helphim_ge[] = {
#include "../cen/gen/cutscene_script_helphim_ge.h"
};
static u8 cutscene_script_helphim_en[] = {
#include "../cen/gen/cutscene_script_helphim_en.h"
};

// entity ids
s32 E_ID(BACKGROUND_BLOCK);
static s32 E_ID(ID_12);
static s32 E_ID(ID_13);
static s32 E_ID(EXPLOSION_VARIANTS);
static s32 E_ID(GREY_PUFF);
s32 E_ID(CUTSCENE);
static s32 E_ID(PLATFORM);
static s32 E_ID(BOSS_MARIA);
static s32 E_ID(ROOM_DARKNESS);
static s32 E_ID(ELEVATOR_STATIONARY_UNUSED);
s32 E_ID(ELEVATOR_STATIONARY);
static s32 E_ID(MOVING_ELEVATOR);
s32 E_ID(BREAKABLE_DEBRIS);

// cutscene pointers
u8* pre_fight_script_ptr1;
u8* post_fight_script_ptr1;
u8* glasses_script_ptr1;
u8* helphim_script_ptr1;
u8* pre_fight_script_ptr2;
u8* post_fight_script_ptr2;
u8* glasses_script_ptr2;
u8* helphim_script_ptr2;

#include "../get_lang_at.h"

static void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(ID_12);
    SET_E_ID(ID_13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(CUTSCENE);
    SET_E_ID(PLATFORM);
    SET_E_ID(BOSS_MARIA);
    SET_E_ID(ROOM_DARKNESS);
    SET_E_ID(ELEVATOR_STATIONARY_UNUSED);
    SET_E_ID(ELEVATOR_STATIONARY);
    SET_E_ID(MOVING_ELEVATOR);
    SET_E_ID(BREAKABLE_DEBRIS);
}

void OVL_EXPORT(Load)(void) {
    pre_fight_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_prefight_en, (u8*)cutscene_script_prefight_fr,
        (u8*)cutscene_script_prefight_sp, (u8*)cutscene_script_prefight_ge,
        (u8*)cutscene_script_prefight_it);
    post_fight_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_postfight_en, (u8*)cutscene_script_postfight_fr,
        (u8*)cutscene_script_postfight_sp, (u8*)cutscene_script_postfight_ge,
        (u8*)cutscene_script_postfight_it);
    glasses_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_glasses_en, (u8*)cutscene_script_glasses_fr,
        (u8*)cutscene_script_glasses_sp, (u8*)cutscene_script_glasses_ge,
        (u8*)cutscene_script_glasses_it);
    helphim_script_ptr1 = GetLangAt(
        0, (u8*)cutscene_script_helphim_en, (u8*)cutscene_script_helphim_fr,
        (u8*)cutscene_script_helphim_sp, (u8*)cutscene_script_helphim_ge,
        (u8*)cutscene_script_helphim_it);

    pre_fight_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_prefight_en, (u8*)cutscene_script_prefight_fr,
        (u8*)cutscene_script_prefight_sp, (u8*)cutscene_script_prefight_ge,
        (u8*)cutscene_script_prefight_it);
    post_fight_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_postfight_en, (u8*)cutscene_script_postfight_fr,
        (u8*)cutscene_script_postfight_sp, (u8*)cutscene_script_postfight_ge,
        (u8*)cutscene_script_postfight_it);
    glasses_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_glasses_en, (u8*)cutscene_script_glasses_fr,
        (u8*)cutscene_script_glasses_sp, (u8*)cutscene_script_glasses_ge,
        (u8*)cutscene_script_glasses_it);
    helphim_script_ptr2 = GetLangAt(
        0, (u8*)cutscene_script_helphim_en, (u8*)cutscene_script_helphim_fr,
        (u8*)cutscene_script_helphim_sp, (u8*)cutscene_script_helphim_ge,
        (u8*)cutscene_script_helphim_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_pspeu_09266B68;
    g_pStObjLayoutVertical = &D_pspeu_09266C40;
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
