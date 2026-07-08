// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcen/rcen.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DEF0;
extern LayoutEntity* D_8D2DFC4;

extern Overlay OVL_EXPORT(Overlay);

extern char cutscene_script_1_it[];
extern char cutscene_script_1_sp[];
extern char cutscene_script_1_fr[];
extern char cutscene_script_1_ge[];
extern char cutscene_script_1_en[];

extern char cutscene_script_2_it[];
extern char cutscene_script_2_sp[];
extern char cutscene_script_2_fr[];
extern char cutscene_script_2_ge[];
extern char cutscene_script_2_en[];

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_16);
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
u8* D_pspeu_09269628;
u8* D_pspeu_09269620;
u8* D_pspeu_09269618;
u8* D_pspeu_09269610;

#include "../get_lang_at.h"

static void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(UNK_16);
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
        4, (u8*)cutscene_script_1_en, (u8*)cutscene_script_1_fr,
        (u8*)cutscene_script_1_sp, (u8*)cutscene_script_1_ge,
        (u8*)cutscene_script_1_it);
    D_pspeu_09269628 = GetLangAt(
        0, (u8*)cutscene_script_1_en, (u8*)cutscene_script_1_fr,
        (u8*)cutscene_script_1_sp, (u8*)cutscene_script_1_ge,
        (u8*)cutscene_script_1_it);
    D_pspeu_09269620 = GetLangAt(
        0, (u8*)cutscene_script_1_en, (u8*)cutscene_script_1_fr,
        (u8*)cutscene_script_1_sp, (u8*)cutscene_script_1_ge,
        (u8*)cutscene_script_1_it);
    D_pspeu_09269618 = GetLangAt(
        0, (u8*)cutscene_script_2_en, (u8*)cutscene_script_2_fr,
        (u8*)cutscene_script_2_sp, (u8*)cutscene_script_2_ge,
        (u8*)cutscene_script_2_it);
    D_pspeu_09269610 = GetLangAt(
        0, (u8*)cutscene_script_2_en, (u8*)cutscene_script_2_fr,
        (u8*)cutscene_script_2_sp, (u8*)cutscene_script_2_ge,
        (u8*)cutscene_script_2_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DEF0;
    g_pStObjLayoutVertical = &D_8D2DFC4;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
