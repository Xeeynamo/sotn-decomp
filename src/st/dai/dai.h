// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DAI_H
#define DAI_H

#include "stage.h"

#define OVL_EXPORT(x) DAI_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG) // psx e_stage_name

#include "../pfn_entity_update.h"

#define SEALED_DOOR_PALETTE 0x245 // e_sealed_door

// e_collect
#define HEART_DROP_CASTLE_FLAG 0x98
// commented here because sotn_str doesn't do .h files
/*
#ifdef VERSION_PSP
#define GOLD_COLLECT_TEXT                                                      \
    _S("$1"), _S("$25"), _S("$50"), _S("$100"), _S("$250"), _S("$400"),        \
        _S("$700"), _S("$1000"), _S("$2000"), _S("$5000"),
#endif
*/

// e_cutscene/cutscene_script_box
#define CUTSCENE_UNK3_RECT_X 0
#define CUTSCENE_UNK4_TPAGE 16

// e_cutscene/cutscene_script_text
#ifdef VERSION_PSP
#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#else
#define CUTSCENE_UNK1_NEXT_X 2
#define CUTSCENE_UNK1_UNK17 8
#endif

// e_cutscene/set_cutscene_script
#ifdef VERSION_PC
#define NUM_CUTSCENE_PRIM 8
#else
#define NUM_CUTSCENE_PRIM 7
#endif

// Used for cluts, palettes, and in g_EInits
enum OVL_EXPORT(Palette) {
    PAL_NONE = 0,
    PAL_41EE4_74 = 0x74,
    PAL_BELL_1 = 0x75,
    PAL_BELL_2 = 0x76,
    PAL_CLOUDS = 0xC0,
    PAL_434FC = 0xC5,
    PAL_41EE4_C8 = 0xC8,
    PAL_UNK_C9 = 0xC9,
    PAL_UNK_CA = 0xCA,
    PAL_UNK_CC = 0xCC,
    PAL_UNK_CE = 0xCE,
    PAL_STAGE_NAME_15F = 0x15F,
    PAL_SPECTRAL_SWORD_WEAPON_3 = 0x16B,
    PAL_STAGE_NAME_19D = 0x19D,
    PAL_STAGE_NAME_19E = 0x19E,
    PAL_STAGE_NAME_19F = 0x19F,
    PAL_SKELERANG = 0x200,
    PAL_CORNER_GUARD = 0x215,
    PAL_BONE_PILLAR = 0x216,
    PAL_BONE_PILLAR_FIRE = 0x221,
    PAL_UNK_22A = 0x22A,
    PAL_WINGED_GUARD = 0x22B,
    PAL_BAT = 0x22C,
    PAL_CROW = 0x22F,
    PAL_HUNTING_GIRL = 0x231,
    PAL_UNK_232 = 0x232,
    PAL_SPECTRAL_SWORD = 0x234,
    PAL_SPECTRAL_SWORD_WEAPON_1 = 0x235,
    PAL_SPECTRAL_SWORD_WEAPON_2 = 0x236,
    PAL_SEALED_DOOR = 0x245,
    PAL_BREAKABLE = 0x249,
    PAL_BREAKABLE_DEBRIS = 0x24D,
    PAL_CUTSCENE = 0x251,
};

