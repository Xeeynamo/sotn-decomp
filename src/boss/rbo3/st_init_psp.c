// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"
#include "../../st/pfn_entity_update.h"

extern LayoutEntity* D_8D2DE2C;
extern LayoutEntity* D_8D2DF00;
extern Overlay g_BossOverlay;

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_22);
s32 E_ID(MEDUSA);
s32 E_ID(UNK_24);
s32 E_ID(UNK_25);
s32 E_ID(UNK_26);
s32 E_ID(UNK_27);
s32 E_ID(UNK_28);
s32 E_ID(UNK_29);
s32 E_ID(LIFE_UP_SPAWN);
s32 E_ID(CLOUDS);
s32 E_ID(UNK_32);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(UNK_22);
    SET_E_ID(MEDUSA);
    SET_E_ID(UNK_24);
    SET_E_ID(UNK_25);
    SET_E_ID(UNK_26);
    SET_E_ID(UNK_27);
    SET_E_ID(UNK_28);
    SET_E_ID(UNK_29);
    SET_E_ID(LIFE_UP_SPAWN);
    SET_E_ID(CLOUDS);
    SET_E_ID(UNK_32);
}

void RBO3_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DE2C;
    g_pStObjLayoutVertical = &D_8D2DF00;
    func_892A018();
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
