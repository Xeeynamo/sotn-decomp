// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO3

#define OVL_EXPORT(x) NO3_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

// NO3 Sound IDs
#define SE_MERMAN_DEATH 0x71D
#define SE_VO_DEATH_STEALS 0x7A0
#define SE_VO_DEATH_LAUGH 0x7A1
#define SE_ITEM_YOINK 0x7A2
#define SE_TREE_BRANCH 0x7A4
#define SE_CASTLE_GATE_MOVE 0x7A5
#define SE_WATER_SPLASH 0x7C2

#define E_PUFF_OPAQUE_PALETTE_OFFSET 0xD0

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_LOCK_CAMERA,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_ID_16,
    /* 0x17 */ E_BG_LIGHTNING,
    /* 0x18 */ E_TRANSP_WATER,
    /* 0x19 */ E_SHUTTING_WINDOW,
    /* 0x1A */ E_CASTLE_DOOR,
    /* 0x1B */ E_BACKGROUND_BUSHES,
    /* 0x1C */ E_BACKGROUND_TREES,
    /* 0x1D */ E_CAVERN_DOOR_LEVER,
    /* 0x1E */ E_CAVERN_DOOR_PLATFORM,
    /* 0x1F */ E_CAVERN_DOOR,
    /* 0x20 */ E_WEIGHTS_SWITCH,
    /* 0x21 */ E_WEIGHT_SMALL,
    /* 0x22 */ E_WEIGHT_TALL,
    /* 0x23 */ E_TRAPDOOR,
    /* 0x24 */ E_MERMAN_ROCK_L,
    /* 0x25 */ E_MERMAN_ROCK_R,
    /* 0x26 */ E_JEWEL_SWORD_DOOR,
    /* 0x27 */ E_FALLING_ROCK_2,
    /* 0x28 */ E_DEATH_SKY_SWIRL,
    /* 0x29 */ E_LIGHTNING_THUNDER,
    /* 0x2A */ E_LIGHTNING_CLOUD,
    /* 0x2B */ E_HEART_ROOM_SWITCH,
    /* 0x2C */ E_HEART_ROOM_DOOR,
    /* 0x2D */ E_FIRE_WARG,
    /* 0x2E */ E_FIRE_WARG_ATTACK,
    /* 0x2F */ E_ID_2F,
    /* 0x30 */ E_ID_30,
    /* 0x31 */ E_ID_31,
    /* 0x32 */ E_EXPLOSION_3,
    /* 0x33 */ E_FIRE_WARG_DEATH,
    /* 0x34 */ E_ALU_WATER_EFFECT,
    /* 0x35 */ E_SPLASH_WATER,
    /* 0x36 */ E_SURFACING_WATER,
    /* 0x37 */ E_SIDE_WATER_SPLASH,
    /* 0x38 */ E_SMALL_WATER_DROP,
    /* 0x39 */ E_WATER_DROP,
    /* 0x3A */ E_MERMAN2,
    /* 0x3B */ E_MERMAN_WATER_SPLASH,
    /* 0x3C */ E_MEDIUM_WATER_SPLASH,
    /* 0x3D */ E_HIGH_WATER_SPLASH,
    /* 0x3E */ E_MERMAN2_SPIT_FIRE,
    /* 0x3F */ E_MERMAN2_DYING,
    /* 0x40 */ E_MERMAN2_JUMP_AIR,
    /* 0x41 */ E_MERMAN,
    /* 0x42 */ E_MERMAN_SPIT_FIRE,
    /* 0x43 */ E_MERMAN_JUMP_AIR,
    /* 0x44 */ E_MERMAN_DYING,
    /* 0x45 */ E_MERMAN_SPAWNER,
    /* 0x46 */ E_BONE_SCIMITAR,
    /* 0x47 */ E_BONE_SCIMITAR_PARTS,
    /* 0x48 */ E_BAT,
    /* 0x49 */ E_TMAP_SHUFF_UNUSED,
    /* 0x4A */ E_WARG,
    /* 0x4B */ E_ID_4B,
    /* 0x4C */ E_ZOMBIE,
    /* 0x4D */ E_ZOMBIE_SPAWNER,
    /* 0x4E */ E_PUSH_ALUCARD,
    /* 0x4F */ E_FOREGROUND_TREE,
    /* 0x50 */ E_FOLIAGE_MAKER,
    /* 0x51 */ E_BACKGROUND_PINE_TREES,
    /* 0x52 */ E_BACKGROUND_PINE_MAKER,
    /* 0x53 */ E_CASTLE_DOOR_TRANSITION,
    /* 0x54 */ E_CASTLE_BRIDGE,
    /* 0x55 */ E_DIST_BG_TREES,
    /* 0x56 */ E_BACKGROUND_WALL,
    /* 0x57 */ E_CUTSCENE,
    /* 0x58 */ E_DEATH_SCENE_MGR,
    /* 0x59 */ E_DEATH_STOLEN_ITEM,
    /* 0x5A */ E_DEATH,
    /* 0x5B */ E_DEATH_SCYTHE,
    /* 0x5C */ E_STAIRWAY_PIECE,
    /* 0x5D */ E_FALLING_ROCK,
    /* 0x5E */ E_DEATH_SCYTHE_SHADOW,
    /* 0x5F */ E_FLYING_OWL_LEAVES,
    /* 0x60 */ E_FALLING_LEAF,
    /* 0x61 */ E_EXPLODE_PUFF_TRANS,
    /* 0x62 */ E_EXPLODE_PUFF_OPAQUE,
} EntityIDs;

