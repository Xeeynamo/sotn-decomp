// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DE7C;
extern LayoutEntity* D_8D2DF50;

extern Overlay OVL_EXPORT(Overlay);

static s32 E_ID(ID_11);
static s32 E_ID(ID_12);
static s32 E_ID(ID_13);
static s32 E_ID(ID_14);
static s32 E_ID(ID_15);
static s32 E_ID(ID_16);
s32 E_ID(SMALL_ROCKS);

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(ID_15) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(SMALL_ROCKS) = 0x17;
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DE7C;
    g_pStObjLayoutVertical = &D_8D2DF50;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
