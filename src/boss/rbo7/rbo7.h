// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO7_H
#define RBO7_H

#include <stage.h>

#define STAGE_IS_RBO7

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
    E_UNK_16,               // func_us_801BAB18_from_bo0
    E_UNK_17,               // func_us_80192B38_from_rbo3
    E_LIFE_UPSPAWN,         // EntityLifeUpSpawn
    E_UNK_19,               // func_us_801940B4
    E_UNK_1A,               // func_us_801957C0
    E_HARPY_KICK,           // EntityHarpyKick
    E_UNK_1C,               // func_us_80195A8C
    E_UNK_1D,               // func_us_80195D04
    E_CTULHU_DEATH,         // EntityCtulhuDeath
    NUM_ENTITIES,
};

#endif // RBO7_H
