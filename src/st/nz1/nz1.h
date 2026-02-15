// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef NZ1_H
#define NZ1_H

#include <stage.h>

#define OVL_EXPORT(x) NZ1_##x
#define STAGE_IS_NZ1

enum Palettes {
    PAL_NONE,
    PAL_SPIKES_DUST = 0x161,
    PAL_UNK_200 = 0x200,
    PAL_UNK_206 = 0x206,
    PAL_UNK_20A = 0x20A,
    PAL_UNK_20F = 0x20F,
    PAL_UNK_220 = 0x220,
    PAL_UNK_223 = 0x223,
    PAL_WALL_CANDELABRA_A = 0x228,
    PAL_WALL_CANDELABRA_B = 0x229,
    PAL_BREAKABLE = 0x22A,
    PAL_BREAKABLE_DEBRIS = 0x22E,
    PAL_UNK_232 = 0x232,
    PAL_UNK_238 = 0x238,
    PAL_UNK_239 = 0x239,
    // puff params 0,1
    PAL_PUFF_OPAQUE_OFFSET = 0x2E0,
    // puff params 2 (not used directly, PAL_PUFF_OPAQUE_OFFSET + 3)
    PAL_PUFF_OPAQUE_2 = 0x2E3,
    // puff params 3 (not used directly, PAL_PUFF_OPAQUE_OFFSET + 4)
    PAL_PUFF_OPAQUE_3 = 0x2E4
};

