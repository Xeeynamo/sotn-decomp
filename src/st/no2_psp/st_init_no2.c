// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no2/no2.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E1B4;
extern LayoutEntity* D_8D2E288;

extern Overlay OVL_EXPORT(Overlay);

s32 E_ID(ID_11);
s32 E_ID(ID_12);
s32 E_ID(ID_13);
s32 E_ID(ID_14);
s32 E_ID(ID_15);
s32 E_ID(ID_16);
s32 E_ID(ID_17);
s32 E_ID(ID_18);
s32 E_ID(ID_19);
s32 E_ID(ID_1A);
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
s32 E_ID(ID_2E);
s32 E_ID(ID_2F);
s32 E_ID(ID_30);
s32 E_ID(ID_31);
s32 E_ID(ID_32);
s32 E_ID(ID_33);
s32 E_ID(ID_34);
s32 E_ID(ID_35);
s32 E_ID(ID_36);
s32 E_ID(ID_37);
s32 E_ID(ID_38);
s32 E_ID(ID_39);
s32 E_ID(ID_3A);
s32 E_ID(ID_3B);
s32 E_ID(ID_3C);
s32 E_ID(ID_3D);
s32 E_ID(ID_3E);
s32 E_ID(ID_3F);
s32 E_ID(ID_40);
s32 E_ID(BREAKABLE_DEBRIS);

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(ID_15) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(ID_17) = 0x17;
    E_ID(ID_18) = 0x18;
    E_ID(ID_19) = 0x19;
    E_ID(ID_1A) = 0x1A;
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
    E_ID(ID_2E) = 0x2E;
    E_ID(ID_2F) = 0x2F;
    E_ID(ID_30) = 0x30;
    E_ID(ID_31) = 0x31;
    E_ID(ID_32) = 0x32;
    E_ID(ID_33) = 0x33;
    E_ID(ID_34) = 0x34;
    E_ID(ID_35) = 0x35;
    E_ID(ID_36) = 0x36;
    E_ID(ID_37) = 0x37;
    E_ID(ID_38) = 0x38;
    E_ID(ID_39) = 0x39;
    E_ID(ID_3A) = 0x3A;
    E_ID(ID_3B) = 0x3B;
    E_ID(ID_3C) = 0x3C;
    E_ID(ID_3D) = 0x3D;
    E_ID(ID_3E) = 0x3E;
    E_ID(ID_3F) = 0x3F;
    E_ID(ID_40) = 0x40;
    E_ID(BREAKABLE_DEBRIS) = 0x41;
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E1B4;
    g_pStObjLayoutVertical = &D_8D2E288;
    func_892A018();
    memcpy((u8*)&g_api, (u8*)&OVL_EXPORT(Overlay), sizeof(Overlay));
}
