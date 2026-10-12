// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"
#include "../../st/pfn_entity_update.h"

extern LayoutEntity* D_8D2DE88;
extern LayoutEntity* D_8D2DF5C;
extern Overlay g_BossOverlay;

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
s32 E_ID(LIFE_UP_SPAWN);

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
    SET_E_ID(LIFE_UP_SPAWN);
}

void RBO4_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DE88;
    g_pStObjLayoutVertical = &D_8D2DF5C;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
