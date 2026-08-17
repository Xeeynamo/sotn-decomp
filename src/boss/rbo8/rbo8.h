// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO8_H
#define RBO8_H

#include <stage.h>

#define STAGE_IS_RBO8

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
    E_UNK_16,               // func_us_80195D80
    E_UNK_17,               // func_us_80197B1C
    E_UNK_18,               // func_us_801980E4
    E_UNK_19,               // func_us_80198210
    E_UNK_1A,               // func_us_801983EC
    E_UNK_1B,               // func_us_8019C7B8_from_rcen
    E_UNK_1C,               // func_us_80198964
    E_UNK_1D,               // func_us_801991D4
    E_MINOTAUR_SPIT_LIQUID, // EntityMinotaurSpitLiquid
    E_UNK_1F,               // func_us_8019921C
    E_UNK_20,               // func_us_8019943C
    E_UNK_21,               // func_us_8019953C
    E_UNK_22,               // func_us_80199A58
    E_LIFE_UPSPAWN,         // EntityLifeUpSpawn
    NUM_ENTITIES,
};

#endif // RBO8_H