extern void ReplaceBreakableWithItemDrop(Entity*);
extern s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags);
extern Primitive* FindFirstUnkPrim(Primitive* poly);

extern u16 g_EInitObtainable[];
extern u16 g_EInitParticle[];
extern s16 D_80182F9C[];
extern s16 D_80182FA8[];
extern s16 D_80182FC8[];
extern s16 D_80182FE8[];
extern u16 g_EInitSpawner[];
extern u16 g_EInitInteractable[];
extern u16 g_EInitLockCamera[];
extern u16 g_EInitCommon[];
extern u16 g_EInitStInteractable[];
extern u16 D_80180B24[];
extern u16 D_80180B30[];
extern u16 D_80180B3C[];
extern u16 g_EInitWaterObject[];
extern u16 g_EInitWaterSplash[];
extern u16 g_EInitMermanFireball[];
extern u16 g_EInitBat[];
extern u16 D_80180BA8[];
extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
extern u8 D_80180DC0[];
extern u8 D_80180DC8[];
extern SVECTOR* D_8018110C;
extern u16 D_80181120[];
extern u16 D_80181130[8];
extern s16 D_801811D0[][2];
extern s16 D_801811E0[];
extern SVECTOR D_801811F0[];
extern u8 D_801811F8;
extern u8 D_80181218[];
extern u8 D_80181224[];
extern u16 D_8018127C[];
extern u16 D_801812A0[];
extern u16 D_801812E2[];
extern u16 D_8018131E[];
extern s16 g_WaterXTbl[];
extern u16 D_801813DC[];
extern u16 D_80181468[];
extern u16 D_801814EC[];
extern u16 D_801817F8[];
extern u8 D_801819D0[];
extern u8 D_801819DC[];
extern s32 D_801819E8[];
extern s32 D_801819EC[];
extern s16 D_801836BC[];
extern u16 D_80180B9C[];

extern s16 D_801832D8[];
extern u8 D_801832E8[];
extern u16 D_801823F4[];
extern u16 D_80182424[];
extern u8* D_80182488[];
extern u16 D_801824E8[];
extern s8 c_HeartPrizes[];
extern s32 D_801824F4[];
extern u8* D_801825A0[];
extern u16 D_80182628[];
extern s32 D_80182638[];
extern u8 D_8018267C[];
extern ObjInit D_80182764[];
extern u8 D_8018383C[];
extern u8 D_80183AF0[];
extern u8 D_80183B04[];
extern u16 g_EInitMerman[];
extern u8 D_80183C44[];
extern u8 D_80183C60[];
extern u8 D_80183C7C[];
extern u8 D_80183C84[];
extern u8 D_80183C98[];
extern s32 D_80183CAC;
extern s32 D_80183CBC;

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***
