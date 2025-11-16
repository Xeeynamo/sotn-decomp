// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CAT_H
#define CAT_H

#define STAGE_IS_CAT

#include "stage.h"

#define OVL_EXPORT(x) CAT_##x

#include "../pfn_entity_update.h"

enum OVL_EXPORT(Palette) {
    PAL_NONE = 0,
    PAL_LIGHT_SWITCH_HIDDEN = 0x094,
    PAL_LIGHT_SWITCH_GREEN = 0x099,
    PAL_LIGHT_SWITCH_YELLOW = 0x09A,
    PAL_SPIKES_DUST = 0x09B,
    PAL_HELLFIRE_BEAST_CAST_TWO = 0x15F,
    PAL_BONE_ARK_PROJECTILE = 0x160,
    PAL_BONE_ARK_LIGHTNING_BALL = 0x162,
    PAL_HELLFIRE_BEAST_THORSHAMMER = 0x16C,
    PAL_HELLFIRE_BEAST_FLAMEPILLAR = 0x16D,
    PAL_BONE_ARK_LIGHTNING_PRIM = 0x19F,
    PAL_BONE_ARK_PROJECTILE_EXPLODE = 0x200,
    PAL_HELLFIRE_BEAST_PRIMONE = 0x208,
    PAL_HELLFIRE_BEAST_PRIMTWO = 0x230,
    PAL_HELLFIRE_BEAST_LIGHTNING = 0x24A,
    PAL_BREAKABLE = 0x256,
    PAL_HELLFIRE_BEAST_CAST_ONE = 0x300,
};

enum OVL_EXPORT(Entities) {
    E_NONE,
    E_BREAKABLE,                        // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,                        // EntityExplosion
    E_PRIZE_DROP,                       // EntityPrizeDrop
    E_DAMAGE_DISPLAY,                   // EntityDamageDisplay
    E_RED_DOOR,                         // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,                // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,                   // EntitySoulStealOrb
    E_ROOM_FOREGROUND,                  // EntityRoomForeground
    E_STAGE_NAME_POPUP,                 // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,                  // EntityEquipItemDrop
    E_RELIC_ORB,                        // EntityRelicOrb
    E_HEART_DROP,                       // EntityHeartDrop
    E_ENEMY_BLOOD,                      // EntityEnemyBlood
    E_MESSAGE_BOX,                      // EntityMessageBox
    E_DUMMY_F,                          // EntityDummy
    E_DUMMY_10,                         // EntityDummy
    E_BACKGROUND_BLOCK,                 // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,                      // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                         // EntityUnkId13
    E_EXPLOSION_VARIANTS,               // EntityExplosionVariants
    E_GREY_PUFF,                        // EntityGreyPuff
    E_UNK_16,                           // func_us_801C4C7C
    E_UNK_17,                           // func_us_801C589C
    E_UNK_18,                           // func_us_801C5DF4
    E_UNK_19,                           // func_us_801C56A0
    E_UNK_1A,                           // func_us_801CA13C
    E_SPIKE_ROOM_LIGHT_SWITCH,          // EntitySpikeRoomLightSwitch
    E_SPIKES,                           // EntitySpikes
    E_SPIKES_PARTS,                     // EntitySpikesParts
    E_SPIKES_DUST,                      // EntitySpikesDust
    E_SPIKE_ROOM_DARKNESS,              // EntitySpikeRoomDarkness
    E_SPIKES_DAMAGE,                    // EntitySpikesDamage
    E_UNK_21,                           // func_us_801B8AD0
    E_UNK_22,                           // func_us_801B87E8
    E_UNK_23,                           // func_us_801BACF4
    E_UNK_24,                           // func_us_801B972C
    E_UNK_25,                           // func_us_801B9D1C
    E_UNK_26,                           // func_us_801B9A74
    E_UNK_27,                           // func_us_801B951C
    E_UNK_28,                           // func_us_801B907C
    E_UNK_29,                           // func_us_801BA388
    E_UNK_2A,                           // func_us_801BA164
    E_ELEVATOR,                         // EntityElevator
    E_COFFIN,                           // EntityCoffin
    E_BIG_RED_FIREBALL,                 // EntityBigRedFireball
    E_DISCUS_LORD,                      // EntityDiscusLord
    E_DISCUS,                           // EntityDiscus
    E_DISCUS_TRAIL,                     // EntityDiscusTrail
    E_DISCUS_CHAIN,                     // EntityDiscusChain
    E_HELLFIRE_BEAST,                   // EntityHellfireBeast
    E_HELLFIRE_BEAST_THORS_HAMMER,      // EntityHellfireBeastThorsHammer
    E_HELLFIRE_BEAST_FLAME_PILLAR,      // EntityHellfireBeastFlamePillar
    E_HELLFIRE_BEAST_FLAME_PILLAR_ANIM, // EntityHellfireBeastFlamePillarAnimation
    E_HELLFIRE_BEAST_PUNCH_HITBOX,      // EntityHellfireBeastPunchHitbox
    E_BONE_ARK,                         // EntityBoneArk
    E_BONE_ARK_SKELETON,                // EntityBoneArkSkeleton
    E_BONE_ARK_LOWER_NECK,              // EntityBoneArkLowerNeck
    E_BONE_ARK_UPPER_NECK,              // EntityBoneArkUpperNeck
    E_BONE_ARK_SKULL,                   // EntityBoneArkSkull
    E_BONE_ARK_PROJECTILE,              // EntityBoneArkProjectile
    E_BONE_ARK_ATTACK_EFFECTS,          // EntityBoneArkAttackEffects
    E_LOSSOTH,                          // EntityLossoth
    E_LOSSOTH_EFFECTS,                  // EntityLossothEffects
    E_LOSSOTH_FIREBALL,                 // EntityLossothFireball
    E_LOSSOTH_NAPALM,                   // EntityLossothNapalmFlare
    E_LOSSOTH_FLAMES,                   // EntityLossothFlames
    E_UNK_43,                           // func_us_801BB4CC
    E_GRAVE_KEEPER,                     // EntityGraveKeeper
    E_GRAVE_KEEPER_HITBOX,              // EntityGraveKeeperHitbox
    E_TOMBSTONE,                        // EntityTombstone
    E_GREMLIN,                          // EntityGremlin
    E_GREMLIN_EFFECT,                   // EntityGremlinEffect
    E_GREMLIN_FIRE,                     // EntityGremlinFire
    E_UNK_4A,                           // EntityLargeSlime
    E_UNK_4B,                           // func_us_801D3D08
    E_UNK_4C,                           // EntitySlime
    E_UNK_4D,                           // func_us_801D4744
    E_WERESKELETON,                     // EntityWereskeleton
    E_ID_42,                            // func_us_801CE958
    E_ID_43,                            // func_us_801CEA2C
    E_THORNWEED,                        // EntityThornweed
    E_CORPSEWEED,                       // EntityCorpseweed
    E_CORPSEWEED_PROJECTILE,            // EntityCorpseweedProjectile
    E_BLOOD_SKELETON,                   // EntityBloodSkeleton
    NUM_ENTITIES,
};

extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitDamageNum;
extern EInit g_EInitEnvironment;
extern EInit g_EInitGremlin;
extern EInit g_EInitGremlinFire;
extern EInit g_EInitLockCamera;
extern EInit g_EInitObtainable;
extern EInit g_EInitWereskeleton;
extern EInit D_us_80180A88;

#endif
