// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

void OVL_EXPORT(EntityBreakable)(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void OVL_EXPORT(EntityRedDoor)(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_801C4C7C(Entity* self);
void func_us_801C589C(Entity* self);
void func_us_801C5DF4(Entity* self);
void func_us_801C56A0(Entity* self);
void EntityLavaGlow(Entity* self);
void func_us_801B732C(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikeRoomDarkness(Entity* self);
void EntitySpikesDamage(Entity* self);
void func_us_801B8AD0(Entity* self);
void func_us_801B87E8(Entity* self);
void func_us_801BACF4(Entity* self);
void func_us_801B972C(Entity* self);
void func_us_801B9D1C(Entity* self);
void func_us_801B9A74(Entity* self);
void func_us_801B951C(Entity* self);
void func_us_801B907C(Entity* self);
void func_us_801BA388(Entity* self);
void func_us_801BA164(Entity* self);
void EntityElevator(Entity* self);
void func_us_801BA7FC(Entity* self);
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

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801C4C7C,
    func_us_801C589C,
    func_us_801C5DF4,
    func_us_801C56A0,
    EntityLavaGlow,
    func_us_801B732C,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikeRoomDarkness,
    EntitySpikesDamage,
    func_us_801B8AD0,
    func_us_801B87E8,
    func_us_801BACF4,
    func_us_801B972C,
    func_us_801B9D1C,
    func_us_801B9A74,
    func_us_801B951C,
    func_us_801B907C,
    func_us_801BA388,
    func_us_801BA164,
    EntityElevator,
    func_us_801BA7FC,
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
EInit OVL_EXPORT(
    EInitBreakable) = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x0000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x0000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x0000, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x003};

// Bone Ark
EInit g_EInitBoneArk = {ANIMSET_OVL(0x05), 0x0D, 0x48, 0x0200, 0x02D};
EInit g_EInitBoneArkSkeleton = {ANIMSET_OVL(0x05), 0x01, 0x48, 0x0200, 0x02E};
EInit g_EInitBoneArkNeck = {ANIMSET_OVL(0x05), 0x11, 0x48, 0x0200, 0x005};
EInit g_EInitBoneArkAttackEffects = {
    ANIMSET_OVL(0x05), 0x0E, 0x48, 0x0200, 0x02D};
EInit g_EInitBoneArkProjectile = {ANIMSET_OVL(0x05), 0x15, 0x48, 0x0200, 0x02F};

EInit D_us_801811C4 = {ANIMSET_OVL(0x02), 0x01, 0x00, 0x0000, 0x005};
EInit g_EInitElevator = {ANIMSET_OVL(0x02), 0x03, 0x00, 0x0000, 0x005};
EInit g_EInitEnvironment = {ANIMSET_OVL(0x01), 0x00, 0x00, 0x0000, 0x005};
EInit D_us_801811E8 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x005};
EInit D_us_801811F4 = {ANIMSET_OVL(0x01), 0x13, 0x00, 0x0000, 0x000};

// Discus Lord
EInit g_EInitDiscusLord = {ANIMSET_OVL(0x04), 0x01, 0x49, 0x0224, 0x04D};
EInit g_EInitDiscus = {ANIMSET_OVL(0x04), 0x10, 0x49, 0x0224, 0x04E};

// Hellfire Beast
EInit g_EInitHellfireBeast = {ANIMSET_OVL(0x04), 0x19, 0x49, 0x0224, 0x047};
EInit g_EInitHellfireBeastPunchHitbox = {
    ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x04A};
EInit g_EInitHellfireBeastFlamePillar = {
    ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x048};
EInit g_EInitHellfireBeastThorsHammer = {
    ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x049};

// Lossoth
EInit g_EInitLossoth = {ANIMSET_OVL(0x03), 0x00, 0x50, 0x0216, 0x083};
EInit g_EInitLossothEffects = {ANIMSET_OVL(0x03), 0x00, 0x50, 0x0216, 0x005};
EInit g_EInitLossothAttack = {ANIMSET_OVL(0x03), 0x00, 0x50, 0x0216, 0x084};

// Grave Keeper
EInit g_EInitGraveKeeper = {ANIMSET_OVL(0x09), 0x01, 0x4D, 0x0236, 0x06F};
EInit g_EInitGraveKeeperHitbox = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x070};

// Tombstone
EInit g_EInitTombstone = {ANIMSET_OVL(0x09), 0x15, 0x4D, 0x0236, 0x071};

// Gremlin
EInit g_EInitGremlin = {ANIMSET_OVL(0x0A), 0x00, 0x4F, 0x0238, 0x0E1};
EInit D_us_801812F0 = {ANIMSET_OVL(0x0A), 0x00, 0x4F, 0x0238, 0x005}; // unused
EInit g_EInitGremlinFire = {ANIMSET_OVL(0x0A), 0x00, 0x4F, 0x0238, 0x0E2};

// Large Slime
EInit g_EInitLargeSlime = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x041};

// Slime
EInit g_EInitSlime = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x042};

// Wereskeleton
EInit g_EInitWereskeleton = {ANIMSET_OVL(0x06), 0x01, 0x49, 0x0250, 0x03D};
EInit D_us_80180A88 = {ANIMSET_OVL(0x06), 0x00, 0x49, 0x0250, 0x03E};

// Thornweed
EInit g_EInitThornweed = {ANIMSET_OVL(0x0B), 0x00, 0x50, 0x0252, 0x09D};

// Corpseweed
EInit D_us_801812F4 = {ANIMSET_OVL(0x0B), 0x00, 0x50, 0x0252, 0x09E}; // unused
EInit g_EInitCorpseweed = {ANIMSET_OVL(0x0B), 0x00, 0x50, 0x0252, 0x09F};
EInit g_EInitCorpseweedProjectile = {
    ANIMSET_OVL(0x0B), 0x00, 0x50, 0x0252, 0x0A0};

// Blood Skeleton
EInit g_EInitBloodSkeleton = {ANIMSET_OVL(0x0D), 0x00, 0x4C, 0x0262, 0x046};
