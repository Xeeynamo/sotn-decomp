// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"
#include "../pfn_entity_update.h"

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_16);
s32 E_ID(CASTLE_WALL1);
s32 E_ID(CASTLE_WALL2);
s32 E_ID(STAIRCASE);
s32 E_ID(UNK_1A);
s32 E_ID(UNK_1B);
s32 E_ID(UNK_1C);
s32 E_ID(UNK_1D);
s32 E_ID(UNK_1E);
s32 E_ID(UNK_1F);
s32 E_ID(UNK_20);
s32 E_ID(UNK_21);
s32 E_ID(UNK_22);
s32 E_ID(UNK_23);
s32 E_ID(UNK_24);
s32 E_ID(UNK_25);
s32 E_ID(UNK_26);
s32 E_ID(UNK_27);
s32 E_ID(IMP);
s32 E_ID(IMP_SMOKE);
s32 E_ID(CLOUDS);
s32 E_ID(BACKGROUND_SKY_LAND);
s32 E_ID(UNK_2C);
s32 E_ID(SPIKES);
s32 E_ID(SPIKES_PARTS);
s32 E_ID(SPIKES_DUST);
s32 E_ID(SPIKES_DAMAGE);
s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(UNK_32);
s32 E_ID(UNK_33);
s32 E_ID(UNK_34);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(UNK_16);
    SET_E_ID(CASTLE_WALL1);
    SET_E_ID(CASTLE_WALL2);
    SET_E_ID(STAIRCASE);
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
    SET_E_ID(IMP);
    SET_E_ID(IMP_SMOKE);
    SET_E_ID(CLOUDS);
    SET_E_ID(BACKGROUND_SKY_LAND);
    SET_E_ID(UNK_2C);
    SET_E_ID(SPIKES);
    SET_E_ID(SPIKES_PARTS);
    SET_E_ID(SPIKES_DUST);
    SET_E_ID(SPIKES_DAMAGE);
    SET_E_ID(BREAKABLE_DEBRIS);
    SET_E_ID(UNK_32);
    SET_E_ID(UNK_33);
    SET_E_ID(UNK_34);
}

extern LayoutEntity* D_8D2E1B0;
extern LayoutEntity* D_8D2E284;
extern AbbreviatedOverlay g_Overlay;

void RDAI_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2E1B0;
    g_pStObjLayoutVertical = &D_8D2E284;
    func_892A018();
    memcpy(&g_api.o, &g_Overlay, 0x40);
}
