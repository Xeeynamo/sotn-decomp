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

extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(ID_13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(ID_16);
extern s32 E_ID(BG_LIGHTNING);
extern s32 E_ID(TRANSP_WATER);
extern s32 E_ID(SHUTTING_WINDOW);
extern s32 E_ID(CASTLE_DOOR);
extern s32 E_ID(BACKGROUND_BUSHES);
extern s32 E_ID(BACKGROUND_TREES);
extern s32 E_ID(CAVERN_DOOR_LEVER);
extern s32 E_ID(CAVERN_DOOR_PLATFORM);
extern s32 E_ID(CAVERN_DOOR);
extern s32 E_ID(WEIGHTS_SWITCH);
extern s32 E_ID(WEIGHT_SMALL);
extern s32 E_ID(WEIGHT_TALL);
extern s32 E_ID(TRAPDOOR);
extern s32 E_ID(MERMAN_ROCK_L);
extern s32 E_ID(MERMAN_ROCK_R);
extern s32 E_ID(JEWEL_SWORD_DOOR);
extern s32 E_ID(FALLING_ROCK_2);
extern s32 E_ID(DEATH_SKY_SWIRL);
extern s32 E_ID(LIGHTNING_THUNDER);
extern s32 E_ID(LIGHTNING_CLOUD);
extern s32 E_ID(HEART_ROOM_SWITCH);
extern s32 E_ID(HEART_ROOM_DOOR);
extern s32 E_ID(FIRE_WARG);
extern s32 E_ID(FIRE_WARG_ATTACK);
extern s32 E_ID(ID_2F);
extern s32 E_ID(ID_30);
extern s32 E_ID(ID_31);
extern s32 E_ID(EXPLOSION_3);
extern s32 E_ID(FIRE_WARG_DEATH);
extern s32 E_ID(ALU_WATER_EFFECT);
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(SURFACING_WATER);
extern s32 E_ID(SIDE_WATER_SPLASH);
extern s32 E_ID(SMALL_WATER_DROP);
extern s32 E_ID(WATER_DROP);
extern s32 E_ID(MERMAN2);
extern s32 E_ID(MERMAN_WATER_SPLASH);
extern s32 E_ID(MEDIUM_WATER_SPLASH);
extern s32 E_ID(HIGH_WATER_SPLASH);
extern s32 E_ID(MERMAN2_SPIT_FIRE);
extern s32 E_ID(MERMAN2_DYING);
extern s32 E_ID(MERMAN2_JUMP_AIR);
extern s32 E_ID(MERMAN);
extern s32 E_ID(MERMAN_SPIT_FIRE);
extern s32 E_ID(MERMAN_JUMP_AIR);
extern s32 E_ID(MERMAN_DYING);
extern s32 E_ID(MERMAN_SPAWNER);
extern s32 E_ID(BONE_SCIMITAR);
extern s32 E_ID(BONE_SCIMITAR_PARTS);
extern s32 E_ID(BAT);
extern s32 E_ID(TMAP_SHUFF_UNUSED);
extern s32 E_ID(WARG);
extern s32 E_ID(ID_4B);
extern s32 E_ID(ZOMBIE);
extern s32 E_ID(ZOMBIE_SPAWNER);
extern s32 E_ID(PUSH_ALUCARD);
extern s32 E_ID(FOREGROUND_TREE);
extern s32 E_ID(FOLIAGE_MAKER);
extern s32 E_ID(BACKGROUND_PINE_TREES);
extern s32 E_ID(BACKGROUND_PINE_MAKER);
extern s32 E_ID(CASTLE_DOOR_TRANSITION);
extern s32 E_ID(CASTLE_BRIDGE);
extern s32 E_ID(DIST_BG_TREES);
extern s32 E_ID(BACKGROUND_WALL);
extern s32 E_ID(CUTSCENE);
extern s32 E_ID(DEATH_SCENE_MGR);
extern s32 E_ID(DEATH_STOLEN_ITEM);
extern s32 E_ID(DEATH);
extern s32 E_ID(DEATH_SCYTHE);
extern s32 E_ID(STAIRWAY_PIECE);
extern s32 E_ID(FALLING_ROCK);
extern s32 E_ID(DEATH_SCYTHE_SHADOW);
extern s32 E_ID(FLYING_OWL_LEAVES);
extern s32 E_ID(FALLING_LEAF);
extern s32 E_ID(EXPLODE_PUFF_TRANS);
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);

// Weird for this entity to be here. But the static GetLangAt
// above this, and the func_pspeu_09238360 below, must be
// in the same file, so this, sandwiched, must also be.
#include "../e_background_lightning.h"

