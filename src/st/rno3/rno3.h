// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO3_H
#define RNO3_H

#include <stage.h>

#define OVL_EXPORT(x) RNO3_##x
#define STAGE_IS_RNO3

enum Palettes {
    PAL_NONE,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,                 // EntityBreakable
    E_EXPLOSION,                 // EntityExplosion
    E_PRIZE_DROP,                // EntityPrizeDrop
    E_DAMAGE_DISPLAY,            // EntityDamageDisplay
    E_RED_DOOR,                  // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,         // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,            // EntitySoulStealOrb
    E_ROOM_FOREGROUND,           // EntityRoomForeground
    E_STAGE_NAME_POPUP,          // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,           // EntityEquipItemDrop
    E_RELIC_ORB,                 // EntityRelicOrb
    E_HEART_DROP,                // EntityHeartDrop
    E_ENEMY_BLOOD,               // EntityEnemyBlood
    E_MESSAGE_BOX,               // EntityMessageBox
    E_DUMMY_F,                   // EntityDummy
    E_DUMMY_10,                  // EntityDummy
    E_BACKGROUND_BLOCK,          // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,               // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                  // EntityUnkId13
    E_EXPLOSION_VARIANTS,        // EntityExplosionVariants
    E_GREY_PUFF,                 // EntityGreyPuff
    E_CASTLE_DOOR,               // EntityCastleDoor
    E_SHUTTING_WINDOW,           // EntityShuttingWindow
    E_BACKGROUND_BUSHES,         // EntityBackgroundBushes
    E_BACKGROUND_TREES,          // EntityBackgroundTrees
    E_UNK_1A,                    // func_us_801B1674
    E_LIGHTNING_THUNDER,         // EntityLightningThunder
    E_LIGHTNING_CLOUD,           // EntityLightningCloud
    E_FIRE_WARG,                 // EntityFireWarg
    E_FIRE_WARG_WAVE_ATTACK,     // EntityFireWargWaveAttack
    E_UNK_ID2F,                  // EntityUnkId2F
    E_UNK_ID30,                  // EntityUnkId30
    E_UNK_ID31,                  // EntityUnkId31
    E_EXPLOSION3,                // EntityExplosion3
    E_FIRE_WARG_DEATH_BEAMS,     // EntityFireWargDeathBeams
    E_UNK_24,                    // func_us_801C1E70
    E_UNK_25,                    // func_us_801C2380
    E_UNK_26,                    // func_us_801C247C
    E_UNK_27,                    // func_us_801C2A10
    E_UNK_28,                    // func_us_801C2FF0
    E_UNK_29,                    // func_us_801C34A0
    E_BLADE_SOLDIER_DEATH_PARTS, // EntityBladeSoldierDeathParts
    E_UNK_2B,                    // func_us_801C35F8
    E_UNK_2C,                    // func_us_801C3DE0
    E_UNK_2D,                    // func_us_801C406C
    E_UNK_2E,                    // func_us_801C4178
    E_UNK_2F,                    // func_us_801C4334
    E_UNK_30,                    // func_us_801C4468
    E_UNK_31,                    // func_us_801C48D8
    E_UNK_32,                    // func_us_801C4B44
    E_UNK_33,                    // func_us_801C4C50
    E_VENUS_WEED,                // EntityVenusWeed
    E_UNK_35,                    // func_us_801C5850
    E_UNK_36,                    // func_us_801C5F40
    E_VENUS_WEED_DART,           // EntityVenusWeedDart
    E_VENUS_WEED_SPIKE,          // EntityVenusWeedSpike
    E_CAVERN_DOOR_LEVER,         // EntityCavernDoorLever
    E_CAVERN_DOOR_PLATFORM,      // EntityCavernDoorPlatform
    E_UNK_3B,                    // func_us_801B1E38
    E_WEIGHTS_SWITCH,            // EntityWeightsSwitch
    E_PATH_BLOCK_SMALL_WEIGHT,   // EntityPathBlockSmallWeight
    E_UNK_3E,                    // func_us_801B2578
    E_HEART_ROOM_SWITCH,         // EntityHeartRoomSwitch
    E_HEART_ROOM_GOLD_DOOR,      // EntityHeartRoomGoldDoor
    E_MERMAN_ROCK_LEFT_SIDE,     // EntityMermanRockLeftSide
    E_MERMAN_ROCK_RIGHT_SIDE,    // EntityMermanRockRightSide
    E_JEWEL_SWORD_DOOR,          // EntityJewelSwordDoor
    E_FALLING_ROCK2,             // EntityFallingRock2
    E_STAIRWAY_PIECE,            // EntityStairwayPiece
    E_FALLING_ROCK,              // EntityFallingRock
    E_UNK_47,                    // func_us_801B3C88
    E_ALUCARD_WATER_EFFECT,      // EntityAlucardWaterEffect
    E_SPLASH_WATER,              // EntitySplashWater
    E_SURFACING_WATER,           // EntitySurfacingWater
    E_SIDE_WATER_SPLASH,         // EntitySideWaterSplash
    E_SMALL_WATER_DROP,          // EntitySmallWaterDrop
    E_WATER_DROP,                // EntityWaterDrop
    E_UNK_4E,                    // func_us_801C8B8C
    NUM_ENTITIES,
};

#endif // RNO3_H
