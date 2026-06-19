// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO3_H
#define RNO3_H

#include <stage.h>

#define OVL_EXPORT(x) RNO3_##x
#define STAGE_IS_RNO3
#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
};

enum Entities {
  /* 0x00 */ E_NONE,
  /* 0x01 */ E_BREAKABLE,                 // EntityBreakable
  /* 0x02 */ E_EXPLOSION,                 // EntityExplosion
  /* 0x03 */ E_PRIZE_DROP,                // EntityPrizeDrop
  /* 0x04 */ E_DAMAGE_DISPLAY,            // EntityDamageDisplay
  /* 0x05 */ E_RED_DOOR,                  // OVL_EXPORT(EntityRedDoor)
  /* 0x06 */ E_INTENSE_EXPLOSION,         // EntityIntenseExplosion
  /* 0x07 */ E_SOUL_STEAL_ORB,            // EntitySoulStealOrb
  /* 0x08 */ E_ROOM_FOREGROUND,           // EntityRoomForeground
  /* 0x09 */ E_STAGE_NAME_POPUP,          // EntityStageNamePopup
  /* 0x0A */ E_EQUIP_ITEM_DROP,           // EntityEquipItemDrop
  /* 0x0B */ E_RELIC_ORB,                 // EntityRelicOrb
  /* 0x0C */ E_HEART_DROP,                // EntityHeartDrop
  /* 0x0D */ E_ENEMY_BLOOD,               // EntityEnemyBlood
  /* 0x0E */ E_MESSAGE_BOX,               // EntityMessageBox
  /* 0x0F */ E_DUMMY_F,                   // EntityDummy
  /* 0x10 */ E_DUMMY_10,                  // EntityDummy
  /* 0x11 */ E_BACKGROUND_BLOCK,          // OVL_EXPORT(EntityBackgroundBlock)
  /* 0x12 */ E_LOCK_CAMERA,               // OVL_EXPORT(EntityLockCamera)
  /* 0x13 */ E_UNK_ID13,                  // EntityUnkId13
  /* 0x14 */ E_EXPLOSION_VARIANTS,        // EntityExplosionVariants
  /* 0x15 */ E_GREY_PUFF,                 // EntityGreyPuff
  /* 0x16 */ E_CASTLE_DOOR,               // EntityCastleDoor
  /* 0x17 */ E_SHUTTING_WINDOW,           // EntityShuttingWindow
  /* 0x18 */ E_BACKGROUND_BUSHES,         // EntityBackgroundBushes
  /* 0x19 */ E_BACKGROUND_TREES,          // EntityBackgroundTrees
  /* 0x1A */ E_UNK_1A,                    // func_us_801B1674
  /* 0x1B */ E_LIGHTNING_THUNDER,         // EntityLightningThunder
  /* 0x1C */ E_LIGHTNING_CLOUD,           // EntityLightningCloud
  /* 0x1D */ E_FIRE_WARG,                 // EntityFireWarg
  /* 0x1E */ E_FIRE_WARG_WAVE_ATTACK,     // EntityFireWargWaveAttack
  /* 0x1F */ E_UNK_ID2F,                  // EntityUnkId2F
  /* 0x20 */ E_UNK_ID30,                  // EntityUnkId30
  /* 0x21 */ E_UNK_ID31,                  // EntityUnkId31
  /* 0x22 */ E_EXPLOSION3,                // EntityExplosion3
  /* 0x23 */ E_FIRE_WARG_DEATH_BEAMS,     // EntityFireWargDeathBeams
  /* 0x24 */ E_UNK_24,                    // func_us_801C1E70
  /* 0x25 */ E_UNK_25,                    // func_us_801C2380
  /* 0x26 */ E_UNK_26,                    // func_us_801C247C
  /* 0x27 */ E_UNK_27,                    // func_us_801C2A10
  /* 0x28 */ E_UNK_28,                    // func_us_801C2FF0
  /* 0x29 */ E_UNK_29,                    // func_us_801C34A0
  /* 0x2A */ E_BLADE_SOLDIER_DEATH_PARTS, // EntityBladeSoldierDeathParts
  /* 0x2B */ E_UNK_2B,                    // func_us_801C35F8
  /* 0x2C */ E_UNK_2C,                    // func_us_801C3DE0
  /* 0x2D */ E_UNK_2D,                    // func_us_801C406C
  /* 0x2E */ E_UNK_2E,                    // func_us_801C4178
  /* 0x2F */ E_UNK_2F,                    // func_us_801C4334
  /* 0x30 */ E_UNK_30,                    // func_us_801C4468
  /* 0x31 */ E_UNK_31,                    // func_us_801C48D8
  /* 0x32 */ E_UNK_32,                    // func_us_801C4B44
  /* 0x33 */ E_UNK_33,                    // func_us_801C4C50
  /* 0x34 */ E_VENUS_WEED,                // EntityVenusWeed
  /* 0x35 */ E_UNK_35,                    // func_us_801C5850
  /* 0x36 */ E_UNK_36,                    // func_us_801C5F40
  /* 0x37 */ E_VENUS_WEED_DART,           // EntityVenusWeedDart
  /* 0x38 */ E_VENUS_WEED_SPIKE,          // EntityVenusWeedSpike
  /* 0x39 */ E_CAVERN_DOOR_LEVER,         // EntityCavernDoorLever
  /* 0x3A */ E_CAVERN_DOOR_PLATFORM,      // EntityCavernDoorPlatform
  /* 0x3B */ E_UNK_3B,                    // func_us_801B1E38
  /* 0x3C */ E_WEIGHTS_SWITCH,            // EntityWeightsSwitch
  /* 0x3D */ E_PATH_BLOCK_SMALL_WEIGHT,   // EntityPathBlockSmallWeight
  /* 0x3E */ E_UNK_3E,                    // func_us_801B2578
  /* 0x3F */ E_HEART_ROOM_SWITCH,         // EntityHeartRoomSwitch
  /* 0x40 */ E_HEART_ROOM_GOLD_DOOR,      // EntityHeartRoomGoldDoor
  /* 0x41 */ E_MERMAN_ROCK_LEFT_SIDE,     // EntityMermanRockLeftSide
  /* 0x42 */ E_MERMAN_ROCK_RIGHT_SIDE,    // EntityMermanRockRightSide
  /* 0x43 */ E_JEWEL_SWORD_DOOR,          // EntityJewelSwordDoor
  /* 0x44 */ E_FALLING_ROCK2,             // EntityFallingRock2
  /* 0x45 */ E_STAIRWAY_PIECE,            // EntityStairwayPiece
  /* 0x46 */ E_FALLING_ROCK,              // EntityFallingRock
  /* 0x47 */ E_UNK_47,                    // func_us_801B3C88
  /* 0x48 */ E_ALUCARD_WATER_EFFECT,      // EntityAlucardWaterEffect
  /* 0x49 */ E_SPLASH_WATER,              // EntitySplashWater
  /* 0x4A */ E_SURFACING_WATER,           // EntitySurfacingWater
  /* 0x4B */ E_SIDE_WATER_SPLASH,         // EntitySideWaterSplash
  /* 0x4C */ E_SMALL_WATER_DROP,          // EntitySmallWaterDrop
  /* 0x4D */ E_WATER_DROP,                // EntityWaterDrop
  /* 0x4E */ E_UNK_4E,                    // func_us_801C8B8C
};

#endif // RNO3_H