enum EntityIDs {
    E_NONE,
    E_BREAKABLE,                // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,                // EntityExplosion
    E_PRIZE_DROP,               // EntityPrizeDrop
    E_DAMAGE_DISPLAY,           // EntityDamageDisplay
    E_RED_DOOR,                 // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,        // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,           // EntitySoulStealOrb
    E_ROOM_FOREGROUND,          // EntityRoomForeground
    E_STAGE_NAME_POPUP,         // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,          // EntityEquipItemDrop
    E_RELIC_ORB,                // EntityRelicOrb
    E_HEART_DROP,               // EntityHeartDrop
    E_ENEMY_BLOOD,              // EntityEnemyBlood
    E_MESSAGE_BOX,              // EntityMessageBox
    E_DUMMY_F,                  // EntityDummy
    E_DUMMY_10,                 // EntityDummy
    E_BACKGROUND_BLOCK,         // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,              // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                 // EntityUnkId13
    E_EXPLOSION_VARIANTS,       // EntityExplosionVariants
    E_GREY_PUFF,                // EntityGreyPuff
    E_BRIDGE_TRIGGER,           // EntityBridgeBreakTrigger
    E_EXPLODE_PUFF_OPAQUE,      // EntityExplosionPuffOpaque
    E_CLOUDS,                   // EntityClouds
    E_BACKGROUND_GEARS,         // EntityBackgroundGears
    E_GEAR_SIDEWAYS_LARGE,      // EntityGearSidewaysLarge
    E_GEAR_HORIZONTAL,          // EntityGearHorizontal
    E_GEAR_VERTICAL,            // EntityGearVertical
    E_GEAR_SIDEWAYS_SMALL,      // EntityGearSidewaysSmall
    E_WALL_GEAR,                // EntityWallGear
    E_PENDULUM_ANCHOR,          // EntityPendulumAnchor
    E_PENDULUM_BONE_CHAIN,      // EntityPendulumBoneChain
    E_PENDULUM_WEIGHT,          // EntityPendulumWeight
    E_BREAKABLE_WALL,           // EntityBreakableWall
    E_SECRET_WALL_DEBRIS,       // EntitySecretWallDebris
    E_ROOM_EXIT,                // EntityRoomExit
    E_BREAKABLE_WALL_PARTIAL,   // EntityBreakableWallPartial
    E_SECRET_AREA_DOOR,         // EntitySecretAreaDoor
    E_WATER_FOREGROUND,         // EntityWaterForeground
    E_ALUCARD_WATER_EFFECT,     // EntityAlucardWaterEffect
    E_SPLASH_WATER,             // EntitySplashWater
    E_SURFACING_WATER,          // EntitySurfacingWater
    E_SIDE_WATER_SPLASH,        // EntitySideWaterSplash
    E_SMALL_WATER_DROP,         // EntitySmallWaterDrop
    E_WATER_DROP,               // EntityWaterDrop
    E_SPIKES,                   // EntitySpikes
    E_SPIKES_PARTS,             // EntitySpikesParts
    E_SPIKES_DUST,              // EntitySpikesDust
    E_SPIKES_DAMAGE,            // EntitySpikesDamage
    E_SKULL_LORD,               // EntitySkullLord
    E_SKULL_LORD_OUTLINE,       // EntitySkullLordOutline
    E_SKULL_LORD_FLAMES,        // EntitySkullLordFlames
    E_SKULL_LORD_PIECES,        // EntitySkullLordPieces
    E_HARPY,                    // EntityHarpy
    E_HARPY_DAGGER,             // EntityHarpyDagger
    E_HARPY_FLAME,              // EntityHarpyFlame
    E_HARPY_KICK,               // EntityHarpyKick
    E_HARPY_FEATHER,            // EntityHarpyFeather
    E_CLOAKED_KNIGHT,           // EntityCloakedKnight
    E_CLOAKED_KNIGHT_CLOAK,     // EntityCloakedKnightCloak
    E_CLOAKED_KNIGHT_SWORD,     // EntityCloakedKnightSword
    E_CLOAKED_KNIGHT_AURA,      // EntityCloakedKnightAura
    E_SWORD_LORD,               // EntitySwordLord
    E_SWORD_LORD_ATTACK_HITBOX, // EntitySwordLordAttackHitbox
    E_VANDAL_SWORD,             // EntityVandalSword
    E_VANDAL_SWORD_DEATH,       // EntityVandalSwordDeath
    E_VANDAL_SWORD_HITBOX,      // EntityVandalSwordHitbox
    E_PHANTOM_SKULL,            // EntityPhantomSkull
    E_PHANTOM_SKULL_TRAIL,      // EntityPhantomSkullTrail
    E_FLAIL_GUARD,              // EntityFlailGuard
    E_FLAIL_GUARD_FLAIL,        // EntityFlailGuardFlail
    E_BRIDGE_BACKGROUND_PIECE,  // EntityBridgeBackgroundPiece
    E_FLEA_ARMOR,               // EntityFleaArmor
    E_FLEA_ARMOR_ATTACK_HITBOX, // EntityFleaArmorAttackHitbox
    E_FLEA_MAN,                 // EntityFleaMan
    E_BREAKABLE_DEBRIS,         // OVL_EXPORT(EntityBreakableDebris)
    E_BOSS_DOOR_TRIGGER,        // EntityBossDoorTrigger
    E_BOSS_DOORS,               // EntityBossDoors
    E_KARASUMAN,                // EntityKarasuman
    E_KARASUMAN_FEATHER_ATTACK, // EntityKarasumanFeatherAttack
    E_KARASUMAN_ORB_ATTACK,     // EntityKarasumanOrbAttack
    E_KARASUMAN_RAVEN_ATTACK,   // EntityKarasumanRavenAttack
    E_KARASUMAN_FEATHER,        // EntityKarasumanFeather
    E_KARASUMAN_RAVEN_ABSORB,   // EntityKarasumanRavenAbsorb
    E_LIFE_UP_SPAWN,            // EntityLifeUpSpawn
    E_MEDUSA_HEAD_SPAWNER,      // EntityMedusaHeadSpawner
    E_MEDUSA_HEAD_BLUE,         // EntityMedusaHeadBlue
    E_MEDUSA_HEAD_YELLOW,       // EntityMedusaHeadYellow
    NUM_ENTITIES,
};

