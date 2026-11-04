// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO6_H
#define RBO6_H

#include <stage.h>

#define STAGE_IS_RBO6

enum Palettes {
    PAL_NONE,
    PAL_DRACULA = 0x200,
    PAL_DRACULA_WINGS = 0x201,
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
    E_BOSS_DRACULA,         // EntityBossDracula
    E_DRACULA_SMALL_HAND,   // EntityDraculaSmallHand
    E_DRACULA_DECOR,        // EntityDraculaDecoration
    E_DRACULA_ARM,          // EntityDraculaArm
    E_DRACULA_HAND,         // EntityDraculaHand
    E_DRACULA_PUPPET_HEAD,  // EntityDraculaPuppetHead
    E_DRACULA_VERTEBRA,     // EntityDraculaPuppetVertebra
    E_DRACULA_WINGS,        // EntityDraculaWings
    E_SUMMONING_LIGHTNING,  // EntitySummoningLightning
    E_BOSS_PORTAL,          // EntityBossPortal
    E_SUMMONED_BOSS,        // EntitySummonedBoss
    E_SQUISH_BLOOD_BALLS,   // EntitySquishBloodBalls
    E_BLUE_FLASH_ORB,       // EntityBlueFlashingOrb
    E_RAINBOW_TRIANGLE,     // EntityRainbowTriangleAttack
    E_TRIANGLE_CORNER_GLOW, // EntityTriangleCornerGlow
    E_BLUE_ORB_SHADOW,      // EntityBlueOrbShadow
    E_LAUNCH_CUTSCENE,               // EntityLaunchCutscene
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
