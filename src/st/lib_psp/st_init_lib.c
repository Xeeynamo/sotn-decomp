// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E160;
extern LayoutEntity* D_8D2E234;

extern Overlay OVL_EXPORT(Overlay);

extern char D_psp_09276330[];
extern char D_psp_09276520[];
extern char D_psp_092766E8[];
extern char D_psp_092768E0[];
extern char D_psp_09276AC8[];

extern u8* D_psp_092A54E0;            // bss
extern u8* D_psp_092A54E8;            // bss
extern u8* D_psp_092A54F0;            // bss
extern u8* OVL_EXPORT(cutscene_data); // bss

#include "../get_lang_at.h"

extern s32 E_ID(ID_11);
extern s32 E_ID(ID_12);
extern s32 E_ID(ID_13);
extern s32 E_ID(ID_14);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(ID_16);
extern s32 E_ID(ID_17);
extern s32 E_ID(ID_18);
extern s32 E_ID(ID_19);
extern s32 E_ID(ID_1A);
extern s32 E_ID(ID_1B);
extern s32 E_ID(ID_1C);
extern s32 E_ID(BLOOD_DRIPS);
extern s32 E_ID(BLOOD_SPLATTER);
extern s32 E_ID(ID_1F);
extern s32 E_ID(ID_20);
extern s32 E_ID(ID_21);
extern s32 E_ID(ID_22);
extern s32 E_ID(ID_23);
extern s32 E_ID(ID_24);
extern s32 E_ID(ID_25);
extern s32 E_ID(ID_26);
extern s32 E_ID(ID_27);
extern s32 E_ID(ID_28);
extern s32 E_ID(ID_29);
extern s32 E_ID(ID_2A);
extern s32 E_ID(ID_2B);
extern s32 E_ID(ID_2C);
extern s32 E_ID(ID_2D);
extern s32 E_ID(ID_2E);
extern s32 E_ID(ID_2F);
extern s32 E_ID(ID_30);
extern s32 E_ID(ID_31);
extern s32 E_ID(ID_32);
extern s32 E_ID(ID_33);
extern s32 E_ID(ID_34);
extern s32 E_ID(ID_35);
extern s32 E_ID(ID_36);
extern s32 E_ID(ID_37);
extern s32 E_ID(ID_38);
extern s32 E_ID(ID_39);
extern s32 E_ID(THORNWEED);
extern s32 E_ID(CORPSEWEED);
extern s32 E_ID(CORPSEWEED_PROJECTILE);
extern s32 E_ID(CANDLE_TABLE);
extern s32 E_ID(ID_3E);
extern s32 E_ID(ID_3F);
extern s32 E_ID(ID_40);
extern s32 E_ID(ID_41);
extern s32 E_ID(ID_42);
extern s32 E_ID(SKELETON);
extern s32 E_ID(SKELETON_THROWN_BONE);
extern s32 E_ID(SKELETON_PIECES);
extern s32 E_ID(ID_46);
extern s32 E_ID(ID_47);
extern s32 E_ID(ID_48);
extern s32 E_ID(ID_49);
extern s32 E_ID(ID_4A);
extern s32 E_ID(ID_4B);
extern s32 E_ID(ID_4C);
extern s32 E_ID(MUDMAN);
extern s32 E_ID(ID_4E);
extern s32 E_ID(ID_4F);

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(ID_17) = 0x17;
    E_ID(ID_18) = 0x18;
    E_ID(ID_19) = 0x19;
    E_ID(ID_1A) = 0x1A;
    E_ID(ID_1B) = 0x1B;
    E_ID(ID_1C) = 0x1C;
    E_ID(BLOOD_DRIPS) = 0x1D;
    E_ID(BLOOD_SPLATTER) = 0x1E;
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
    E_ID(THORNWEED) = 0x3A;
    E_ID(CORPSEWEED) = 0x3B;
    E_ID(CORPSEWEED_PROJECTILE) = 0x3C;
    E_ID(CANDLE_TABLE) = 0x3D;
    E_ID(ID_3E) = 0x3E;
    E_ID(ID_3F) = 0x3F;
    E_ID(ID_40) = 0x40;
    E_ID(ID_41) = 0x41;
    E_ID(ID_42) = 0x42;
    E_ID(SKELETON) = 0x43;
    E_ID(SKELETON_THROWN_BONE) = 0x44;
    E_ID(SKELETON_PIECES) = 0x45;
    E_ID(ID_46) = 0x46;
    E_ID(ID_47) = 0x47;
    E_ID(ID_48) = 0x48;
    E_ID(ID_49) = 0x49;
    E_ID(ID_4A) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ID_4C) = 0x4C;
    E_ID(MUDMAN) = 0x4D;
    E_ID(ID_4E) = 0x4E;
    E_ID(ID_4F) = 0x4F;
}

void func_psp_09254120(void) {
    OVL_EXPORT(cutscene_data) = GetLangAt(
        8, (u8*)D_psp_09276AC8, (u8*)D_psp_092766E8, (u8*)D_psp_09276520,
        (u8*)D_psp_092768E0, (u8*)D_psp_09276330);

    D_psp_092A54F0 = GetLangAt(
        0, (u8*)D_psp_09276AC8, (u8*)D_psp_092766E8, (u8*)D_psp_09276520,
        (u8*)D_psp_092768E0, (u8*)D_psp_09276330);

    D_psp_092A54E8 = GetLangAt(
        0, (u8*)D_psp_09276AC8, (u8*)D_psp_092766E8, (u8*)D_psp_09276520,
        (u8*)D_psp_092768E0, (u8*)D_psp_09276330);

    D_psp_092A54E0 = GetLangAt(
        4, (u8*)D_psp_09276AC8, (u8*)D_psp_092766E8, (u8*)D_psp_09276520,
        (u8*)D_psp_092768E0, (u8*)D_psp_09276330);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E160;
    g_pStObjLayoutVertical = &D_8D2E234;
    func_892A018();
    memcpy((u8*)&g_api, (u8*)&OVL_EXPORT(Overlay), sizeof(Overlay));
}
