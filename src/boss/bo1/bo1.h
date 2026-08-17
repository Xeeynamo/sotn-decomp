// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO1_H
#define BO1_H

#include <stage.h>

#define BOSS_IS_BO1

enum Palettes {
    PAL_NONE,
    PAL_BASE = 0x200,
    PAL_EXPLOSION_FLAME = 0x2E0,
};

enum EntityID {
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
    E_BOSS_DOOR,            // EntityBossDoor
    E_UNK_17,               // func_us_801BA164_from_cat
    E_GRANFALOON,           // EntityGranfaloon
    E_GRANFALOON_TENTACLE,  // EntityGranfaloonTentacle
    E_TENTACLE_HEAD,        // EntityTentacleHead
    E_TENTACLE_LASER,       // EntityTentacleLaser
    E_BODY_PART_SHELL,      // EntityBodyPartShell
    E_BODY_PART_DEAD_PIECE, // EntityBodyPartDeadPiece
    E_UNK_1E,               // func_us_801A2CC4
    E_UNK_1F,               // func_us_801A2D90
    E_ZOMBIE_FALLING,       // EntityZombieFalling
    E_ZOMBIE_ENEMY,         // EntityZombieEnemy
    E_EXPLOSION_FLAME,      // EntityExplosionFlame
    E_UNK_23,               // func_us_801A493C
    E_HOMING_LASER,         // EntityHomingLaser
    E_LIFE_UPSPAWN,         // EntityLifeUpSpawn
    NUM_ENTITIES,
};

#endif // BO1_H
