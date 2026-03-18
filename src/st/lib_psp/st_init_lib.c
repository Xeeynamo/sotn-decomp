// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E160;
extern LayoutEntity* D_8D2E234;

extern Overlay OVL_EXPORT(Overlay);

extern char cutscene_data_it[];
extern char cutscene_data_sp[];
extern char cutscene_data_fr[];
extern char cutscene_data_ge[];
extern char cutscene_data_en[];

#include "../get_lang_at.h"

static s32 E_ID(ID_11);
s32 E_ID(ID_12);
static s32 E_ID(ID_13);
static s32 E_ID(EXPLOSION_VARIANTS);
static s32 E_ID(GREY_PUFF);
static s32 E_ID(ID_16);
static s32 E_ID(ID_17);
static s32 E_ID(ID_18);
static s32 E_ID(ID_19);
static s32 E_ID(ID_1A);
static s32 E_ID(ID_1B);
static s32 E_ID(ID_1C);
static s32 E_ID(BLOOD_DRIPS);
static s32 E_ID(BLOOD_SPLATTER);
s32 E_ID(ID_1F);
s32 E_ID(ID_20);
s32 E_ID(ID_21);
s32 E_ID(ID_22);
static s32 E_ID(ID_23);
static s32 E_ID(ID_24);
s32 E_ID(ID_25);
static s32 E_ID(ID_26);
s32 E_ID(ID_27);
s32 E_ID(ID_28);
s32 E_ID(ID_29);
s32 E_ID(ID_2A);
static s32 E_ID(ID_2B);
static s32 E_ID(ID_2C);
s32 E_ID(ID_2D);
s32 E_ID(ID_2E);
s32 E_ID(ID_2F);
static s32 E_ID(ID_30);
static s32 E_ID(ID_31);
static s32 E_ID(ID_32);
static s32 E_ID(ID_33);
static s32 E_ID(ID_34);
static s32 E_ID(ID_35);
static s32 E_ID(ID_36);
s32 E_ID(ID_37);
static s32 E_ID(ID_38);
static s32 E_ID(ID_39);
static s32 E_ID(THORNWEED);
static s32 E_ID(CORPSEWEED);
static s32 E_ID(CORPSEWEED_PROJECTILE);
s32 E_ID(CANDLE_TABLE);
static s32 E_ID(ID_3E);
static s32 E_ID(ID_3F);
s32 E_ID(ID_40);
static s32 E_ID(ID_41);
s32 E_ID(ID_42);
s32 E_ID(SKELETON);
static s32 E_ID(SKELETON_THROWN_BONE);
static s32 E_ID(SKELETON_PIECES);
static s32 E_ID(ID_46);
static s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(ID_48);
static s32 E_ID(ID_49);
static s32 E_ID(ID_4A);
static s32 E_ID(ID_4B);
static s32 E_ID(ID_4C);
s32 E_ID(MUDMAN);
static s32 E_ID(ID_4E);
s32 E_ID(ID_4F);

u8* OVL_EXPORT(cutscene_data_offset_eight);
u8* OVL_EXPORT(cutscene_data);
u8* OVL_EXPORT(cutscene_data_offset_zero);
u8* OVL_EXPORT(cutscene_data_offset_four);

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(EXPLOSION_VARIANTS) = 0x14;
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
    E_ID(BREAKABLE_DEBRIS) = 0x47;
    E_ID(ID_48) = 0x48;
    E_ID(ID_49) = 0x49;
    E_ID(ID_4A) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ID_4C) = 0x4C;
    E_ID(MUDMAN) = 0x4D;
    E_ID(ID_4E) = 0x4E;
    E_ID(ID_4F) = 0x4F;
}

void OVL_EXPORT(Load)(void) {
    OVL_EXPORT(cutscene_data_offset_eight) = GetLangAt(
        8, (u8*)cutscene_data_en, (u8*)cutscene_data_fr, (u8*)cutscene_data_sp,
        (u8*)cutscene_data_ge, (u8*)cutscene_data_it);

    OVL_EXPORT(cutscene_data) = GetLangAt(
        0, (u8*)cutscene_data_en, (u8*)cutscene_data_fr, (u8*)cutscene_data_sp,
        (u8*)cutscene_data_ge, (u8*)cutscene_data_it);

    OVL_EXPORT(cutscene_data_offset_zero) = GetLangAt(
        0, (u8*)cutscene_data_en, (u8*)cutscene_data_fr, (u8*)cutscene_data_sp,
        (u8*)cutscene_data_ge, (u8*)cutscene_data_it);

    OVL_EXPORT(cutscene_data_offset_four) = GetLangAt(
        4, (u8*)cutscene_data_en, (u8*)cutscene_data_fr, (u8*)cutscene_data_sp,
        (u8*)cutscene_data_ge, (u8*)cutscene_data_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E160;
    g_pStObjLayoutVertical = &D_8D2E234;
    func_psp_0892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
