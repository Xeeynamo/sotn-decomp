// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E3BC;
extern LayoutEntity* D_8D2E490;

extern Overlay OVL_EXPORT(Overlay);

extern char cutscene_data_it[];
extern char cutscene_data_sp[];
extern char cutscene_data_fr[];
extern char cutscene_data_ge[];
extern char cutscene_data_en[];

extern u8* OVL_EXPORT(cutscene_data); // bss

#include "../get_lang_at.h"

extern s32 E_ID(ID_11);
extern s32 E_ID(ID_12);
extern s32 E_ID(ID_13);
extern s32 E_ID(ID_14);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(ID_16);
extern s32 E_ID(BG_LIGHTNING);
extern s32 E_ID(ID_18);
extern s32 E_ID(ID_19);
extern s32 E_ID(ID_1A);
extern s32 E_ID(ID_1B);
extern s32 E_ID(ID_1C);
extern s32 E_ID(ID_1D);
extern s32 E_ID(CAVERN_DOOR_PLATFORM);
extern s32 E_ID(ID_1F);
extern s32 E_ID(ID_20);
extern s32 E_ID(ID_21);
extern s32 E_ID(ID_22);
extern s32 E_ID(ID_23);
extern s32 E_ID(ID_24);
extern s32 E_ID(ID_25);
extern s32 E_ID(ID_26);
extern s32 E_ID(FALLING_ROCK_2);
extern s32 E_ID(ID_28);
extern s32 E_ID(LIGHTNING_THUNDER);
extern s32 E_ID(LIGHTNING_CLOUD);
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
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(SURFACING_WATER);
extern s32 E_ID(SIDE_WATER_SPLASH);
extern s32 E_ID(SMALL_WATER_DROP);
extern s32 E_ID(WATER_DROP);
extern s32 E_ID(MERMAN2);
extern s32 E_ID(MERMAN_JUMP_WATER);
extern s32 E_ID(MERMAN2_UNK1);
extern s32 E_ID(HIGH_WATER_SPLASH);
extern s32 E_ID(MERMAN2_SPIT_FIRE);
extern s32 E_ID(MERMAN2_DYING);
extern s32 E_ID(MERMAN2_JUMP_AIR);
extern s32 E_ID(MERMAN);
extern s32 E_ID(MERMAN_SPIT_FIRE);
extern s32 E_ID(MERMAN_JUMP_AIR);
extern s32 E_ID(MERMAN_DYING);
extern s32 E_ID(ID_45);
extern s32 E_ID(ID_46);
extern s32 E_ID(BONE_SCIMITAR_HEAD);
extern s32 E_ID(ID_48);
extern s32 E_ID(ID_49);
extern s32 E_ID(ID_4A);
extern s32 E_ID(ID_4B);
extern s32 E_ID(ZOMBIE);
extern s32 E_ID(ID_4D);
extern s32 E_ID(ID_4E);
extern s32 E_ID(ID_4F);
extern s32 E_ID(ID_50);
extern s32 E_ID(ID_51);
extern s32 E_ID(ID_52);
extern s32 E_ID(ID_53);
extern s32 E_ID(ID_54);
extern s32 E_ID(ID_55);
extern s32 E_ID(ID_56);
extern s32 E_ID(ID_57);
extern s32 E_ID(ID_58);
extern s32 E_ID(ID_59);
extern s32 E_ID(ID_5A);
extern s32 E_ID(DEATH_SCYTHE);
extern s32 E_ID(ID_5C);
extern s32 E_ID(FALLING_ROCK);
extern s32 E_ID(DEATH_SCYTHE_SHADOW);
extern s32 E_ID(ID_5F);
extern s32 E_ID(FLYING_OWL_UNK60);
extern s32 E_ID(WARG_EXP_TRANSP);
extern s32 E_ID(WARG_EXP_OPAQUE);

