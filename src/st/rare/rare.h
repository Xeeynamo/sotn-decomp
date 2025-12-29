// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RARE_H
#define RARE_H

#include <stage.h>

#define OVL_EXPORT(x) RARE_##x
#define STAGE_IS_RARE
#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
    PAL_TORCH_A = 0x5A,
    PAL_TORCH_B = 0x5B,
    PAL_BACKGROUND_DOOR_RUBBLE = 0x9E,
    PAL_FOUNTAIN_WATER = 0xC0,
    // 0xC0 - 0xCA are cycled in EntityFountainWater based on g_Timer
    PAL_FOUNTAIN_WATER_MAX = 0xCA,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,              // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,              // EntityExplosion
    E_PRIZE_DROP,             // EntityPrizeDrop
    E_DAMAGE_DISPLAY,         // EntityDamageDisplay
    E_RED_DOOR,               // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb
    E_ROOM_FOREGROUND,        // EntityRoomForeground
    E_STAGE_NAME_POPUP,       // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop
    E_RELIC_ORB,              // EntityRelicOrb
    E_HEART_DROP,             // EntityHeartDrop
    E_ENEMY_BLOOD,            // EntityEnemyBlood
    E_MESSAGE_BOX,            // EntityMessageBox
    E_DUMMY_F,                // EntityDummy
    E_DUMMY_10,               // EntityDummy
    E_BACKGROUND_BLOCK,       // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,            // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,               // EntityUnkId13
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants
    E_GREY_PUFF,              // EntityGreyPuff
    E_UNK_16,                 // func_us_801B1BC8
    E_UNK_17,                 // func_us_801B2800
    E_UNK_18,                 // func_us_801B28F4
    E_UNK_19,                 // func_us_801B29E0
    E_UNK_1A,                 // func_us_801B7290
    E_CORNER_GUARD_ATTACK,    // EntityCornerGuardAttack
    E_UNK_1C,                 // func_us_801B7FF8
    E_UNK_1D,                 // func_us_801B80E8
    E_UNK_1E,                 // func_us_801B81CC
    E_UNK_1F,                 // func_us_801B2B2C
    E_UNK_20,                 // func_us_801B3B34
    E_UNK_21,                 // func_us_801B4E9C
    E_BREAKABLE_FLOOR_SECRET, // EntityBreakableFloorSecret
    E_BREAKABLE_DEBRIS,       // OVL_EXPORT(EntityBreakableDebris)
    E_BACKGROUND_DOOR_RUBBLE, // EntityBackgroundDoorRubble
    E_FOUNTAIN_WATER,         // EntityFountainWater
    E_BOSS_TORCH,             // EntityBossTorch
    E_BOSS_DOORS,             // EntityBossDoors
    E_UNK_28,                 // func_us_801B5448
    E_UNK_29,                 // func_us_801B65F8
    E_UNK_2A,                 // func_us_801B6824
    NUM_ENTITIES,
};

#endif // RARE_H
