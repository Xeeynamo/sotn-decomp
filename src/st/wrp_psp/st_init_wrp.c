// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"
#include "../pfn_entity_update.h"

// entity table to allocate new entities
extern PfnEntityUpdate* PfnEntityUpdates;

extern LayoutEntity* D_8D2DE7C;
extern LayoutEntity* D_8D2DF50;

// entity table to allocate new entities
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern Overlay OVL_EXPORT(Overlay);

extern s32 E_ID(ID_11);
extern s32 E_ID(ID_12);
extern s32 E_ID(ID_13);
extern s32 E_ID(ID_14);
extern s32 E_ID(ID_15);
extern s32 E_ID(ID_16);
extern s32 E_ID(SMALL_ROCKS);

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(ID_15) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(SMALL_ROCKS) = 0x17;
}

void func_psp_092447C0(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DE7C;
    g_pStObjLayoutVertical = &D_8D2DF50;
    func_892A018();
    memcpy((u8*)&g_api, (u8*)&OVL_EXPORT(Overlay), sizeof(Overlay));
}
