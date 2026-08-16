// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO1_H
#define RBO1_H

#include <stage.h>

#define STAGE_IS_RBO1

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
    E_UNK_16,               // func_us_801923A8
    E_UNK_17,               // func_us_80192C5C
    E_UNK_18,               // func_us_80192F84
    E_UNK_19,               // func_us_801936FC
    E_UNK_1A,               // func_us_80193C2C
    E_UNK_1B,               // func_us_80193E24
    E_UNK_1C,               // func_us_80194108
    E_UNK_1D,               // func_us_801947E4
    E_UNK_1E,               // func_us_80194C50
    E_BOSS_ROOM_BLOCK,      // EntityBossRoomBlock
    E_LIFE_UPSPAWN,         // EntityLifeUpSpawn
    NUM_ENTITIES,
};

#endif // RBO1_H
