// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNZ1_H
#define RNZ1_H

#include <stage.h>

#define STAGE_IS_RNZ1
#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
    PAL_SPIKES_DUST = 0x161,
    PAL_BREAKABLE_DEBRIS = 0x226,
    PAL_WALL_CANDELABRA_A = 0x228,
    PAL_WALL_CANDELABRA_B = 0x229,
    PAL_BREAKABLE = 0x22A,
    PAL_PUFF_OPAQUE_OFFSET = 0x2E0,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,              // EntityBreakable
    E_EXPLOSION,              // EntityExplosion
    E_PRIZE_DROP,             // EntityPrizeDrop
    E_DAMAGE_DISPLAY,         // EntityDamageDisplay
    E_RED_DOOR,               // EntityRedDoor
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb
    E_ROOM_FOREGROUND,        // EntityRoomForeground
    E_STAGE_NAME_POPUP,       // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop
    E_RELIC_ORB,              // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,   // EntityPersistentItemDrop
    E_ENEMY_BLOOD,            // EntityEnemyBlood
    E_MESSAGE_BOX,            // EntityMessageBox
    E_DUMMY_F,                // EntityDummy
    E_DUMMY_10,               // EntityDummy
    E_BACKGROUND_BLOCK,       // EntityBackgroundBlock
    E_LOCK_CAMERA,            // EntityLockCamera
    E_UNK_ID13,               // EntityUnkId13
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants
    E_GREY_PUFF,              // EntityGreyPuff
    E_EXPLODE_PUFF_OPAQUE,    // EntityExplosionPuffOpaque
    E_CLOUDS,                 // EntityClouds
    E_BACKGROUND_GEARS,       // EntityBackgroundGears
    E_GEAR_SIDEWAYS_LARGE,    // EntityGearSidewaysLarge
    E_GEAR_HORIZONTAL,        // EntityGearHorizontal
    E_GEAR_VERTICAL,          // EntityGearVertical
    E_GEAR_SIDEWAYS_SMALL,    // EntityGearSidewaysSmall
    E_WALL_GEAR,              // EntityWallGear
    E_BREAKABLE_WALL,         // EntityBreakableWall
    E_SECRET_WALL_DEBRIS,     // EntitySecretWallDebris
    E_ROOM_EXIT,              // EntityRoomExit
    E_BREAKABLE_WALL_PARTIAL, // EntityBreakableWallPartial
    E_SECRET_AREA_DOOR,       // EntitySecretAreaDoor
    E_WATER_FOREGROUND,       // EntityWaterForeground
    E_ALUCARD_WATER_EFFECT,   // EntityAlucardWaterEffect
    E_SPLASH_WATER,           // EntitySplashWater
    E_SURFACING_WATER,        // EntitySurfacingWater
    E_SIDE_WATER_SPLASH,      // EntitySideWaterSplash
    E_SMALL_WATER_DROP,       // EntitySmallWaterDrop
    E_WATER_DROP,             // EntityWaterDrop
    E_SPIKES,                 // EntitySpikes
    E_SPIKES_PARTS,           // EntitySpikesParts
    E_SPIKES_DUST,            // EntitySpikesDust
    E_SPIKES_DAMAGE,          // EntitySpikesDamage
    E_DARKWING_BAT,           // EntityDarkwingBat
    E_DARKWING_PERCH,         // EntityDarkwingBatPerch
    E_BAT_WINGS,              // EntityDarkwingBatWings
    E_DARKWING_WIND_DUST,     // EntityDarkwingWindDust
    E_FADING_FIREBALL,        // EntityFadingFireball
    E_BOSS_DOOR_TRIGGER,      // EntityBossFightManager
    E_BOSS_DOORS,             // EntityBossDoors
    E_LIFE_UP_SPAWN,          // EntityLifeUpSpawn
    E_CLOAKED_KNIGHT,         // EntityCloakedKnight
    E_CLOAKED_KNIGHT_CLOAK,   // EntityCloakedKnightCloak
    E_CLOAKED_KNIGHT_SWORD,   // EntityCloakedKnightSword
    E_CLOAKED_KNIGHT_AURA,    // EntityCloakedKnightAura
    E_MEDUSA_HEAD_SPAWNER,    // EntityMedusaHeadSpawner
    E_MEDUSA_HEAD_BLUE,       // EntityMedusaHeadBlue
    E_MEDUSA_HEAD_YELLOW,     // EntityMedusaHeadYellow
    E_BREAKABLE_DEBRIS,       // EntityBreakableDebris
    E_VALHALLA_KNIGHT,        // EntityValhallaKnight
    E_UNK_3F,                 // func_us_801C8954_from_are
    E_UNK_40,                 // func_us_801C8AAC_from_are
    E_BOMB_KNIGHT,            // func_us_801BBE58
    E_UNK_42,                 // func_us_801BC650
    E_UNK_43,                 // func_us_801BCE4C
    E_UNK_44,                 // func_us_801BCA5C
    E_UNK_45,                 // func_us_801BCB9C
    E_UNK_46,                 // func_us_801BCD80
    E_UNK_47,                 // func_us_801BCFC8
    E_UNK_48,                 // func_us_801BD398
    E_UNK_49,                 // func_us_801BDA24
    E_CRUSHER,                // func_us_801BD324
    NUM_ENTITIES,
};

extern s32 g_BossFlag;

#endif // RNZ1_H