#ifdef VERSION_PSP
extern s32 E_ID(ALUCARD_WATER_EFFECT);
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(BACKGROUND_GEARS);
extern s32 E_ID(BOSS_DOORS);
extern s32 E_ID(BOSS_DOOR_TRIGGER);
extern s32 E_ID(BREAKABLE_DEBRIS);
extern s32 E_ID(BREAKABLE_WALL);
extern s32 E_ID(BREAKABLE_WALL_PARTIAL);
extern s32 E_ID(BRIDGE_BACKGROUND_PIECE);
extern s32 E_ID(BRIDGE_TRIGGER);
extern s32 E_ID(CLOAKED_KNIGHT);
extern s32 E_ID(CLOAKED_KNIGHT_AURA);
extern s32 E_ID(CLOAKED_KNIGHT_CLOAK);
extern s32 E_ID(CLOAKED_KNIGHT_SWORD);
extern s32 E_ID(CLOUDS);
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(FLAIL_GUARD);
extern s32 E_ID(FLAIL_GUARD_FLAIL);
extern s32 E_ID(FLEA_ARMOR);
extern s32 E_ID(FLEA_ARMOR_ATTACK_HITBOX);
extern s32 E_ID(FLEA_MAN);
extern s32 E_ID(GEAR_HORIZONTAL);
extern s32 E_ID(GEAR_SIDEWAYS_LARGE);
extern s32 E_ID(GEAR_SIDEWAYS_SMALL);
extern s32 E_ID(GEAR_VERTICAL);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(HARPY);
extern s32 E_ID(HARPY_DAGGER);
extern s32 E_ID(HARPY_FEATHER);
extern s32 E_ID(HARPY_FLAME);
extern s32 E_ID(HARPY_KICK);
extern s32 E_ID(KARASUMAN);
extern s32 E_ID(KARASUMAN_FEATHER);
extern s32 E_ID(KARASUMAN_FEATHER_ATTACK);
extern s32 E_ID(KARASUMAN_ORB_ATTACK);
extern s32 E_ID(KARASUMAN_RAVEN_ABSORB);
extern s32 E_ID(KARASUMAN_RAVEN_ATTACK);
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(MEDUSA_HEAD_BLUE);
extern s32 E_ID(MEDUSA_HEAD_SPAWNER);
extern s32 E_ID(MEDUSA_HEAD_YELLOW);
extern s32 E_ID(PENDULUM_ANCHOR);
extern s32 E_ID(PENDULUM_BONE_CHAIN);
extern s32 E_ID(PENDULUM_WEIGHT);
extern s32 E_ID(PHANTOM_SKULL);
extern s32 E_ID(PHANTOM_SKULL_TRAIL);
extern s32 E_ID(ROOM_EXIT);
extern s32 E_ID(SECRET_AREA_DOOR);
extern s32 E_ID(SECRET_WALL_DEBRIS);
extern s32 E_ID(SIDE_WATER_SPLASH);
extern s32 E_ID(SKULL_LORD);
extern s32 E_ID(SKULL_LORD_FLAMES);
extern s32 E_ID(SKULL_LORD_OUTLINE);
extern s32 E_ID(SKULL_LORD_PIECES);
extern s32 E_ID(SMALL_WATER_DROP);
extern s32 E_ID(SPIKES);
extern s32 E_ID(SPIKES_DAMAGE);
extern s32 E_ID(SPIKES_DUST);
extern s32 E_ID(SPIKES_PARTS);
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(SURFACING_WATER);
extern s32 E_ID(SWORD_LORD);
extern s32 E_ID(SWORD_LORD_ATTACK_HITBOX);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(VANDAL_SWORD);
extern s32 E_ID(VANDAL_SWORD_DEATH);
extern s32 E_ID(VANDAL_SWORD_HITBOX);
extern s32 E_ID(WALL_GEAR);
extern s32 E_ID(WATER_DROP);
extern s32 E_ID(WATER_FOREGROUND);
#endif

extern EInit g_EInitEnvironment;

#endif // NZ1_H
