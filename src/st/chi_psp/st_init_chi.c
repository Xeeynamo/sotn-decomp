// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../chi/chi.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DFF4;
extern LayoutEntity* D_8D2E0C8;

extern Overlay OVL_EXPORT(Overlay);

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(ID_12);
s32 E_ID(ID_13);
s32 E_ID(ID_14);
s32 E_ID(GREY_PUFF);
s32 E_ID(ID_16);
s32 E_ID(ID_17);
s32 E_ID(ID_18);
s32 E_ID(ID_19);
s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(ID_1B);
s32 E_ID(ID_1C);
s32 E_ID(ID_1D);
s32 E_ID(ID_1E);
s32 E_ID(ID_1F);
s32 E_ID(ID_20);
s32 E_ID(ID_21);
s32 E_ID(ID_22);
s32 E_ID(ID_23);
s32 E_ID(ID_24);
s32 E_ID(ID_25);
s32 E_ID(ID_26);
s32 E_ID(ID_27);
s32 E_ID(ID_28);
s32 E_ID(ID_29);
s32 E_ID(ID_2A);
s32 E_ID(ID_2B);
s32 E_ID(ID_2C);
s32 E_ID(ID_2D);

void InitEntityIds(void) {
    E_ID(BACKGROUND_BLOCK) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(ID_17) = 0x17;
    E_ID(ID_18) = 0x18;
    E_ID(ID_19) = 0x19;
    E_ID(BREAKABLE_DEBRIS) = 0x1A;
    E_ID(ID_1B) = 0x1B;
    E_ID(ID_1C) = 0x1C;
    E_ID(ID_1D) = 0x1D;
    E_ID(ID_1E) = 0x1E;
    E_ID(ID_1F) = 0x1F;
    E_ID(ID_20) = 0x20;
    E_ID(ID_21) = 0x21;
    E_ID(ID_22) = 0x22;
    E_ID(ID_23) = 0x23;
    E_ID(ID_24) = 0x24;
    E_ID(ID_25) = 0x25;
    E_ID(ID_26) = 0x26;
    E_ID(ID_27) = 0x27;
    E_ID(ID_28) = 0x28;
    E_ID(ID_29) = 0x29;
    E_ID(ID_2A) = 0x2A;
    E_ID(ID_2B) = 0x2B;
    E_ID(ID_2C) = 0x2C;
    E_ID(ID_2D) = 0x2D;
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DFF4;
    g_pStObjLayoutVertical = &D_8D2E0C8;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
