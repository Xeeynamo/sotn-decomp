// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO4_H
#define RBO4_H

#include <stage.h>

#define STAGE_IS_RBO4

enum Palettes {
    PAL_NONE,
    PAL_THE_CREATURE = 0x200,
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
    E_THE_CREATURE,         // EntityTheCreature
    E_THE_CREATURE_HEAD,    // EntityTheCreatureHead
    E_THE_CREATURE_FLAMES,  // EntityTheCreatureFlames
    E_UNK_19,               // func_us_80198A18
    E_BOSS_FIGHT_MANAGER,   // EntityBossFightManager
    E_BOSS_DOORS,           // EntityBossDoors
    E_LIFE_UP_SPAWN,        // EntityLifeUpSpawn
    NUM_ENTITIES,
};

#endif // RBO4_H
