// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"
#include "../../st/pfn_entity_update.h"

extern LayoutEntity* D_8D2DEC0;
extern LayoutEntity* D_8D2DF94;
extern Overlay g_BossOverlay;

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(SPLASH_WATER);
s32 E_ID(WATER_DROP);
s32 E_ID(UNK_1C);
s32 E_ID(UNK_1D);
s32 E_ID(UNK_2D);
s32 E_ID(UNK_2E);
s32 E_ID(UNK_2F);
s32 E_ID(UNK_30);
s32 E_ID(UNK_31);
s32 E_ID(UNK_32);
s32 E_ID(UNK_33);
s32 E_ID(UNK_34);
s32 E_ID(UNK_35);
s32 E_ID(UNK_36);
s32 E_ID(UNK_37);
s32 E_ID(UNK_38);
s32 E_ID(UNK_39);
s32 E_ID(UNK_3A);
s32 E_ID(UNK_3B);
s32 E_ID(UNK_3C);
s32 E_ID(EXPLODE_PUFF_OPAQUE);
s32 E_ID(UNK_3E);
s32 E_ID(BREAKABLE_WALL_DEBRIS);
s32 E_ID(LIFE_UP_SPAWN);
s32 E_ID(UNK_41);
s32 E_ID(UNK_42);
s32 E_ID(UNK_43);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(SPLASH_WATER);
    SET_E_ID(WATER_DROP);
    SET_E_ID(UNK_1C);
    SET_E_ID(UNK_1D);
    SET_E_ID(UNK_2D);
    SET_E_ID(UNK_2E);
    SET_E_ID(UNK_2F);
    SET_E_ID(UNK_30);
    SET_E_ID(UNK_31);
    SET_E_ID(UNK_32);
    SET_E_ID(UNK_33);
    SET_E_ID(UNK_34);
    SET_E_ID(UNK_35);
    SET_E_ID(UNK_36);
    SET_E_ID(UNK_37);
    SET_E_ID(UNK_38);
    SET_E_ID(UNK_39);
    SET_E_ID(UNK_3A);
    SET_E_ID(UNK_3B);
    SET_E_ID(UNK_3C);
    SET_E_ID(EXPLODE_PUFF_OPAQUE);
    SET_E_ID(UNK_3E);
    SET_E_ID(BREAKABLE_WALL_DEBRIS);
    SET_E_ID(LIFE_UP_SPAWN);
    SET_E_ID(UNK_41);
    SET_E_ID(UNK_42);
    SET_E_ID(UNK_43);
}

void BO3_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DEC0;
    g_pStObjLayoutVertical = &D_8D2DF94;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
