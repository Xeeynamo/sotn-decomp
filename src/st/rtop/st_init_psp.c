// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rtop/rtop.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DF3C;
extern LayoutEntity* D_8D2E010;

extern Overlay g_StageOverlay;

s32 E_ID(ID_11);
s32 E_ID(ID_12);
s32 E_ID(UNK_ID_13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(ID_16);
s32 E_ID(ID_17);
s32 E_ID(STAIR_SEGMENT);
s32 E_ID(ID_19);
s32 E_ID(ID_1A);
s32 E_ID(ID_1B);
s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(ID_1D);
s32 E_ID(ID_1E);
s32 E_ID(ID_1F);
s32 E_ID(ID_20);
s32 E_ID(ID_21);
s32 E_ID(YORICK);
s32 E_ID(YORICK_SKULL);
s32 E_ID(SKELETON_PARTS);
s32 E_ID(TOMBSTONE);
s32 E_ID(SKULL_LORD);
s32 E_ID(SKULL_LORD_OUTLINE);
s32 E_ID(SKULL_LORD_EYE);
s32 E_ID(SKULL_LORD_PIECES);

static void InitEntityIds(void) {
    SET_E_ID(ID_11);
    SET_E_ID(ID_12);
    SET_E_ID(UNK_ID_13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(ID_16);
    SET_E_ID(ID_17);
    SET_E_ID(STAIR_SEGMENT);
    SET_E_ID(ID_19);
    SET_E_ID(ID_1A);
    SET_E_ID(ID_1B);
    SET_E_ID(BREAKABLE_DEBRIS);
    SET_E_ID(ID_1D);
    SET_E_ID(ID_1E);
    SET_E_ID(ID_1F);
    SET_E_ID(ID_20);
    SET_E_ID(ID_21);
    SET_E_ID(YORICK);
    SET_E_ID(YORICK_SKULL);
    SET_E_ID(SKELETON_PARTS);
    SET_E_ID(TOMBSTONE);
    SET_E_ID(SKULL_LORD);
    SET_E_ID(SKULL_LORD_OUTLINE);
    SET_E_ID(SKULL_LORD_EYE);
    SET_E_ID(SKULL_LORD_PIECES);
}

void OvlLoad(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DF3C;
    g_pStObjLayoutVertical = &D_8D2E010;
    func_psp_0892A018();
    memcpy(&g_api.o, &g_StageOverlay, sizeof(Overlay));
}
