// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO4
#define OVL_EXPORT(x) NO4_##x

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    // /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP,
    // /* 0x04 */ E_NUMERIC_DAMAGE,
    // /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION = 0x06,
    // /* 0x07 */ E_SOUL_STEAL_ORB,
    // /* 0x08 */ E_ROOM_FOREGROUND,
    // /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0x0A,
    // /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP = 0x0C,
    // /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX = 0x0E,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11 = 0x11,
    // /* 0x12 */ E_ID_12,
    // /* 0x13 */ E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    // /* 0x16 */ E_ID_16,
    /* 0x17 */ E_SPLASH_WATER = 0x17,
    /* 0x18 */ E_SURFACING_WATER,
    /* 0x19 */ E_SIDE_WATER_SPLASH,
    // /* 0x1A */ E_ID_1A,
    /* 0x1B */ E_WATER_DROP = 0x1B,
    // /* 0x1C */ E_ID_1C,
    // /* 0x1D */ E_ID_1D,
    // /* 0x1E */ E_ID_1E,
    // /* 0x1F */ E_ID_1F,
    // /* 0x20 */ E_ID_20,
    // /* 0x21 */ E_ID_21,
    // /* 0x22 */ E_ID_22,
    // /* 0x23 */ E_ID_23,
    // /* 0x24 */ E_ID_24,
    // /* 0x25 */ E_ID_25,
    /* 0x26 */ E_ID_26 = 0x26,
    /* 0x27 */ E_ID_27 = 0x27,
    // /* 0x28 */ E_ID_28,
    // /* 0x29 */ E_ID_29,
    // /* 0x2A */ E_ID_2A,
    // /* 0x2B */ E_ID_2B,
    // /* 0x2C */ E_ID_2C,
    // /* 0x2D */ E_ID_2D,
    /* 0x2E */ E_FERRYMAN = 0x2E,
    // /* 0x2F */ E_ID_2F,
    // /* 0x30 */ E_ID_30,
    // /* 0x31 */ E_ID_31,
    // /* 0x32 */ E_ID_32,
    // /* 0x33 */ E_ID_33,
    // /* 0x34 */ E_ID_34,
    /* 0x35 */ E_ID_35 = 0x35,
    // /* 0x36 */ E_ID_36,
    // /* 0x37 */ E_ID_37,
    // /* 0x38 */ E_ID_38,
    // /* 0x39 */ E_ID_39,
    /* 0x3A */ E_UNK_NO4_SPEAR_GUARD = 0x3A,
    /* 0x3B */ E_SPEAR_GUARD_BLOCK,
    /* 0x3C */ E_TOAD,
    /* 0x3D */ E_FISHHEAD_SPAWNER,
    /* 0x3E */ E_FISHHEAD,
    /* 0x3F */ E_FISHHEAD_TOP,
    /* 0x40 */ E_FISHHEAD_FIREBALL,
    /* 0x41 */ E_FISHHEAD_PARTICLES,
    /* 0x42 */ E_FISHHEAD_DEATH_PARTS,
    /* 0x43 */ E_FISHHEAD_FIRE_BREATH,
    // /* 0x44 */ E_ID_44,
    // /* 0x45 */ E_ID_45,
    /* 0x46 */ E_FROZEN_SHADE_CRYSTAL = 0x46,
    /* 0x47 */ E_FROZEN_SHADE_ICICLE,
    /* 0x48 */ E_FROZEN_SHADE_ICICLE_UNK,
    // /* 0x49 */ E_ID_49,
    /* 0x4A */ E_SPEAR_GUARD = 0x4A,
    /* 0x4B */ E_THROWN_SPEAR,
    /* 0x4C */ E_BONE_ARCHER,
    /* 0x4D */ E_BONE_ARCHER_ARROW,
    // /* 0x4E */ E_ID_4E,
    /* 0x4F */ E_ID_4F = 0x4F,
    // /* 0x50 */ E_ID_50,
    // /* 0x51 */ E_ID_51,
    /* 0x52 */ E_BREAKABLE_WALL_DEBRIS = 0x52,
    // /* 0x53 */ E_ID_53,
    /* 0x54 */ E_ID_54 = 0x54,
    // /* 0x55 */ E_ID_55,
    /* 0x56 */ E_SKELETON_APE = 0x56,
    /* 0x57 */ E_SKELETON_APE_PUNCH,
    /* 0x58 */ E_SKELETON_APE_BARREL,
    /* 0x59 */ E_THROWN_BARREL,
    /* 0x5A */ E_KILLER_FISH_DEATH_PUFF = 0x5A,
    // /* 0x5B */ E_ID_5B,
    /* 0x5C */ E_ID_5C = 0x5C,
} EntityIDs;

extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);
extern void EntitySkeletonApe(Entity* entity);

extern EInit g_EInitBreakable;
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
// extern EInit g_EInitDamageNum;
// extern EInit D_us_80180BF8;
extern EInit g_EInitToad;
extern EInit g_EInitFrog;
extern EInit g_EInitFishhead;
extern EInit g_EInitFishheadSpawner;
extern EInit g_EInitFishheadFireball;
extern EInit g_EInitFishheadPieces;
extern EInit g_EInitFishheadFireBreath;
extern EInit g_EInitBat;
extern EInit g_EInitFrozenShade;
extern EInit g_EInitFrozenShadeCrystal;
extern EInit g_EInitFrozenShadeIcicle;
extern EInit g_EInitSpearGuard;
extern EInit g_EInitThrownSpear;
extern EInit g_EInitBoneArcher;
extern EInit g_EInitBoneArcherArrow;
// extern EInit D_us_80180CB8;
extern EInit g_EInitSkeletonApe;
extern EInit g_EInitSkeletonApeBarrel;
extern EInit g_EInitSkeletonApePunch;
extern EInit g_EInitKillerFish;

extern s32 D_us_80181108;
extern s16 D_us_8018159C[];
extern s16 D_us_801DF788;
extern s16 D_us_801DF78A;
extern s8 D_us_801DF78E;
extern s8 D_us_801DF78F;
