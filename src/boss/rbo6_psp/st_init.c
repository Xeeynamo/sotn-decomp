// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

#include "../../st/get_lang_at.h"

extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(UNK_16);
extern s32 E_ID(UNK_17);
extern s32 E_ID(UNK_18);
extern s32 E_ID(UNK_19);
extern s32 E_ID(UNK_1A);
extern s32 E_ID(UNK_1B);
extern s32 E_ID(UNK_1C);
extern s32 E_ID(UNK_1D);
extern s32 E_ID(UNK_1E);
extern s32 E_ID(UNK_1F);
extern s32 E_ID(UNK_20);
extern s32 E_ID(UNK_21);
extern s32 E_ID(UNK_22);
extern s32 E_ID(UNK_23);
extern s32 E_ID(UNK_24);
extern s32 E_ID(UNK_25);
extern s32 E_ID(UNK_26);
extern s32 E_ID(UNK_27);
extern s32 E_ID(UNK_28);
extern s32 E_ID(UNK_29);
extern s32 E_ID(UNK_2A);
extern s32 E_ID(UNK_2B);
extern s32 E_ID(UNK_2C);
extern s32 E_ID(UNK_2D);
extern s32 E_ID(BACKGROUND_VORTEX);
extern s32 E_ID(UNK_2F);
extern s32 E_ID(UNK_30);
extern s32 E_ID(UNK_31);
extern s32 E_ID(UNK_32);

void InitEntityIds(void) {
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
    SET_E_ID(UNK_21);
    SET_E_ID(UNK_22);
    SET_E_ID(UNK_23);
    SET_E_ID(UNK_24);
    SET_E_ID(UNK_25);
    SET_E_ID(UNK_26);
    SET_E_ID(UNK_27);
    SET_E_ID(UNK_28);
    SET_E_ID(UNK_29);
    SET_E_ID(UNK_2A);
    SET_E_ID(UNK_2B);
    SET_E_ID(UNK_2C);
    SET_E_ID(UNK_2D);
    SET_E_ID(BACKGROUND_VORTEX);
    SET_E_ID(UNK_2F);
    SET_E_ID(UNK_30);
    SET_E_ID(UNK_31);
    SET_E_ID(UNK_32);
}

#include "../../st/pfn_entity_update.h"

extern u8 D_pspeu_09255AE0[];
extern u8 D_pspeu_09255578[];
extern u8 D_pspeu_09255318[];
extern u8 D_pspeu_09255818[];
extern u8 D_pspeu_09255048[];
extern u8 D_pspeu_09256968[];
extern u8 D_pspeu_09256308[];
extern u8 D_pspeu_09256028[];
extern u8 D_pspeu_09256638[];
extern u8 D_pspeu_09255D28[];
extern u8* D_pspeu_0926BF28;
extern u8* D_pspeu_0926BF20;
extern u8* D_pspeu_0926BF18;
extern u8* D_pspeu_0926BF10;
extern LayoutEntity* D_8D2DE98;
extern LayoutEntity* D_8D2DF6C;
extern AbbreviatedOverlay2 g_BossOverlay;

void RBO6_Load(void) {
    D_pspeu_0926BF28 =
        GetLangAt(0, D_pspeu_09255AE0, D_pspeu_09255578, D_pspeu_09255318,
                  D_pspeu_09255818, D_pspeu_09255048);
    D_pspeu_0926BF20 =
        GetLangAt(0, D_pspeu_09255AE0, D_pspeu_09255578, D_pspeu_09255318,
                  D_pspeu_09255818, D_pspeu_09255048);
    D_pspeu_0926BF18 =
        GetLangAt(0, D_pspeu_09256968, D_pspeu_09256308, D_pspeu_09256028,
                  D_pspeu_09256638, D_pspeu_09255D28);
    D_pspeu_0926BF10 =
        GetLangAt(0, D_pspeu_09256968, D_pspeu_09256308, D_pspeu_09256028,
                  D_pspeu_09256638, D_pspeu_09255D28);
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DE98;
    g_pStObjLayoutVertical = &D_8D2DF6C;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
