// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RCHI_H
#define RCHI_H

#include <stage.h>

#define STAGE_IS_RCHI

enum Palettes {
    PAL_NONE,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,               // EntityBreakable
    E_EXPLOSION,               // EntityExplosion
    E_PRIZE_DROP,              // EntityPrizeDrop
    E_DAMAGE_DISPLAY,          // EntityDamageDisplay
    E_RED_DOOR,                // EntityRedDoor
    E_INTENSE_EXPLOSION,       // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,          // EntitySoulStealOrb
    E_ROOM_FOREGROUND,         // EntityRoomForeground
    E_STAGE_NAME_POPUP,        // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,         // EntityEquipItemDrop
    E_RELIC_ORB,               // EntityRelicOrb
    E_HEART_DROP,              // EntityHeartDrop
    E_ENEMY_BLOOD,             // EntityEnemyBlood
    E_MESSAGE_BOX,             // EntityMessageBox
    E_DUMMY_F,                 // EntityDummy
    E_DUMMY_10,                // EntityDummy
    E_BACKGROUND_BLOCK,        // EntityBackgroundBlock
    E_LOCK_CAMERA,             // EntityLockCamera
    E_UNK_ID13,                // EntityUnkId13
    E_EXPLOSION_VARIANTS,      // EntityExplosionVariants
    E_GREY_PUFF,               // EntityGreyPuff
    E_SLOGRA,                  // EntitySlogra
    E_SLOGRA_SPEAR,            // EntitySlograSpear
    E_SLOGRA_SPEAR_PROJECTILE, // EntitySlograSpearProjectile
    E_GAIBON,                  // EntityGaibon
    E_GAIBON_LEG,              // EntityGaibonLeg
    E_SMALL_GAIBON_PROJECTILE, // EntitySmallGaibonProjectile
    E_LARGE_GAIBON_PROJECTILE, // EntityLargeGaibonProjectile
    E_BREAKABLE_DEBRIS,        // EntityBreakableDebris
    E_DEMON_SWITCH_WALL,       // EntityDemonSwitchWall
    E_DEMON_SWITCH,            // EntityDemonSwitch
    E_BREAKABLE_WALL,          // EntityBreakableWall
    E_BREAKABLE_WALL_DEBRIS,   // EntityBreakableWallDebris
    E_THORNWEED,               // EntityThornweed
    E_CORPSEWEED,              // EntityCorpseweed
    E_CORPSEWEED_PROJECTILE,   // EntityCorpseweedProjectile
    E_BAT,                     // EntityBat
    NUM_ENTITIES,
};

#endif // RCHI_H
