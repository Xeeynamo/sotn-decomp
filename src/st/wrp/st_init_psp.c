// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DE7C;
extern LayoutEntity* D_8D2DF50;

extern Overlay OVL_EXPORT(Overlay);

static s32 E_ID(ID_11);
static s32 E_ID(ID_12);
static s32 E_ID(ID_13);
static s32 E_ID(EXPLOSION_VARIANTS);
static s32 E_ID(GREY_PUFF);
static s32 E_ID(WARP);
s32 E_ID(SMALL_ROCKS);

void InitEntityIds(void) {
    E_ID(ID_11) = E_ID_11;
    E_ID(ID_12) = E_ID_12;
    E_ID(ID_13) = E_ID_13;
    E_ID(EXPLOSION_VARIANTS) = E_EXPLOSION_VARIANTS;
    E_ID(GREY_PUFF) = E_GREY_PUFF;
    E_ID(WARP) = E_WARP;
    E_ID(SMALL_ROCKS) = E_SMALL_ROCKS;
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DE7C;
    g_pStObjLayoutVertical = &D_8D2DF50;
    func_psp_0892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
