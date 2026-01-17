// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

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
void EntityLava(Entity* self);
void EntityCavernBackgroundLossoth(Entity* self);
void EntityCavernBackgroundDiscusLord(Entity* self);
void EntityLavaEmbers(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikeRoomDarkness(Entity* self);
void EntitySpikesDamage(Entity* self);
void func_us_801B1F1C(Entity* self);
void func_us_801B87E8_from_cat(Entity* self);
void func_us_801BACF4_from_cat(Entity* self);
void func_us_801BEFD8(Entity* self);
void func_us_801BFF94(Entity* self);
void func_us_801C0118(Entity* self);
void func_us_801C02C4(Entity* self);
void func_us_801C0718(Entity* self);
void func_us_801C0844(Entity* self);
void func_us_801C0990(Entity* self);
void func_us_801C1194(Entity* self);
void func_us_801C13B4(Entity* self);
void func_us_801C148C(Entity* self);
void func_us_801C1804(Entity* self);
void func_us_801B3248(Entity* self);
void EntitySecretWall(Entity* self);
void EntityBreakableWallSegment(Entity* self);
void EntityBreakableWallParticles(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntitySkeleton(Entity* self);
void EntitySkeletonThrownBone(Entity* self);
void EntitySkeletonPieces(Entity* self);
void EntityBloodSkeleton(Entity* self);
void EntityBat(Entity* self);

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
    EntityLava,
    EntityCavernBackgroundLossoth,
    EntityCavernBackgroundDiscusLord,
    EntityLavaEmbers,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikeRoomDarkness,
    EntitySpikesDamage,
    func_us_801B1F1C,
    func_us_801B87E8_from_cat,
    func_us_801BACF4_from_cat,
    func_us_801BEFD8,
    func_us_801BFF94,
    func_us_801C0118,
    func_us_801C02C4,
    func_us_801C0718,
    func_us_801C0844,
    func_us_801C0990,
    func_us_801C1194,
    func_us_801C13B4,
    func_us_801C148C,
    func_us_801C1804,
    func_us_801B3248,
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
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit D_us_80181018 = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit D_us_80181024 = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitFrozenHalf = {ANIMSET_OVL(3), 1, 72, 512, 0x0D9};
EInit D_us_8018103C = {ANIMSET_OVL(3), 24, 72, 512, 0x0DA};
EInit D_us_80181048 = {ANIMSET_OVL(3), 30, 72, 512, 0x0DB};
EInit D_us_80181054 = {ANIMSET_OVL(3), 23, 72, 512, 0x005};
EInit D_us_80181060 = {ANIMSET_OVL(3), 28, 72, 512, 0x0DC};
EInit g_EInitSalome = {ANIMSET_OVL(4), 0, 76, 518, 0x0E5};
EInit D_us_80181078 = {ANIMSET_OVL(4), 0, 76, 518, 0x005};
EInit D_us_80181084 = {ANIMSET_OVL(4), 0, 76, 518, 0x0E6};
EInit D_us_80181090 = {ANIMSET_OVL(4), 0, 76, 518, 0x0E7};
EInit D_us_8018109C = {ANIMSET_OVL(4), 0, 76, 518, 0x0E8};
EInit g_EInitBat = {ANIMSET_OVL(9), 0, 95, 576, 0x040};
EInit g_EInitBloodSkeleton = {ANIMSET_OVL(10), 0, 93, 592, 0x046};
EInit g_EInitSkeleton = {ANIMSET_OVL(11), 1, 94, 608, 0x04B};
EInit D_us_801810CC = {ANIMSET_OVL(11), 0, 94, 608, 0x002};
EInit D_us_801810D8 = {ANIMSET_OVL(11), 21, 94, 608, 0x04C};
// clang-format on
