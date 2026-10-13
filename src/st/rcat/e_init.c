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
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitBreakableWallSegment = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};

EInit g_EInitFrozenHalf = {ANIMSET_OVL(3), 0x01, 0x48, PAL_FROZEN_HALF, ENEMY_FROZEN_HALF};
EInit g_EInitFrozenHalfOrbitIcicle = {ANIMSET_OVL(3), 0x18, 0x48, PAL_FROZEN_HALF, ENEMY_FROZEN_HALF_ORBIT_ICICLE};
EInit g_EInitFrozenHalfThrownChunk = {ANIMSET_OVL(3), 0x1E, 0x48, PAL_FROZEN_HALF, ENEMY_FROZEN_HALF_THROWN_CHUNK};
EInit g_EInitFrozenHalfBlizzard = {ANIMSET_OVL(3), 0x17, 0x48, PAL_FROZEN_HALF, ENEMY_INTERACTABLE};
EInit g_EInitFrozenHalfFallingIce = {ANIMSET_OVL(3), 0x1C, 0x48, PAL_FROZEN_HALF, ENEMY_FROZEN_HALF_FALLING_ICE};

EInit g_EInitSalome = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_SALOME, ENEMY_SALOME};
EInit g_EInitSalomeEffects = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_SALOME, ENEMY_INTERACTABLE};
EInit g_EInitSalomeMagicOrb = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_SALOME, ENEMY_SALOME_MAGIC_ORB};
EInit g_EInitSalomeSkull = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_SALOME, ENEMY_SALOME_SKULL};
EInit g_EInitSalomeCat = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_SALOME, ENEMY_SALOME_CAT};

EInit g_EInitBat = {ANIMSET_OVL(9), 0x00, 0x5F, PAL_BAT, ENEMY_BAT};

EInit g_EInitBloodSkeleton = {ANIMSET_OVL(10), 0x00, 0x5D, PAL_BLOOD_SKELETON, ENEMY_BLOOD_SKELETON};

EInit g_EInitSkeleton = {ANIMSET_OVL(11), 0x01, 0x5E, PAL_SKELETON, ENEMY_SKELETON};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(11), 0x00, 0x5E, PAL_SKELETON, ENEMY_PARTICLE};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(11), 0x15, 0x5E, PAL_SKELETON, ENEMY_SKELETON_BONE};
// clang-format on