// Weird for this entity to be here. But the static GetLangAt
// above this, and the func_pspeu_09238360 below, must be
// in the same file, so this, sandwiched, must also be.
#include "../e_background_lightning.h"

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(BG_LIGHTNING) = 0x17;
    E_ID(ID_18) = 0x18;
    E_ID(ID_19) = 0x19;
    E_ID(ID_1A) = 0x1A;
    E_ID(ID_1B) = 0x1B;
    E_ID(ID_1C) = 0x1C;
    E_ID(ID_1D) = 0x1D;
    E_ID(CAVERN_DOOR_PLATFORM) = 0x1E;
    E_ID(ID_1F) = 0x1F;
    E_ID(ID_20) = 0x20;
    E_ID(ID_21) = 0x21;
    E_ID(ID_22) = 0x22;
    E_ID(ID_23) = 0x23;
    E_ID(ID_24) = 0x24;
    E_ID(ID_25) = 0x25;
    E_ID(ID_26) = 0x26;
    E_ID(FALLING_ROCK_2) = 0x27;
    E_ID(ID_28) = 0x28;
    E_ID(LIGHTNING_THUNDER) = 0x29;
    E_ID(LIGHTNING_CLOUD) = 0x2A;
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
    E_ID(SPLASH_WATER) = 0x35;
    E_ID(SURFACING_WATER) = 0x36;
    E_ID(SIDE_WATER_SPLASH) = 0x37;
    E_ID(SMALL_WATER_DROP) = 0x38;
    E_ID(WATER_DROP) = 0x39;
    E_ID(MERMAN2) = 0x3A;
    E_ID(MERMAN_JUMP_WATER) = 0x3B;
    E_ID(MERMAN2_UNK1) = 0x3C;
    E_ID(HIGH_WATER_SPLASH) = 0x3D;
    E_ID(MERMAN2_SPIT_FIRE) = 0x3E;
    E_ID(MERMAN2_DYING) = 0x3F;
    E_ID(MERMAN2_JUMP_AIR) = 0x40;
    E_ID(MERMAN) = 0x41;
    E_ID(MERMAN_SPIT_FIRE) = 0x42;
    E_ID(MERMAN_JUMP_AIR) = 0x43;
    E_ID(MERMAN_DYING) = 0x44;
    E_ID(ID_45) = 0x45;
    E_ID(ID_46) = 0x46;
    E_ID(BONE_SCIMITAR_HEAD) = 0x47;
    E_ID(ID_48) = 0x48;
    E_ID(ID_49) = 0x49;
    E_ID(ID_4A) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ZOMBIE) = 0x4C;
    E_ID(ID_4D) = 0x4D;
    E_ID(ID_4E) = 0x4E;
    E_ID(ID_4F) = 0x4F;
    E_ID(ID_50) = 0x50;
    E_ID(ID_51) = 0x51;
    E_ID(ID_52) = 0x52;
    E_ID(ID_53) = 0x53;
    E_ID(ID_54) = 0x54;
    E_ID(ID_55) = 0x55;
    E_ID(ID_56) = 0x56;
    E_ID(ID_57) = 0x57;
    E_ID(ID_58) = 0x58;
    E_ID(ID_59) = 0x59;
    E_ID(ID_5A) = 0x5A;
    E_ID(DEATH_SCYTHE) = 0x5B;
    E_ID(ID_5C) = 0x5C;
    E_ID(FALLING_ROCK) = 0x5D;
    E_ID(DEATH_SCYTHE_SHADOW) = 0x5E;
    E_ID(ID_5F) = 0x5F;
    E_ID(FLYING_OWL_UNK60) = 0x60;
    E_ID(WARG_EXP_TRANSP) = 0x61;
    E_ID(WARG_EXP_OPAQUE) = 0x62;
}

void func_pspeu_09238360(void) {
    OVL_EXPORT(cutscene_data) = GetLangAt(
        0, (u8*)cutscene_data_en, (u8*)cutscene_data_fr, (u8*)cutscene_data_sp,
        (u8*)cutscene_data_ge, (u8*)cutscene_data_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E3BC;
    g_pStObjLayoutVertical = &D_8D2E490;
    func_892A018();
    memcpy((u8*)&g_api, (u8*)&OVL_EXPORT(Overlay), sizeof(Overlay));
}
