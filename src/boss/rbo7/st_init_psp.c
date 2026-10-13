// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo7.h"
#include "../../st/pfn_entity_update.h"

extern LayoutEntity* D_8D2DDD4;
extern LayoutEntity* D_8D2DEA8;
extern Overlay g_BossOverlay;

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_16);
s32 E_ID(BOSS_FIGHT_MANAGER);
s32 E_ID(LIFE_UP_SPAWN);
s32 E_ID(UNK_19);
s32 E_ID(UNK_1A);
s32 E_ID(HARPY_KICK);
s32 E_ID(UNK_1C);
s32 E_ID(UNK_1D);
s32 E_ID(CTULHU_DEATH);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(UNK_16);
    SET_E_ID(BOSS_FIGHT_MANAGER);
    SET_E_ID(LIFE_UP_SPAWN);
    SET_E_ID(UNK_19);
    SET_E_ID(UNK_1A);
    SET_E_ID(HARPY_KICK);
    SET_E_ID(UNK_1C);
    SET_E_ID(UNK_1D);
    SET_E_ID(CTULHU_DEATH);
}

void RBO7_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DDD4;
    g_pStObjLayoutVertical = &D_8D2DEA8;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
