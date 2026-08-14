// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO1_H
#define BO1_H

#include <stage.h>

#define STAGE_IS_BO1

enum Palettes {
    PAL_NONE,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,          // EntityBreakable
    E_EXPLOSION,          // EntityExplosion
    E_PRIZE_DROP,         // EntityPrizeDrop
    E_DAMAGE_DISPLAY,     // EntityDamageDisplay
    E_RED_DOOR,           // EntityRedDoor
    E_INTENSE_EXPLOSION,  // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,     // EntitySoulStealOrb
    E_ROOM_FOREGROUND,    // EntityRoomForeground
    E_STAGE_NAME_POPUP,   // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,    // EntityEquipItemDrop
    E_RELIC_ORB,          // EntityRelicOrb
    E_HEART_DROP,         // EntityHeartDrop
    E_ENEMY_BLOOD,        // EntityEnemyBlood
    E_MESSAGE_BOX,        // EntityMessageBox
    E_DUMMY_F,            // EntityDummy
    E_DUMMY_10,           // EntityDummy
    E_BACKGROUND_BLOCK,   // EntityBackgroundBlock
    E_LOCK_CAMERA,        // EntityLockCamera
    E_UNK_ID13,           // EntityUnkId13
    E_EXPLOSION_VARIANTS, // EntityExplosionVariants
    E_GREY_PUFF,          // EntityGreyPuff
    E_UNK_16,             // func_us_801BA388_from_cat
    E_UNK_17,             // func_us_801BA164_from_cat
    E_UNK_18,             // EntityGranfaloon
    E_UNK_19,             // func_us_801A2F2C
    E_UNK_1A,             // func_us_801A3480
    E_UNK_1B,             // func_us_801A38EC
    E_UNK_1C,             // func_us_801A2774
    E_UNK_1D,             // func_us_801A2BC4
    E_UNK_1E,             // func_us_801A2CC4
    E_UNK_1F,             // func_us_801A2D90
    E_UNK_20,             // func_us_801A4394
    E_UNK_21,             // func_us_801A45D0
    E_UNK_22,             // func_us_801A518C
    E_UNK_23,             // func_us_801A493C
    E_UNK_24,             // func_us_801A4AF4
    E_LIFE_UPSPAWN,       // EntityLifeUpSpawn
    NUM_ENTITIES,
};

#endif // BO1_H
