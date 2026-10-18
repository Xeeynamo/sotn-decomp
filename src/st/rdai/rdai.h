// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RDAI_H
#define RDAI_H

#include <stage.h>

#define STAGE_IS_RDAI

extern EInit g_EInitSpectralSwordAura;

enum Palettes {
    PAL_NONE,
    PAL_CASTLE_WALL_1 = 0x74,
    PAL_CLOUDS = 0xC0,
    PAL_BACKGROUND_SKY_LAND = 0xC5,
    PAL_CASTLE_WALL_2 = 0xC8,
    PAL_ARCHER = 0x212,
    PAL_SPECTRAL_SWORD = 0x215,
    PAL_SNIPER_OF_GOTH = 0x224,
    PAL_IMP = 0x22D,
    PAL_BREAKABLE = 0x230,
    PAL_BREAKABLE_DEBRIS = 0x234,
    PAL_BLACK_PANTHER = 0x238
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
    E_UNK_16,               // func_us_801B1C34
    E_CASTLE_WALL1,         // EntityCastleWall1
    E_CASTLE_WALL2,         // EntityCastleWall2
    E_STAIRCASE,            // EntityStaircase
    E_UNK_1A,               // func_us_801B2C28
    E_UNK_1B,               // func_us_801B3368
    E_UNK_1C,               // func_us_801BFE6C
    E_UNK_1D,               // func_us_801C0240
    E_UNK_1E,               // func_us_801BF830
    E_UNK_1F,               // EntityRdaiUnk1F
    E_UNK_20,               // func_us_801C0528
    E_UNK_21,               // func_us_801C0898
    E_UNK_22,               // func_us_801C0C44
    E_UNK_23,               // EntitySpectralSwordAura
    E_UNK_24,               // func_us_801C17E8
    E_UNK_25,               // func_us_801C1DE8
    E_SNIPER_OF_GOTH,       // EntitySniperOfGoth
    E_SNIPER_OF_GOTH_ARROW, // EntitySniperOfGothArrow
    E_IMP,                  // EntityImp
    E_IMP_SMOKE,            // EntityImpSmoke
    E_CLOUDS,               // EntityClouds
    E_BACKGROUND_SKY_LAND,  // EntityBackgroundSkyLand
    E_UNK_2C,               // EntityRbo3Door
    E_SPIKES,               // EntitySpikes
    E_SPIKES_PARTS,         // EntitySpikesParts
    E_SPIKES_DUST,          // EntitySpikesDust
    E_SPIKES_DAMAGE,        // EntitySpikesDamage
    E_BREAKABLE_DEBRIS,     // EntityBreakableDebris
    E_BLACK_PANTHER,        // EntityBlackPanther
    E_BALLOON_POD,          // EntityBalloonPod
    E_UNK_34,               // EntityImpDeathParticle
    NUM_ENTITIES,
};

#endif // RDAI_H
