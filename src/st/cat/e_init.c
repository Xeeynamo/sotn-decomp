// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

void EntityBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void EntityRedDoor(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityPersistentItemDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntityLava(Entity* self);
void EntityCavernBackgroundLossoth(Entity* self);
void EntityCavernBackgroundDiscusLord(Entity* self);
void EntityLavaEmbers(Entity* self);
void EntityLavaGlow(Entity* self);
void EntitySpikeRoomLightSwitch(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikeRoomDarkness(Entity* self);
void EntitySpikesDamage(Entity* self);
void func_us_801B8AD0(Entity* self);
void func_us_801B87E8(Entity* self);
void func_us_801BACF4(Entity* self);
void EntitySecretWallLeft(Entity* self);
void EntitySecretWall(Entity* self);
void EntityBreakableWallSegment(Entity* self);
void EntityBreakableWallParticles(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void func_us_801BA388(Entity* self);
void func_us_801BA164(Entity* self);
void EntityElevator(Entity* self);
void EntityCoffin(Entity* self);
void EntityBigRedFireball(Entity* self);
void EntityDiscusLord(Entity* self);
void EntityDiscus(Entity* self);
void EntityDiscusTrail(Entity* self);
void EntityDiscusChain(Entity* self);
void EntityHellfireBeast(Entity* self);
void EntityHellfireBeastThorsHammer(Entity* self);
void EntityHellfireBeastFlamePillar(Entity* self);
void EntityHellfireBeastFlamePillarAnimation(Entity* self);
void EntityHellfireBeastPunchHitbox(Entity* self);
void EntityBoneArk(Entity* self);
void EntityBoneArkSkeleton(Entity* self);
void EntityBoneArkLowerNeck(Entity* self);
void EntityBoneArkUpperNeck(Entity* self);
void EntityBoneArkSkull(Entity* self);
void EntityBoneArkProjectile(Entity* self);
void EntityBoneArkAttackEffects(Entity* self);
void EntityLossoth(Entity* self);
void EntityLossothEffects(Entity* self);
void EntityLossothFireball(Entity* self);
void EntityLossothNapalmFlare(Entity* self);
void EntityLossothFlames(Entity* self);
void func_us_801BB4CC(Entity* self);
void EntityGraveKeeper(Entity* self);
void EntityGraveKeeperHitbox(Entity* self);
void EntityTombstone(Entity* self);
void EntityGremlin(Entity* self);
void EntityGremlinEffect(Entity* self);
void EntityGremlinFire(Entity* self);
void EntityLargeSlime(Entity* self);
void func_us_801D3D08(Entity* self);
void EntitySlime(Entity* self);
void func_us_801D4744(Entity* self);
void EntityWereskeleton(Entity* self);
void func_us_801CEA2C(Entity* self);
void func_us_801CE958(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void EntityBloodSkeleton(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    EntityRedDoor,
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityPersistentItemDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityLava,
    EntityCavernBackgroundLossoth,
    EntityCavernBackgroundDiscusLord,
    EntityLavaEmbers,
    EntityLavaGlow,
    EntitySpikeRoomLightSwitch,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikeRoomDarkness,
    EntitySpikesDamage,
    func_us_801B8AD0,
    func_us_801B87E8,
    func_us_801BACF4,
    EntitySecretWallLeft,
    EntitySecretWall,
    EntityBreakableWallSegment,
    EntityBreakableWallParticles,
    EntityBreakableWallDebris,
    func_us_801BA388,
    func_us_801BA164,
    EntityElevator,
    EntityCoffin,
    EntityBigRedFireball,
    EntityDiscusLord,
    EntityDiscus,
    EntityDiscusTrail,
    EntityDiscusChain,
    EntityHellfireBeast,
    EntityHellfireBeastThorsHammer,
    EntityHellfireBeastFlamePillar,
    EntityHellfireBeastFlamePillarAnimation,
    EntityHellfireBeastPunchHitbox,
    EntityBoneArk,
    EntityBoneArkSkeleton,
    EntityBoneArkLowerNeck,
    EntityBoneArkUpperNeck,
    EntityBoneArkSkull,
    EntityBoneArkProjectile,
    EntityBoneArkAttackEffects,
    EntityLossoth,
    EntityLossothEffects,
    EntityLossothFireball,
    EntityLossothNapalmFlare,
    EntityLossothFlames,
    func_us_801BB4CC,
    EntityGraveKeeper,
    EntityGraveKeeperHitbox,
    EntityTombstone,
    EntityGremlin,
    EntityGremlinEffect,
    EntityGremlinFire,
    EntityLargeSlime,
    func_us_801D3D08,
    EntitySlime,
    func_us_801D4744,
    EntityWereskeleton,
    func_us_801CEA2C,
    func_us_801CE958,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityBloodSkeleton,
};

// Common
// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};

// Bone Ark
EInit g_EInitBoneArk = {ANIMSET_OVL(5), 0x0D, 0x48, PAL_BONE_ARK, ENEMY_BONE_ARK};
EInit g_EInitBoneArkSkeleton = {ANIMSET_OVL(5), 0x01, 0x48, PAL_BONE_ARK, ENEMY_BONE_ARK_SKELETON};
EInit g_EInitBoneArkNeck = {ANIMSET_OVL(5), 0x11, 0x48, PAL_BONE_ARK, ENEMY_INTERACTABLE};
EInit g_EInitBoneArkAttackEffects = {ANIMSET_OVL(5), 0x0E, 0x48, PAL_BONE_ARK, ENEMY_BONE_ARK};
EInit g_EInitBoneArkProjectile = {ANIMSET_OVL(5), 0x15, 0x48, PAL_BONE_ARK, ENEMY_BONE_ARK_PROJECTILE};

EInit g_EInitSpikeRoomLightSwitch = {ANIMSET_OVL(2), 0x01, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitElevator = {ANIMSET_OVL(2), 0x03, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit D_us_801811E8 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitCoffin = {ANIMSET_OVL(1), 0x13, 0x00, PAL_NONE, ENEMY_BREAKABLE};

// Discus Lord
EInit g_EInitDiscusLord = {ANIMSET_OVL(4), 0x01, 0x49, PAL_DISCUS_LORD_HELLFIRE_BEAST, ENEMY_DISCUS_LORD};
EInit g_EInitDiscus = {ANIMSET_OVL(4), 0x10, 0x49, PAL_DISCUS_LORD_HELLFIRE_BEAST, ENEMY_DISCUS_LORD_DISCUS};

// Hellfire Beast
EInit g_EInitHellfireBeast = {ANIMSET_OVL(4), 0x19, 0x49, PAL_DISCUS_LORD_HELLFIRE_BEAST, ENEMY_HELLFIRE_BEAST};
EInit g_EInitHellfireBeastPunchHitbox = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_HELLFIRE_BEAST_PUNCH_HITBOX};
EInit g_EInitHellfireBeastFlamePillar = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_HELLFIRE_BEAST_FLAME_PILLAR};
EInit g_EInitHellfireBeastThorsHammer = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_HELLFIRE_BEAST_THORS_HAMMER};

// Lossoth
EInit g_EInitLossoth = {ANIMSET_OVL(3), 0x00, 0x50, PAL_LOSSOTH, ENEMY_LOSSOTH};
EInit g_EInitLossothEffects = {ANIMSET_OVL(3), 0x00, 0x50, PAL_LOSSOTH, ENEMY_INTERACTABLE};
EInit g_EInitLossothAttack = {ANIMSET_OVL(3), 0x00, 0x50, PAL_LOSSOTH, ENEMY_LOSSOTH_ATTACK};

// Grave Keeper
EInit g_EInitGraveKeeper = {ANIMSET_OVL(9), 0x01, 0x4D, PAL_GRAVE_KEEPER_TOMBSTONE, ENEMY_GRAVE_KEEPER};
EInit g_EInitGraveKeeperHitbox = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_GRAVE_KEEPER_HITBOX};

// Tombstone
EInit g_EInitTombstone = {ANIMSET_OVL(9), 0x15, 0x4D, PAL_GRAVE_KEEPER_TOMBSTONE, ENEMY_TOMBSTONE};

// Gremlin
EInit g_EInitGremlin = {ANIMSET_OVL(10), 0x00, 0x4F, PAL_GREMLIN, ENEMY_GREMLIN};
EInit D_us_801812F0 = {ANIMSET_OVL(10), 0x00, 0x4F, PAL_GREMLIN, ENEMY_INTERACTABLE}; // unused
EInit g_EInitGremlinFire = {ANIMSET_OVL(10), 0x00, 0x4F, PAL_GREMLIN, ENEMY_GREMLIN_FIRE};

// Large Slime
EInit g_EInitLargeSlime = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_LARGE_SLIME};

// Slime
EInit g_EInitSlime = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SLIME};

// Wereskeleton
EInit g_EInitWereskeleton = {ANIMSET_OVL(6), 0x01, 0x49, PAL_WERESKELETON, ENEMY_WERESKELETON};
EInit D_us_80180A88 = {ANIMSET_OVL(6), 0x00, 0x49, PAL_WERESKELETON, ENEMY_WERESKELETON_BONE};

// Thornweed
EInit g_EInitThornweed = {ANIMSET_OVL(11), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};

// Corpseweed
EInit D_us_801812F4 = {ANIMSET_OVL(11), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED}; // unused
EInit g_EInitCorpseweed = {ANIMSET_OVL(11), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};
EInit g_EInitCorpseweedProjectile = {ANIMSET_OVL(11), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};

// Blood Skeleton
EInit g_EInitBloodSkeleton = {ANIMSET_OVL(13), 0x00, 0x4C, PAL_BLOOD_SKELETON, ENEMY_BLOOD_SKELETON};
