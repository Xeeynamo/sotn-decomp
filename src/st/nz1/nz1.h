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

enum OVL_EXPORT(Entities) {
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
    E_LIFE_UPSPAWN,             // EntityLifeUpSpawn
    E_MEDUSA_HEAD_SPAWNER,      // EntityMedusaHeadSpawner
    E_MEDUSA_HEAD_BLUE,         // EntityMedusaHeadBlue
    E_MEDUSA_HEAD_YELLOW,       // EntityMedusaHeadYellow
    NUM_ENTITIES,
};

#endif // NZ1_H
