// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DE60;
extern LayoutEntity* D_8D2DF34;

extern Overlay OVL_EXPORT(Overlay);

extern char cutscene_script_pre_fight_it[];
extern char cutscene_script_pre_fight_sp[];
extern char cutscene_script_pre_fight_fr[];
extern char cutscene_script_pre_fight_ge[];
extern char cutscene_script_pre_fight_en[];

extern char cutscene_script_post_fight_it[];
extern char cutscene_script_post_fight_sp[];
extern char cutscene_script_post_fight_fr[];
extern char cutscene_script_post_fight_ge[];
extern char cutscene_script_post_fight_en[];

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(3D_BACKGROUND_HOUSE);
s32 E_ID(3D_HOUSE_SPAWNER);
s32 E_ID(BACKGROUND_CLOUDS);
s32 E_ID(SUCCUBUS);
s32 E_ID(SUCCUBUS_PETAL);
s32 E_ID(SUCCUBUS_WING_OVERLAY);
s32 E_ID(SUCCUBUS_CLONE);
s32 E_ID(SUCCUBUS_PINK_BALL_PROJECTILE);
s32 E_ID(SUCCUBUS_WING_SPIKE);
s32 E_ID(SUCCUBUS_WING_SPIKE_TIP);
s32 E_ID(SUCCUBUS_CUTSCENE);
s32 E_ID(CS_MOVE_ALUCARD);
s32 E_ID(FADE_TO_WHITE1);
s32 E_ID(UNK_ID23);
s32 E_ID(FADE_TO_WHITE2);

u8* OVL_EXPORT(cutscene_script);
u8* D_pspeu_092600B8;
u8* D_pspeu_092600B0;
u8* D_pspeu_092600A8;
u8* D_801816C0; // used by e_cutscene_actors
u8* D_801816C4; // used by e_succubus

#include "../get_lang_at.h"

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(3D_BACKGROUND_HOUSE);
    SET_E_ID(3D_HOUSE_SPAWNER);
    SET_E_ID(BACKGROUND_CLOUDS);
    SET_E_ID(SUCCUBUS);
    SET_E_ID(SUCCUBUS_PETAL);
    SET_E_ID(SUCCUBUS_WING_OVERLAY);
    SET_E_ID(SUCCUBUS_CLONE);
    SET_E_ID(SUCCUBUS_PINK_BALL_PROJECTILE);
    SET_E_ID(SUCCUBUS_WING_SPIKE);
    SET_E_ID(SUCCUBUS_WING_SPIKE_TIP);
    SET_E_ID(SUCCUBUS_CUTSCENE);
    SET_E_ID(CS_MOVE_ALUCARD);
    SET_E_ID(FADE_TO_WHITE1);
    SET_E_ID(UNK_ID23);
    SET_E_ID(FADE_TO_WHITE2);
}

void OVL_EXPORT(Load)(void) {
    OVL_EXPORT(cutscene_script) = GetLangAt(
        4, (u8*)cutscene_script_pre_fight_en, (u8*)cutscene_script_pre_fight_fr,
        (u8*)cutscene_script_pre_fight_sp, (u8*)cutscene_script_pre_fight_ge,
        (u8*)cutscene_script_pre_fight_it);
    D_pspeu_092600B8 = GetLangAt(
        0, (u8*)cutscene_script_pre_fight_en, (u8*)cutscene_script_pre_fight_fr,
        (u8*)cutscene_script_pre_fight_sp, (u8*)cutscene_script_pre_fight_ge,
        (u8*)cutscene_script_pre_fight_it);
    D_pspeu_092600B0 = GetLangAt(
        4, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);
    D_pspeu_092600A8 = GetLangAt(
        0, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);
    D_801816C0 = GetLangAt(
        0, (u8*)cutscene_script_pre_fight_en, (u8*)cutscene_script_pre_fight_fr,
        (u8*)cutscene_script_pre_fight_sp, (u8*)cutscene_script_pre_fight_ge,
        (u8*)cutscene_script_pre_fight_it);
    D_801816C4 = GetLangAt(
        0, (u8*)cutscene_script_post_fight_en,
        (u8*)cutscene_script_post_fight_fr, (u8*)cutscene_script_post_fight_sp,
        (u8*)cutscene_script_post_fight_ge, (u8*)cutscene_script_post_fight_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DE60;
    g_pStObjLayoutVertical = &D_8D2DF34;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