void InitEntityIds(void) {
    E_ID(BACKGROUND_BLOCK) = 0x11;
    E_ID(LOCK_CAMERA) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(EXPLOSION_VARIANTS) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(BG_LIGHTNING) = 0x17;
    E_ID(TRANSP_WATER) = 0x18;
    E_ID(SHUTTING_WINDOW) = 0x19;
    E_ID(CASTLE_DOOR) = 0x1A;
    E_ID(BACKGROUND_BUSHES) = 0x1B;
    E_ID(BACKGROUND_TREES) = 0x1C;
    E_ID(CAVERN_DOOR_LEVER) = 0x1D;
    E_ID(CAVERN_DOOR_PLATFORM) = 0x1E;
    E_ID(CAVERN_DOOR) = 0x1F;
    E_ID(WEIGHTS_SWITCH) = 0x20;
    E_ID(WEIGHT_SMALL) = 0x21;
    E_ID(WEIGHT_TALL) = 0x22;
    E_ID(TRAPDOOR) = 0x23;
    E_ID(MERMAN_ROCK_L) = 0x24;
    E_ID(MERMAN_ROCK_R) = 0x25;
    E_ID(JEWEL_SWORD_DOOR) = 0x26;
    E_ID(FALLING_ROCK_2) = 0x27;
    E_ID(DEATH_SKY_SWIRL) = 0x28;
    E_ID(LIGHTNING_THUNDER) = 0x29;
    E_ID(LIGHTNING_CLOUD) = 0x2A;
    E_ID(HEART_ROOM_SWITCH) = 0x2B;
    E_ID(HEART_ROOM_DOOR) = 0x2C;
    E_ID(FIRE_WARG) = 0x2D;
    E_ID(FIRE_WARG_ATTACK) = 0x2E;
    E_ID(ID_2F) = 0x2F;
    E_ID(ID_30) = 0x30;
    E_ID(ID_31) = 0x31;
    E_ID(EXPLOSION_3) = 0x32;
    E_ID(FIRE_WARG_DEATH) = 0x33;
    E_ID(ALU_WATER_EFFECT) = 0x34;
    E_ID(SPLASH_WATER) = 0x35;
    E_ID(SURFACING_WATER) = 0x36;
    E_ID(SIDE_WATER_SPLASH) = 0x37;
    E_ID(SMALL_WATER_DROP) = 0x38;
    E_ID(WATER_DROP) = 0x39;
    E_ID(MERMAN2) = 0x3A;
    E_ID(MERMAN_WATER_SPLASH) = 0x3B;
    E_ID(MEDIUM_WATER_SPLASH) = 0x3C;
    E_ID(HIGH_WATER_SPLASH) = 0x3D;
    E_ID(MERMAN2_SPIT_FIRE) = 0x3E;
    E_ID(MERMAN2_DYING) = 0x3F;
    E_ID(MERMAN2_JUMP_AIR) = 0x40;
    E_ID(MERMAN) = 0x41;
    E_ID(MERMAN_SPIT_FIRE) = 0x42;
    E_ID(MERMAN_JUMP_AIR) = 0x43;
    E_ID(MERMAN_DYING) = 0x44;
    E_ID(MERMAN_SPAWNER) = 0x45;
    E_ID(BONE_SCIMITAR) = 0x46;
    E_ID(BONE_SCIMITAR_PARTS) = 0x47;
    E_ID(BAT) = 0x48;
    E_ID(TMAP_SHUFF_UNUSED) = 0x49;
    E_ID(WARG) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ZOMBIE) = 0x4C;
    E_ID(ZOMBIE_SPAWNER) = 0x4D;
    E_ID(PUSH_ALUCARD) = 0x4E;
    E_ID(FOREGROUND_TREE) = 0x4F;
    E_ID(FOLIAGE_MAKER) = 0x50;
    E_ID(BACKGROUND_PINE_TREES) = 0x51;
    E_ID(BACKGROUND_PINE_MAKER) = 0x52;
    E_ID(CASTLE_DOOR_TRANSITION) = 0x53;
    E_ID(CASTLE_BRIDGE) = 0x54;
    E_ID(DIST_BG_TREES) = 0x55;
    E_ID(BACKGROUND_WALL) = 0x56;
    E_ID(CUTSCENE) = 0x57;
    E_ID(DEATH_SCENE_MGR) = 0x58;
    E_ID(DEATH_STOLEN_ITEM) = 0x59;
    E_ID(DEATH) = 0x5A;
    E_ID(DEATH_SCYTHE) = 0x5B;
    E_ID(STAIRWAY_PIECE) = 0x5C;
    E_ID(FALLING_ROCK) = 0x5D;
    E_ID(DEATH_SCYTHE_SHADOW) = 0x5E;
    E_ID(FLYING_OWL_LEAVES) = 0x5F;
    E_ID(FALLING_LEAF) = 0x60;
    E_ID(EXPLODE_PUFF_TRANS) = 0x61;
    E_ID(EXPLODE_PUFF_OPAQUE) = 0x62;
}

void OVL_EXPORT(Load)(void) {
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
