// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO6_H
#define RBO6_H

#include <stage.h>

#define STAGE_IS_RBO6

enum Palettes {
    PAL_NONE,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,            // EntityBreakable
    E_EXPLOSION,            // EntityExplosion
    E_PRIZE_DROP,           // EntityPrizeDrop
    E_DAMAGE_DISPLAY,       // EntityDamageDisplay
    E_RED_DOOR,             // EntityRedDoor
    E_INTENSE_EXPLOSION,    // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,       // EntitySoulStealOrb
    E_ROOM_FOREGROUND,      // EntityRoomForeground
    E_STAGE_NAME_POPUP,     // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,      // EntityEquipItemDrop
    E_RELIC_ORB,            // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP, // EntityPersistentItemDrop
    E_ENEMY_BLOOD,          // EntityEnemyBlood
    E_MESSAGE_BOX,          // EntityMessageBox
    E_DUMMY_F,              // EntityDummy
    E_DUMMY_10,             // EntityDummy
    E_BACKGROUND_BLOCK,     // EntityBackgroundBlock
    E_LOCK_CAMERA,          // EntityLockCamera
    E_UNK_ID13,             // EntityUnkId13
    E_EXPLOSION_VARIANTS,   // EntityExplosionVariants
    E_GREY_PUFF,            // EntityGreyPuff
    E_UNK_16,               // func_us_8019D330_from_rcen
    E_UNK_17,               // func_us_8019DB9C
    E_UNK_18,               // func_us_8019FBC0
    E_UNK_19,               // func_us_8019FB04
    E_UNK_1A,               // func_us_8019EADC
    E_UNK_1B,               // func_us_8019EE30
    E_UNK_1C,               // func_us_8019F1CC
    E_UNK_1D,               // func_us_8019FA78
    E_UNK_1E,               // func_us_8019FCB4
    E_UNK_1F,               // func_us_801A01A4
    E_UNK_20,               // func_us_801A0710
    E_UNK_21,               // func_us_801A0860
    E_UNK_22,               // func_us_801A0AB4
    E_UNK_23,               // func_us_801A0DC0
    E_UNK_24,               // func_us_801A11DC
    E_UNK_25,               // func_us_801A1B38
    E_UNK_26,               // func_us_801A1150
    E_UNK_27,               // func_us_801A362C
    E_UNK_28,               // func_us_801A367C
    E_UNK_29,               // func_us_801A9208_from_bo6
    E_UNK_2A,               // func_us_801A37B4
    E_UNK_2B,               // func_us_801A399C
    E_UNK_2C,               // func_us_801A3BE0
    E_UNK_2D,               // func_us_801A4028
    E_BACKGROUND_VORTEX,    // EntityBackgroundVortex
    E_UNK_2F,               // func_us_801B1738
    E_UNK_30,               // func_us_801B2864
    E_UNK_31,               // func_us_801A4594
    E_UNK_32,               // func_us_801A4F14
    NUM_ENTITIES,
};

#endif // RBO6_H
