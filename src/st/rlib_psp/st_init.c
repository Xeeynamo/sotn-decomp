// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"
#include "../pfn_entity_update.h"
#include "entity_ids.h"

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
    SET_E_ID(HARPY_KICK);
    SET_E_ID(UNK_1E);
    SET_E_ID(UNK_1F);
    SET_E_ID(UNK_20);
    SET_E_ID(UNK_21);
    SET_E_ID(UNK_22);
    SET_E_ID(UNK_23);
    SET_E_ID(UNK_24);
    SET_E_ID(UNK_25);
    SET_E_ID(EXPLODE_PUFF_OPAQUE);
    SET_E_ID(UNK_27);
    SET_E_ID(UNK_28);
    SET_E_ID(UNK_29);
}

extern LayoutEntity* D_8D2DFC8;
extern LayoutEntity* D_8D2E09C;
extern AbbreviatedOverlay g_StageOverlay;

void RLIB_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DFC8;
    g_pStObjLayoutVertical = &D_8D2E09C;
    func_892A018();
    memcpy(&g_api.o, &g_StageOverlay, 0x40);
}
