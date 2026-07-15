// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

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
void EntityHeartDrop(Entity* self);
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
void EntityCavernBackgroundIce(Entity* self);
void EntityCavernBackgroundIceBridge(Entity* self);
void EntitySnowflakes(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikeRoomDarkness(Entity* self);
void EntitySpikesDamage(Entity* self);
void func_us_801B1F1C(Entity* self);
void func_us_801B87E8(Entity* self);
void func_us_801BACF4(Entity* self);
void EntityFrozenHalf(Entity* self);
void EntityFrozenHalfOrbitIcicle(Entity* self);
void EntityFrozenHalfThrownChunk(Entity* self);
void EntityFrozenHalfBlizzard(Entity* self);
void EntityFrozenHalfFallingIce(Entity* self);
void EntityFrozenHalfFrostMist(Entity* self);
void EntitySalome(Entity* self);
void EntitySalomeEffects(Entity* self);
void EntitySalomeMagicOrb(Entity* self);
void EntitySalomeSkull(Entity* self);
void EntitySalomeCat(Entity* self);
void EntitySecretWallRight(Entity* self);
void EntitySecretWall(Entity* self);
void EntityBreakableWallSegment(Entity* self);
void EntityBreakableWallParticles(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntitySkeleton(Entity* self);
void EntitySkeletonThrownBone(Entity* self);
void EntitySkeletonPieces(Entity* self);
void EntityBloodSkeleton(Entity* self);
void EntityBat(Entity* self);

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
    EntityHeartDrop,
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
    EntityCavernBackgroundIce,
    EntityCavernBackgroundIceBridge,
    EntitySnowflakes,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikeRoomDarkness,
    EntitySpikesDamage,
    func_us_801B1F1C,
    func_us_801B87E8,
    func_us_801BACF4,
    EntityFrozenHalf,
    EntityFrozenHalfOrbitIcicle,
    EntityFrozenHalfThrownChunk,
    EntityFrozenHalfBlizzard,
    EntityFrozenHalfFallingIce,
    EntityFrozenHalfFrostMist,
    EntitySalome,
    EntitySalomeEffects,
    EntitySalomeMagicOrb,
    EntitySalomeSkull,
    EntitySalomeCat,
    EntitySecretWallRight,
    EntitySecretWall,
    EntityBreakableWallSegment,
    EntityBreakableWallParticles,
    EntityBreakableWallDebris,
    EntitySkeleton,
    EntitySkeletonThrownBone,
    EntitySkeletonPieces,
    EntityBloodSkeleton,
    EntityBat,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0x000, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0x000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0x000, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0x000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0x000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0x000, 0x003};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0, 0, 0x000, 0x005};
EInit g_EInitBreakableWallSegment = {ANIMSET_DRA(0), 0, 0, 0x000, 0x005};

EInit g_EInitFrozenHalf = {ANIMSET_OVL(3), 1, 72, 0x200, 0x0D9};
EInit g_EInitFrozenHalfOrbitIcicle = {ANIMSET_OVL(3), 24, 72, 0x200, 0x0DA};
EInit g_EInitFrozenHalfThrownChunk = {ANIMSET_OVL(3), 30, 72, 0x200, 0x0DB};
EInit g_EInitFrozenHalfBlizzard = {ANIMSET_OVL(3), 23, 72, 0x200, 0x005};
EInit g_EInitFrozenHalfFallingIce = {ANIMSET_OVL(3), 28, 72, 0x200, 0x0DC};

EInit g_EInitSalome = {ANIMSET_OVL(4), 0, 76, 0x206, 0x0E5};
EInit g_EInitSalomeEffects = {ANIMSET_OVL(4), 0, 76, 0x206, 0x005};
EInit g_EInitSalomeMagicOrb = {ANIMSET_OVL(4), 0, 76, 0x206, 0x0E6};
EInit g_EInitSalomeSkull = {ANIMSET_OVL(4), 0, 76, 0x206, 0x0E7};
EInit g_EInitSalomeCat = {ANIMSET_OVL(4), 0, 76, 0x206, 0x0E8};

EInit g_EInitBat = {ANIMSET_OVL(9), 0, 95, 0x240, 0x040};

EInit g_EInitBloodSkeleton = {ANIMSET_OVL(10), 0, 93, 0x250, 0x046};

EInit g_EInitSkeleton = {ANIMSET_OVL(11), 1, 94, 0x260, 0x04B};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(11), 0, 94, 0x260, 0x002};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(11), 21, 94, 0x260, 0x04C};
// clang-format on
