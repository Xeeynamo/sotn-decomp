// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"
#include "../../st/pfn_entity_update.h"

extern LayoutEntity* D_8D2DE34;
extern LayoutEntity* D_8D2DF08;
extern Overlay g_BossOverlay;

extern char cutscene_script_en[];
extern char cutscene_script_fr[];
extern char cutscene_script_sp[];
extern char cutscene_script_ge[];
extern char cutscene_script_it[];

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(CAMERA_BOUNDS);
s32 E_ID(STAINED_GLASS);
s32 E_ID(STAINED_GLASS_BACKGROUND);
s32 E_ID(BLOCK);
s32 E_ID(STATUE);
s32 E_ID(BELL);
s32 E_ID(CASTLE_WALL1);
s32 E_ID(CASTLE_WALL2);
s32 E_ID(STAIRCASE);
s32 E_ID(CLOUDS);
s32 E_ID(BACKGROUND_SKY_LAND);
s32 E_ID(RBO3DOOR);
s32 E_ID(HIPPOGRYPH);
s32 E_ID(UNK_23);
s32 E_ID(UNK_24);
s32 E_ID(HIPPOGRYPH_EGG);
s32 E_ID(UNK_26);
s32 E_ID(FIRE_BREATH);
s32 E_ID(LIFE_UP_SPAWN);
s32 E_ID(PLAY_BOSS_MUSIC);
s32 E_ID(CUTSCENE);
s32 E_ID(CUTSCENE_STAGE);
s32 E_ID(UNK_2C);
s32 E_ID(UNK_2D);
s32 E_ID(UNK_2E);

// Used by bo5/e_cutscene_dialogue/EntityCutscene
u8* cutscene_script;     // bss
u8* cutscene_script_ptr; // bss

#include "../../st/get_lang_at.h"

static void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(CAMERA_BOUNDS);
    SET_E_ID(STAINED_GLASS);
    SET_E_ID(STAINED_GLASS_BACKGROUND);
    SET_E_ID(BLOCK);
    SET_E_ID(STATUE);
    SET_E_ID(BELL);
    SET_E_ID(CASTLE_WALL1);
    SET_E_ID(CASTLE_WALL2);
    SET_E_ID(STAIRCASE);
    SET_E_ID(CLOUDS);
    SET_E_ID(BACKGROUND_SKY_LAND);
    SET_E_ID(RBO3DOOR);
    SET_E_ID(HIPPOGRYPH);
    SET_E_ID(UNK_23);
    SET_E_ID(UNK_24);
    SET_E_ID(HIPPOGRYPH_EGG);
    SET_E_ID(UNK_26);
    SET_E_ID(FIRE_BREATH);
    SET_E_ID(LIFE_UP_SPAWN);
    SET_E_ID(PLAY_BOSS_MUSIC);
    SET_E_ID(CUTSCENE);
    SET_E_ID(CUTSCENE_STAGE);
    SET_E_ID(UNK_2C);
    SET_E_ID(UNK_2D);
    SET_E_ID(UNK_2E);
}

void BO5_Load(void) {
    cutscene_script = GetLangAt(
        0, (u8*)cutscene_script_en, (u8*)cutscene_script_fr,
        (u8*)cutscene_script_sp, (u8*)cutscene_script_ge,
        (u8*)cutscene_script_it);
    cutscene_script_ptr = GetLangAt(
        0, (u8*)cutscene_script_en, (u8*)cutscene_script_fr,
        (u8*)cutscene_script_sp, (u8*)cutscene_script_ge,
        (u8*)cutscene_script_it);
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DE34;
    g_pStObjLayoutVertical = &D_8D2DF08;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
