// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO3_H
#define BO3_H

#include <stage.h>

#define STAGE_IS_BO3

enum Palettes {
    PAL_NONE,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,             // EntityBreakable
    E_EXPLOSION,             // EntityExplosion
    E_PRIZE_DROP,            // EntityPrizeDrop
    E_DAMAGE_DISPLAY,        // EntityDamageDisplay
    E_RED_DOOR,              // EntityRedDoor
    E_INTENSE_EXPLOSION,     // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,        // EntitySoulStealOrb
    E_ROOM_FOREGROUND,       // EntityRoomForeground
    E_STAGE_NAME_POPUP,      // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,       // EntityEquipItemDrop
    E_RELIC_ORB,             // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,  // EntityPersistentItemDrop
    E_ENEMY_BLOOD,           // EntityEnemyBlood
    E_MESSAGE_BOX,           // EntityMessageBox
    E_DUMMY_F,               // EntityDummy
    E_DUMMY_10,              // EntityDummy
    E_BACKGROUND_BLOCK,      // EntityBackgroundBlock
    E_LOCK_CAMERA,           // EntityLockCamera
    E_UNK_ID13,              // EntityUnkId13
    E_EXPLOSION_VARIANTS,    // EntityExplosionVariants
    E_GREY_PUFF,             // EntityGreyPuff
    E_DUMMY_16,              // EntityDummy
    E_SPLASH_WATER,          // EntitySplashWater
    E_DUMMY_18,              // EntityDummy
    E_DUMMY_19,              // EntityDummy
    E_DUMMY_1A,              // EntityDummy
    E_WATER_DROP,            // EntityWaterDrop
    E_UNK_1C,                // func_us_801C12B0_from_no4
    E_UNK_1D,                // func_us_801C15F8_from_no4
    E_DUMMY_1E,              // EntityDummy
    E_DUMMY_1F,              // EntityDummy
    E_DUMMY_20,              // EntityDummy
    E_DUMMY_21,              // EntityDummy
    E_DUMMY_22,              // EntityDummy
    E_DUMMY_23,              // EntityDummy
    E_DUMMY_24,              // EntityDummy
    E_DUMMY_25,              // EntityDummy
    E_DUMMY_26,              // EntityDummy
    E_DUMMY_27,              // EntityDummy
    E_DUMMY_28,              // EntityDummy
    E_DUMMY_29,              // EntityDummy
    E_DUMMY_2A,              // EntityDummy
    E_DUMMY_2B,              // EntityDummy
    E_DUMMY_2C,              // EntityDummy
    E_UNK_2D,                // func_us_801A07CC
    E_UNK_2E,                // func_us_801A0A80
    E_UNK_2F,                // func_us_801A1120
    E_UNK_30,                // func_us_801A16E4
    E_UNK_31,                // func_us_801A2AEC
    E_UNK_32,                // func_us_801A3CD8
    E_UNK_33,                // func_us_801A365C
    E_UNK_34,                // func_us_801A3EE0
    E_UNK_35,                // func_us_801A42A8
    E_UNK_36,                // func_us_801A4680
    E_UNK_37,                // func_us_801A4988
    E_UNK_38,                // func_us_801A4C0C
    E_UNK_39,                // func_us_801A4E24
    E_UNK_3A,                // func_us_801A5338
    E_UNK_3B,                // func_us_801A57A4
    E_UNK_3C,                // func_us_801A5948
    E_UNK_3D,                // func_us_801A5F0C
    E_UNK_3E,                // func_us_801A1BE8
    E_BREAKABLE_WALL_DEBRIS, // EntityBreakableWallDebris
    E_LIFE_UPSPAWN,          // EntityLifeUpSpawn
    E_UNK_41,                // func_us_801A6370
    E_UNK_42,                // func_us_801A6568
    E_UNK_43,                // func_us_801C123C_from_no4
    NUM_ENTITIES,
};

#endif // BO3_H
