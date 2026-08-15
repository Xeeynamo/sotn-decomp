// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"
#include "../../st/pfn_entity_update.h"

extern LayoutEntity* D_8D2E490;
extern LayoutEntity* D_8D2E564;
extern Overlay g_BossOverlay;

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(BOSS_DOOR);
s32 E_ID(UNK_17);
s32 E_ID(GRANFALOON);
s32 E_ID(GRANFALOON_TENTACLE);
s32 E_ID(TENTACLE_HEAD);
s32 E_ID(TENTACLE_LASER);
s32 E_ID(BODY_PART_SHELL);
s32 E_ID(BODY_PART_DEAD_PIECE);
s32 E_ID(UNK_1E);
s32 E_ID(UNK_1F);
s32 E_ID(ZOMBIE_FALLING);
s32 E_ID(ZOMBIE_ENEMY);
s32 E_ID(EXPLOSION_FLAME);
s32 E_ID(UNK_23);
s32 E_ID(HOMING_LASER);
s32 E_ID(LIFE_UPSPAWN);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(BOSS_DOOR);
    SET_E_ID(UNK_17);
    SET_E_ID(GRANFALOON);
    SET_E_ID(GRANFALOON_TENTACLE);
    SET_E_ID(TENTACLE_HEAD);
    SET_E_ID(TENTACLE_LASER);
    SET_E_ID(BODY_PART_SHELL);
    SET_E_ID(BODY_PART_DEAD_PIECE);
    SET_E_ID(UNK_1E);
    SET_E_ID(UNK_1F);
    SET_E_ID(ZOMBIE_FALLING);
    SET_E_ID(ZOMBIE_ENEMY);
    SET_E_ID(EXPLOSION_FLAME);
    SET_E_ID(UNK_23);
    SET_E_ID(HOMING_LASER);
    SET_E_ID(LIFE_UPSPAWN);
}

void OvlLoad(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2E490;
    g_pStObjLayoutVertical = &D_8D2E564;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
