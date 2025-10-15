// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

extern LayoutEntity* D_8D2E2B0;
extern LayoutEntity* D_8D2E384;

extern Overlay OVL_EXPORT(Overlay);

extern char OVL_EXPORT(cutscene_script_en)[];
extern char OVL_EXPORT(cutscene_script_fr)[];
extern char OVL_EXPORT(cutscene_script_sp)[];
extern char OVL_EXPORT(cutscene_script_ge)[];
extern char OVL_EXPORT(cutscene_script_it)[];

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_16);
s32 E_ID(STAINED_GLASS);
s32 E_ID(STAINED_GLASS_BACKGROUND);
s32 E_ID(BLOCK);
s32 E_ID(STATUE);
s32 E_ID(BELL);
s32 E_ID(CASTLE_WALL_1);
s32 E_ID(CASTLE_WALL_2);
s32 E_ID(STAIRCASE);
s32 E_ID(CLOUDS);
s32 E_ID(BACKGROUND_SKY_LAND);
s32 E_ID(GARGOYLE_TONGUE);
s32 E_ID(CHAIR);
s32 E_ID(CONFESSIONAL_GHOST);
s32 E_ID(CONFESSIONAL_BLADES);
s32 E_ID(CONFESSIONAL_BLADE_DEBRIS);
s32 E_ID(BELL_HELPER);
s32 E_ID(CORNER_GUARD);
s32 E_ID(CORNER_GUARD_ATTACK);
s32 E_ID(BONE_PILLAR_HEAD);
s32 E_ID(BONE_PILLAR_FIRE);
s32 E_ID(BONE_PILLAR_PIECES);
s32 E_ID(BONE_PILLAR_SPIKE_BALL);
s32 E_ID(UNK_2D);
s32 E_ID(SPIKES);
s32 E_ID(SPIKES_PARTS);
s32 E_ID(SPIKES_DUST);
s32 E_ID(SPIKES_DAMAGE);
s32 E_ID(BONE_HALBERD);
s32 E_ID(BONE_HALBERD_NAGINATA);
s32 E_ID(BONE_HALBERD_PARTS);
s32 E_ID(UNK_35);
s32 E_ID(UNK_36);
s32 E_ID(BAT);
s32 E_ID(BLACK_CROW);
s32 E_ID(BLUE_CROW);
s32 E_ID(SKELERANG);
s32 E_ID(SKELERANG_BOOMERANG);
s32 E_ID(SKELERANG_UNKNOWN);
s32 E_ID(HUNTING_GIRL);
s32 E_ID(HUNTING_GIRL_ATTACK);
s32 E_ID(UNK_3F);
s32 E_ID(UNK_40);
s32 E_ID(UNK_41);
s32 E_ID(UNK_42);
s32 E_ID(SEALED_DOOR);
s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(CUTSCENE_DIALOGUE);
s32 E_ID(CUTSCENE_STAGE);
s32 E_ID(CUTSCENE_MARIA);
s32 E_ID(MIST_DOOR);

// Used by dai/e_cutscene_dialogue/DAI_EntityCutsceneDialogue
u8* OVL_EXPORT(cutscene_script);         // bss
u8* OVL_EXPORT(cutscene_script_address); // bss

#include "../get_lang_at.h"

static void InitEntityIds(void) {
    E_ID(BACKGROUND_BLOCK) = 0x11;
    E_ID(LOCK_CAMERA) = 0x12;
    E_ID(UNK_13) = 0x13;
    E_ID(EXPLOSION_VARIANTS) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(UNK_16) = 0x16;
    E_ID(STAINED_GLASS) = 0x17;
    E_ID(STAINED_GLASS_BACKGROUND) = 0x18;
    E_ID(BLOCK) = 0x19;
    E_ID(STATUE) = 0x1A;
    E_ID(BELL) = 0x1B;
    E_ID(CASTLE_WALL_1) = 0x1C;
    E_ID(CASTLE_WALL_2) = 0x1D;
    E_ID(STAIRCASE) = 0x1E;
    E_ID(CLOUDS) = 0x1F;
    E_ID(BACKGROUND_SKY_LAND) = 0x20;
    E_ID(GARGOYLE_TONGUE) = 0x21;
    E_ID(CHAIR) = 0x22;
    E_ID(CONFESSIONAL_GHOST) = 0x23;
    E_ID(CONFESSIONAL_BLADES) = 0x24;
    E_ID(CONFESSIONAL_BLADE_DEBRIS) = 0x25;
    E_ID(BELL_HELPER) = 0x26;
    E_ID(CORNER_GUARD) = 0x27;
    E_ID(CORNER_GUARD_ATTACK) = 0x28;
    E_ID(BONE_PILLAR_HEAD) = 0x29;
    E_ID(BONE_PILLAR_FIRE) = 0x2A;
    E_ID(BONE_PILLAR_PIECES) = 0x2B;
    E_ID(BONE_PILLAR_SPIKE_BALL) = 0x2C;
    E_ID(UNK_2D) = 0x2D;
    E_ID(SPIKES) = 0x2E;
    E_ID(SPIKES_PARTS) = 0x2F;
    E_ID(SPIKES_DUST) = 0x30;
    E_ID(SPIKES_DAMAGE) = 0x31;
    E_ID(BONE_HALBERD) = 0x32;
    E_ID(BONE_HALBERD_NAGINATA) = 0x33;
    E_ID(BONE_HALBERD_PARTS) = 0x34;
    E_ID(UNK_35) = 0x35;
    E_ID(UNK_36) = 0x36;
    E_ID(BAT) = 0x37;
    E_ID(BLACK_CROW) = 0x38;
    E_ID(BLUE_CROW) = 0x39;
    E_ID(SKELERANG) = 0x3A;
    E_ID(SKELERANG_BOOMERANG) = 0x3B;
    E_ID(SKELERANG_UNKNOWN) = 0x3C;
    E_ID(HUNTING_GIRL) = 0x3D;
    E_ID(HUNTING_GIRL_ATTACK) = 0x3E;
    E_ID(UNK_3F) = 0x3F;
    E_ID(UNK_40) = 0x40;
    E_ID(UNK_41) = 0x41;
    E_ID(UNK_42) = 0x42;
    E_ID(SEALED_DOOR) = 0x43;
    E_ID(BREAKABLE_DEBRIS) = 0x44;
    E_ID(CUTSCENE_DIALOGUE) = 0x45;
    E_ID(CUTSCENE_STAGE) = 0x46;
    E_ID(CUTSCENE_MARIA) = 0x47;
    E_ID(MIST_DOOR) = 0x48;
}

void OVL_EXPORT(Load)(void) {
    OVL_EXPORT(cutscene_script) = GetLangAt(
        0, (u8*)OVL_EXPORT(cutscene_script_en),
        (u8*)OVL_EXPORT(cutscene_script_fr),
        (u8*)OVL_EXPORT(cutscene_script_sp),
        (u8*)OVL_EXPORT(cutscene_script_ge),
        (u8*)OVL_EXPORT(cutscene_script_it));
    OVL_EXPORT(cutscene_script_address) = GetLangAt(
        0, (u8*)OVL_EXPORT(cutscene_script_en),
        (u8*)OVL_EXPORT(cutscene_script_fr),
        (u8*)OVL_EXPORT(cutscene_script_sp),
        (u8*)OVL_EXPORT(cutscene_script_ge),
        (u8*)OVL_EXPORT(cutscene_script_it));
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E2B0;
    g_pStObjLayoutVertical = &D_8D2E384;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
