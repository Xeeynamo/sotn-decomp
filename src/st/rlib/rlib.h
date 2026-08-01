// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RLIB_H
#define RLIB_H

#include <stage.h>

#define OVL_EXPORT(x) RLIB_##x
#define STAGE_IS_RLIB

enum Palettes {
    PAL_NONE,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,             // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,             // EntityExplosion
    E_PRIZE_DROP,            // EntityPrizeDrop
    E_DAMAGE_DISPLAY,        // EntityDamageDisplay
    E_RED_DOOR,              // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,     // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,        // EntitySoulStealOrb
    E_ROOM_FOREGROUND,       // EntityRoomForeground
    E_STAGE_NAME_POPUP,      // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,       // EntityEquipItemDrop
    E_RELIC_ORB,             // EntityRelicOrb
    E_HEART_DROP,            // EntityHeartDrop
    E_ENEMY_BLOOD,           // EntityEnemyBlood
    E_MESSAGE_BOX,           // EntityMessageBox
    E_DUMMY_F,               // EntityDummy
    E_DUMMY_10,              // EntityDummy
    E_BACKGROUND_BLOCK,      // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,           // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,              // EntityUnkId13
    E_EXPLOSION_VARIANTS,    // EntityExplosionVariants
    E_GREY_PUFF,             // EntityGreyPuff
    E_BACKGROUND_BOOKCASE,   // EntityBackgroundBookcase
    E_BACKGROUND_FURNITURE,  // EntityBackgroundFurniture
    E_BACKGROUND_SHADOW,     // EntityBackgroundShadow
    E_UNK_19,                // func_us_801AFA80_from_lib
    E_UNK_1A,                // func_us_801AE8E8_from_lib
    E_BREAKABLE_HELPER,      // EntityBreakableHelper
    E_UNK_1C,                // func_us_801ADBE8
    E_UNK_1D,                // func_us_80196768_from_rbo0
    E_UNK_1E,                // func_us_801AE414
    E_UNK_1F,                // func_us_801AE534
    E_UNK_20,                // func_us_801AED4C
    E_FISHHEAD_FIREBALL,     // EntityFishheadFireball
    E_UNK_22,                // func_us_801AEFE0
    E_UNK_23,                // func_us_801AF11C
    E_UNK_24,                // func_us_801AF448
    E_UNK_25,                // func_us_801AF9E8
    E_EXPLOSION_PUFF_OPAQUE, // EntityExplosionPuffOpaque
    E_UNK_27,                // func_us_801AFC88
    E_BREAKABLE_DEBRIS,      // OVL_EXPORT(EntityBreakableDebris)
    E_CANDLE_TABLE,          // EntityCandleTable
    NUM_ENTITIES,
};

#endif // RLIB_H