// Used when a constant value E_ID is used for both psx and pspeu
// The E_ID() macro should be used when psx uses a constant value, but pspeu
// uses a bss reference
enum OVL_EXPORT(Entities) {
    E_NONE,
    E_BREAKABLE,              // DAI_EntityBreakable,
    E_EXPLOSION,              // EntityExplosion,
    E_PRIZE_DROP,             // EntityPrizeDrop,
    E_DAMAGE_DISPLAY,         // EntityDamageDisplay,
    E_RED_DOOR,               // DAI_EntityRedDoor,
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion,
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb,
    E_ROOM_FOREGROUND,        // EntityRoomForeground,
    E_STAGE_NAME_POPUP,       // EntityStageNamePopup,
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop,
    E_RELIC_ORB,              // EntityRelicOrb,
    E_HEART_DROP,             // EntityHeartDrop,
    E_ENEMY_BLOOD,            // EntityEnemyBlood,
    E_MESSAGE_BOX,            // EntityMessageBox,
    E_DUMMY_F,                // EntityDummy,
    E_DUMMY_10,               // EntityDummy,
    E_BACKGROUND_BLOCK,       // DAI_EntityBackgroundBlock,
    E_LOCK_CAMERA,            // DAI_EntityLockCamera,
    E_UNK_13,                 // EntityUnkId13,
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants,
    E_GREY_PUFF,              // EntityGreyPuff,
    E_UNK_16,                 // func_us_801C0BA4,
    E_UNK_17,                 // func_us_801D97D0,
    E_UNK_18,                 // func_us_801D9F5C,
    E_UNK_19,                 // EntityBlock,
    E_STATUE,                 // EntityStatue,
    E_BELL,                   // EntityBell,
    E_UNK_1C,                 // func_us_801C1EE4,
    E_UNK_1D,                 // func_us_801C2068,
    E_UNK_1E,                 // func_us_801C220C,
    E_CLOUDS,                 // EntityClouds,
    E_UNK_20,                 // func_us_801C34FC,
    E_UNK_21,                 // func_us_801C23A4,
    E_UNK_22,                 // EntityChair,
    E_PRIEST,                 // EntityPriest,
    E_PRIEST_BLADES,          // EntityPriestBlades,
    E_PRIEST_BLADE_DEBRIS,    // EntityPriestBladeDebris,
    E_UNK_26,                 // EntityBellHelper,
    E_CORNER_GUARD,           // EntityCornerGuard,
    E_UNK_28,                 // func_us_801D1C24,
    E_BONE_PILLAR_HEAD,       // EntityBonePillarHead,
    E_BONE_PILLAR_FIRE,       // EntityBonePillarFireBreath,
    E_BONE_PILLAR_PIECES,     // EntityBonePillarDeathParts,
    E_BONE_PILLAR_SPIKE_BALL, // EntityBonePillarSpikeBall,
    E_UNK_2D,                 // func_us_801C3644,
    E_UNK_2E,                 // func_us_801C3D44,
    E_UNK_2F,                 // func_us_801C3850,
    E_UNK_30,                 // func_us_801C379C,
    E_UNK_31,                 // func_us_801C3ED8,
    E_BONE_HALBERD,           // EntityBoneHalberd,
    E_BONE_HALBERD_NAGINATA,  // EntityBoneHalberdNaginata,
    E_BONE_HALBERD_PARTS,     // EntityBoneHalberdParts,
    E_WINGED_GUARD,           // EntityWingedGuard,
    E_WINGED_GUARD_PARTS,     // EntityWingedGuardParts,
    E_BAT,                    // EntityBat,
    E_BLACK_CROW,             // EntityBlackCrow,
    E_BLUE_CROW,              // EntityBlueRaven,
    E_SKELERANG,              // EntitySkelerang,
    E_SKELERANG_BOOMERANG,    // EntitySkelerangBoomerang,
    E_SKELERANG_UNKNOWN,      // EntitySkelerangUnknown,
    E_HUNTING_GIRL,           // EntityHuntingGirl,
    E_HUNTING_GIRL_SPIRIT,    // EntityHuntingGirlSpirit,
    E_SPECTRAL_SWORD,         // EntitySpectralSword,
    E_SPECTRAL_SWORD_AURA,    // EntitySpectralSwordAura,
    E_SPECTRAL_SWORD_WEAPON,  // EntitySpectralSwordWeapon,
    E_UNK_42,                 // EntityWingedGuardSpawner,
    E_SEALED_DOOR,            // EntitySealedDoor,
    E_BREAKABLE_DEBRIS,       // EntityBreakableDebris,
    E_CUTSCENE,               // DAI_EntityCutscene,
    E_UNK_46,                 // func_us_801C5920,
    E_UNK_47,                 // func_us_801C5B88,
    E_MIST_DOOR,              // EntityMistDoor,
    NUM_ENTITIES,
};

extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[]; // e_room_bg
extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
// extern EInit g_EInitDamageNum;
// extern EInit g_EInit_801809A4; // Unused
extern EInit g_EInitStatueBlock;
extern EInit g_EInitPriest;
// extern EInit g_EInit_801809C8; // Unused
extern EInit D_us_801809D4;
extern EInit g_EInitCornerGuard;
extern EInit D_us_801809EC;
extern EInit g_EInitBonePillarHead;
extern EInit g_EInitBonePillarPieces;
extern EInit g_EInitBonePillarFireBreath;
extern EInit g_EInitBonePillarSpikeBall;
extern EInit g_EInitBoneHalberd;
extern EInit g_EInitBoneHalberdNaginata;
extern EInit g_EInitWingedGuard;
extern EInit g_EInitWingedGuardParts;
extern EInit g_EInitBat;
extern EInit g_EInitBlueRaven;
extern EInit g_EInitBlackCrow;
extern EInit g_EInitSkelerang;
extern EInit g_EInitSkelerangBoomerang;
extern EInit g_EInitHuntingGirl;
extern EInit g_EInitSpectralSword;
extern EInit g_EInitSpectralSwordAura;
extern EInit g_EInitSpectralSwordWeapon;

#endif
