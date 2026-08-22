// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO5_H
#define BO5_H

#include <stage.h>

#define STAGE_IS_BO5

enum Palettes {
    PAL_NONE = 0,
    PAL_CASTLE_WALL_1 = 0x74,
    PAL_BACKGROUND_SKY_LAND = 0xC5,
    PAL_CASTLE_WALL_2 = 0xC8,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,                // EntityBreakable
    E_EXPLOSION,                // EntityExplosion
    E_PRIZE_DROP,               // EntityPrizeDrop
    E_DAMAGE_DISPLAY,           // EntityDamageDisplay
    E_RED_DOOR,                 // EntityRedDoor
    E_INTENSE_EXPLOSION,        // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,           // EntitySoulStealOrb
    E_ROOM_FOREGROUND,          // EntityRoomForeground
    E_STAGE_NAME_POPUP,         // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,          // EntityEquipItemDrop
    E_RELIC_ORB,                // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,     // EntityPersistentItemDrop
    E_ENEMY_BLOOD,              // EntityEnemyBlood
    E_MESSAGE_BOX,              // EntityMessageBox
    E_DUMMY_F,                  // EntityDummy
    E_DUMMY_10,                 // EntityDummy
    E_BACKGROUND_BLOCK,         // EntityBackgroundBlock
    E_LOCK_CAMERA,              // EntityLockCamera
    E_UNK_ID13,                 // EntityUnkId13
    E_EXPLOSION_VARIANTS,       // EntityExplosionVariants
    E_GREY_PUFF,                // EntityGreyPuff
    E_UNK_16,                   // func_801A8620
    E_STAINED_GLASS,            // EntityStainedGlass
    E_STAINED_GLASS_BACKGROUND, // EntityStainedGlassBackground
    E_BLOCK,                    // EntityBlock
    E_STATUE,                   // EntityStatue
    E_BELL,                     // EntityBell
    E_CASTLE_WALL1,             // EntityCastleWall1
    E_CASTLE_WALL2,             // EntityCastleWall2
    E_STAIRCASE,                // EntityStaircase
    E_CLOUDS,                   // EntityClouds
    E_BACKGROUND_SKY_LAND,      // EntityBackgroundSkyLand
    E_RBO3DOOR,                 // EntityRbo3Door
    E_UNK_22,                   // func_us_801A1C14
    E_UNK_23,                   // func_us_801A425C
    E_UNK_24,                   // func_us_801A4430
    E_UNK_25,                   // func_us_801A3FD4
    E_UNK_26,                   // func_us_801A3E78
    E_UNK_27,                   // func_us_801A3B88
    E_LIFE_UPSPAWN,             // EntityLifeUpSpawn
    E_UNK_29,                   // func_us_801A4494
    E_CUTSCENE,                 // EntityCutscene
    E_UNK_2B,                   // func_us_801A5F88
    E_UNK_2C,                   // func_us_801A62B4
    E_UNK_2D,                   // func_801B1D68
    E_UNK_2E,                   // RicSetDeadPrologue
    NUM_ENTITIES,
};

#endif // BO5_H
