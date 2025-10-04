// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no4/no4.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E4B0;
extern LayoutEntity* D_8D2E584;

extern Overlay OVL_EXPORT(Overlay);

// Imported in cutscene_data.c
extern char cutscene_data_ferryman_right_it[];
extern char cutscene_data_ferryman_right_sp[];
extern char cutscene_data_ferryman_right_fr[];
extern char cutscene_data_ferryman_right_ge[];
extern char cutscene_data_ferryman_right_en[];
extern char cutscene_data_ferryman_left_it[];
extern char cutscene_data_ferryman_left_sp[];
extern char cutscene_data_ferryman_left_fr[];
extern char cutscene_data_ferryman_left_ge[];
extern char cutscene_data_ferryman_left_en[];

// bss
static s32 E_ID(ID_11);
static s32 E_ID(ID_12);
static s32 E_ID(ID_13);
static s32 E_ID(ID_14);
static s32 E_ID(ID_15);
static s32 E_ID(ID_16);
s32 E_ID(SPLASH_WATER);
s32 E_ID(SURFACING_WATER);
static s32 E_ID(ID_19);
static s32 E_ID(ID_1A);
static s32 E_ID(ID_1B);
static s32 E_ID(ID_1C);
static s32 E_ID(ID_1D);
static s32 E_ID(ID_1E);
static s32 E_ID(ID_1F);
static s32 E_ID(ID_20);
static s32 E_ID(ID_21);
static s32 E_ID(ID_22);
static s32 E_ID(ID_23);
static s32 E_ID(ID_24);
static s32 E_ID(ID_25);
s32 E_ID(ID_26);
s32 E_ID(ID_27);
static s32 E_ID(ID_28);
static s32 E_ID(ID_29);
static s32 E_ID(ID_2A);
static s32 E_ID(ID_2B);
static s32 E_ID(ID_2C);
static s32 E_ID(ID_2D);
s32 E_ID(FERRYMAN);
static s32 E_ID(ID_2F);
static s32 E_ID(ID_30);
static s32 E_ID(ID_31);
static s32 E_ID(ID_32);
static s32 E_ID(ID_33);
static s32 E_ID(ID_34);
s32 E_ID(ID_35);
static s32 E_ID(ID_36);
static s32 E_ID(ID_37);
static s32 E_ID(ID_38);
static s32 E_ID(ID_39);
static s32 E_ID(ID_3A);
s32 E_ID(ID_3B);
static s32 E_ID(ID_3C);
static s32 E_ID(ID_3D);
static s32 E_ID(ID_3E);
static s32 E_ID(ID_3F);
static s32 E_ID(ID_40);
static s32 E_ID(ID_41);
static s32 E_ID(ID_42);
static s32 E_ID(ID_43);
static s32 E_ID(ID_44);
static s32 E_ID(ID_45);
static s32 E_ID(ID_46);
static s32 E_ID(ID_47);
static s32 E_ID(ID_48);
static s32 E_ID(ID_49);
static s32 E_ID(ID_4A);
static s32 E_ID(ID_4B);
static s32 E_ID(ID_4C);
static s32 E_ID(ID_4D);
static s32 E_ID(ID_4E);
s32 E_ID(ID_4F);
static s32 E_ID(ID_50);
static s32 E_ID(ID_51);
s32 E_ID(BREAKABLE_WALL_DEBRIS);
static s32 E_ID(ID_53);
s32 E_ID(ID_54);
static s32 E_ID(ID_55);
s32 E_ID(ID_56);
static s32 E_ID(ID_57);
s32 E_ID(ID_58);
static s32 E_ID(ID_59);
s32 E_ID(KILLER_FISH_DEATH_PUFF);
static s32 E_ID(ID_5B);
s32 E_ID(ID_5C);
static s32 E_ID(ID_5D);
static s32 E_ID(ID_5E);
static s32 E_ID(ID_5F);
static s32 E_ID(ID_60);

u8* cutscene_data_ferryman_right;
static u8* cutscene_data_ferryman_right_unused;
u8* cutscene_data_ferryman_left;
static u8* cutscene_data_ferryman_left_unused;

#include "../get_lang_at.h"

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(ID_15) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(SPLASH_WATER) = 0x17;
    E_ID(SURFACING_WATER) = 0x18;
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
    E_ID(FERRYMAN) = 0x2E;
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
    E_ID(ID_41) = 0x41;
    E_ID(ID_42) = 0x42;
    E_ID(ID_43) = 0x43;
    E_ID(ID_44) = 0x44;
    E_ID(ID_45) = 0x45;
    E_ID(ID_46) = 0x46;
    E_ID(ID_47) = 0x47;
    E_ID(ID_48) = 0x48;
    E_ID(ID_49) = 0x49;
    E_ID(ID_4A) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ID_4C) = 0x4C;
    E_ID(ID_4D) = 0x4D;
    E_ID(ID_4E) = 0x4E;
    E_ID(ID_4F) = 0x4F;
    E_ID(ID_50) = 0x50;
    E_ID(ID_51) = 0x51;
    E_ID(BREAKABLE_WALL_DEBRIS) = 0x52;
    E_ID(ID_53) = 0x53;
    E_ID(ID_54) = 0x54;
    E_ID(ID_55) = 0x55;
    E_ID(ID_56) = 0x56;
    E_ID(ID_57) = 0x57;
    E_ID(ID_58) = 0x58;
    E_ID(ID_59) = 0x59;
    E_ID(KILLER_FISH_DEATH_PUFF) = 0x5A;
    E_ID(ID_5B) = 0x5B;
    E_ID(ID_5C) = 0x5C;
    E_ID(ID_5D) = 0x5D;
    E_ID(ID_5E) = 0x5E;
    E_ID(ID_5F) = 0x5F;
    E_ID(ID_60) = 0x60;
}

void OVL_EXPORT(Load)(void) {
    cutscene_data_ferryman_right = GetLangAt(
        NULL, (u8*)cutscene_data_ferryman_right_en,
        (u8*)cutscene_data_ferryman_right_fr,
        (u8*)cutscene_data_ferryman_right_sp,
        (u8*)cutscene_data_ferryman_right_ge,
        (u8*)cutscene_data_ferryman_right_it);

    cutscene_data_ferryman_right_unused = GetLangAt(
        NULL, (u8*)cutscene_data_ferryman_right_en,
        (u8*)cutscene_data_ferryman_right_fr,
        (u8*)cutscene_data_ferryman_right_sp,
        (u8*)cutscene_data_ferryman_right_ge,
        (u8*)cutscene_data_ferryman_right_it);

    cutscene_data_ferryman_left = GetLangAt(
        NULL, (u8*)cutscene_data_ferryman_left_en,
        (u8*)cutscene_data_ferryman_left_fr,
        (u8*)cutscene_data_ferryman_left_sp,
        (u8*)cutscene_data_ferryman_left_ge,
        (u8*)cutscene_data_ferryman_left_it);

    cutscene_data_ferryman_left_unused = GetLangAt(
        NULL, (u8*)cutscene_data_ferryman_left_en,
        (u8*)cutscene_data_ferryman_left_fr,
        (u8*)cutscene_data_ferryman_left_sp,
        (u8*)cutscene_data_ferryman_left_ge,
        (u8*)cutscene_data_ferryman_left_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E4B0;
    g_pStObjLayoutVertical = &D_8D2E584;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
