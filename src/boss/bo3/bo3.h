// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO3_H
#define BO3_H

#include <stage.h>

#define STAGE_IS_BO3

enum Palettes {
    PAL_NONE,
    PAL_SCYLLA = 0x200,
    PAL_BREAKABLE_STATUE = 0x228,
    PAL_PUFF_OPAQUE_OFFSET = 0x2E0,
};

#ifdef VERSION_PSP
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(WATER_DROP);
extern s32 E_ID(UNK_1C);
extern s32 E_ID(UNK_1D);
extern s32 E_ID(UNK_2D);
extern s32 E_ID(UNK_2E);
extern s32 E_ID(UNK_2F);
extern s32 E_ID(UNK_30);
extern s32 E_ID(SCYLLA);
extern s32 E_ID(SCYLLA_TENTACLES);
extern s32 E_ID(SCYLLA_WOLF_HEAD);
extern s32 E_ID(SCYLLA_WATER_BLADE);
extern s32 E_ID(SCYLLA_WATER_ORB_BEAM);
extern s32 E_ID(SCYLLA_BUBBLE_SKULL);
extern s32 E_ID(SCYLLA_WATER_ORB);
extern s32 E_ID(SCYLLA_FALLING_ROCK);
extern s32 E_ID(SCYLLA_DROPLET);
extern s32 E_ID(WYRM);
extern s32 E_ID(WYRM_BODY_PART);
extern s32 E_ID(WYRM_HEAD);
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
extern s32 E_ID(UNK_3E);
extern s32 E_ID(BREAKABLE_WALL_DEBRIS);
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(UNK_41);
extern s32 E_ID(UNK_42);
extern s32 E_ID(BREAKABLE_STATUE_BROKEN);
#endif

typedef enum EntityID {
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
    E_PERSISTENT_ITEM_DROP,    // EntityPersistentItemDrop
    E_ENEMY_BLOOD,             // EntityEnemyBlood
    E_MESSAGE_BOX,             // EntityMessageBox
    E_DUMMY_F,                 // EntityDummy
    E_DUMMY_10,                // EntityDummy
    E_BACKGROUND_BLOCK,        // EntityBackgroundBlock
    E_LOCK_CAMERA,             // EntityLockCamera
    E_UNK_ID13,                // EntityUnkId13
    E_EXPLOSION_VARIANTS,      // EntityExplosionVariants
    E_GREY_PUFF,               // EntityGreyPuff
    E_DUMMY_16,                // EntityDummy
    E_SPLASH_WATER,            // EntitySplashWater
    E_DUMMY_18,                // EntityDummy
    E_DUMMY_19,                // EntityDummy
    E_DUMMY_1A,                // EntityDummy
    E_WATER_DROP,              // EntityWaterDrop
    E_UNK_1C,                  // func_us_801C12B0
    E_UNK_1D,                  // func_us_801C15F8
    E_DUMMY_1E,                // EntityDummy
    E_DUMMY_1F,                // EntityDummy
    E_DUMMY_20,                // EntityDummy
    E_DUMMY_21,                // EntityDummy
    E_DUMMY_22,                // EntityDummy
    E_DUMMY_23,                // EntityDummy
    E_DUMMY_24,                // EntityDummy
    E_DUMMY_25,                // EntityDummy
    E_DUMMY_26,                // EntityDummy
    E_DUMMY_27,                // EntityDummy
    E_DUMMY_28,                // EntityDummy
    E_DUMMY_29,                // EntityDummy
    E_DUMMY_2A,                // EntityDummy
    E_DUMMY_2B,                // EntityDummy
    E_DUMMY_2C,                // EntityDummy
    E_UNK_2D,                  // func_us_801A07CC
    E_UNK_2E,                  // func_us_801A0A80
    E_UNK_2F,                  // func_us_801A1120
    E_UNK_30,                  // func_us_801A16E4
    E_SCYLLA,                  // EntityScylla
    E_SCYLLA_TENTACLES,        // EntityScyllaTentacles
    E_SCYLLA_WOLF_HEAD,        // EntityScyllaWolfHead
    E_SCYLLA_WATER_BLADE,      // EntityScyllaWaterBlade
    E_SCYLLA_WATER_ORB_BEAM,   // EntityScyllaWaterOrbBeam
    E_SCYLLA_BUBBLE_SKULL,     // EntityScyllaBubbleSkull
    E_SCYLLA_WATER_ORB,        // EntityScyllaWaterOrb
    E_SCYLLA_FALLING_ROCK,     // EntityScyllaFallingRock
    E_SCYLLA_DROPLET,          // EntityScyllaDroplet
    E_WYRM,                    // EntityWyrm
    E_WYRM_BODY_PART,          // EntityWyrmBodyPart
    E_WYRM_HEAD,               // EntityWyrmHead
    E_EXPLODE_PUFF_OPAQUE,     // EntityExplosionPuffOpaque
    E_UNK_3E,                  // func_us_801A1BE8
    E_BREAKABLE_WALL_DEBRIS,   // EntityBreakableWallDebris
    E_LIFE_UP_SPAWN,           // EntityLifeUpSpawn
    E_UNK_41,                  // func_us_801A6370
    E_UNK_42,                  // func_us_801A6568
    E_BREAKABLE_STATUE_BROKEN, // EntityBreakableStatueBroken
    NUM_ENTITIES,
};

enum BossMgrState {
    BOSS_MGR_IDLE = 0,
    BOSS_MGR_FIGHT_ON = 0x01,       // Scylla and the Wyrm have spawned
    BOSS_MGR_DEFEAT = 0x02,         // Scylla has been defeated
    BOSS_MGR_TERMINATED = 0x04,     // Scylla is gone, entities get destroyed
    BOSS_MGR_FLAMES_2_END = 0x08,   // second wave of death flames is over
    BOSS_MGR_FLAMES_1_END = 0x10,   // first wave of death flames is over
    BOSS_MGR_FLAMES_2_START = 0x20, // second wave of death flames begins
    BOSS_MGR_FLAMES_1_START = 0x40, // first wave of death flames begins
};

extern s32 g_BossMgrState;

#endif // BO3_H
