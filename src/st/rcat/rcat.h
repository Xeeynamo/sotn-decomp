// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RCAT_H
#define RCAT_H

#include <stage.h>

#define OVL_EXPORT(x) RCAT_##x
#define STAGE_IS_RCAT

enum Palettes {
    PAL_NONE,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,                     // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,                     // EntityExplosion
    E_PRIZE_DROP,                    // EntityPrizeDrop
    E_DAMAGE_DISPLAY,                // EntityDamageDisplay
    E_RED_DOOR,                      // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,             // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,                // EntitySoulStealOrb
    E_ROOM_FOREGROUND,               // EntityRoomForeground
    E_STAGE_NAME_POPUP,              // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,               // EntityEquipItemDrop
    E_RELIC_ORB,                     // EntityRelicOrb
    E_HEART_DROP,                    // EntityHeartDrop
    E_ENEMY_BLOOD,                   // EntityEnemyBlood
    E_MESSAGE_BOX,                   // EntityMessageBox
    E_DUMMY_F,                       // EntityDummy
    E_DUMMY_10,                      // EntityDummy
    E_BACKGROUND_BLOCK,              // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,                   // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                      // EntityUnkId13
    E_EXPLOSION_VARIANTS,            // EntityExplosionVariants
    E_GREY_PUFF,                     // EntityGreyPuff
    E_LAVA,                          // EntityLava
    E_CAVERN_BACKGROUND_LOSSOTH,     // EntityCavernBackgroundLossoth
    E_CAVERN_BACKGROUND_DISCUS_LORD, // EntityCavernBackgroundDiscusLord
    E_LAVA_EMBERS,                   // EntityLavaEmbers
    E_SPIKES,                        // EntitySpikes
    E_SPIKES_PARTS,                  // EntitySpikesParts
    E_SPIKES_DUST,                   // EntitySpikesDust
    E_SPIKE_ROOM_DARKNESS,           // EntitySpikeRoomDarkness
    E_SPIKES_DAMAGE,                 // EntitySpikesDamage
    E_UNK_1F,                        // func_us_801B1F1C
    E_UNK_20,                        // func_us_801B87E8_from_cat
    E_UNK_21,                        // func_us_801BACF4_from_cat
    E_UNK_22,                        // func_us_801BEFD8
    E_UNK_23,                        // func_us_801BFF94
    E_UNK_24,                        // func_us_801C0118
    E_UNK_25,                        // func_us_801C02C4
    E_UNK_26,                        // func_us_801C0718
    E_UNK_27,                        // func_us_801C0844
    E_UNK_28,                        // func_us_801C0990
    E_UNK_29,                        // func_us_801C1194
    E_UNK_2A,                        // func_us_801C13B4
    E_UNK_2B,                        // func_us_801C148C
    E_UNK_2C,                        // func_us_801C1804
    E_UNK_2D,                        // func_us_801B3248
    E_SECRET_WALL,                   // EntitySecretWall
    E_BREAKABLE_WALL_SEGMENT,        // EntityBreakableWallSegment
    E_BREAKABLE_WALL_PARTICLES,      // EntityBreakableWallParticles
    E_BREAKABLE_WALL_DEBRIS,         // EntityBreakableWallDebris
    E_SKELETON,                      // EntitySkeleton
    E_SKELETON_THROWN_BONE,          // EntitySkeletonThrownBone
    E_SKELETON_PIECES,               // EntitySkeletonPieces
    E_BLOOD_SKELETON,                // EntityBloodSkeleton
    E_BAT,                           // EntityBat
    NUM_ENTITIES,
};

#endif // RCAT_H
