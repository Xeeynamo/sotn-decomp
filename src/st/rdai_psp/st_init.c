// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"
#include "../pfn_entity_update.h"
#include "entity_ids.h"

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(UNK_16);
    SET_E_ID(CASTLE_WALL1);
    SET_E_ID(CASTLE_WALL2);
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
