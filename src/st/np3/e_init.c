// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

void EntityBreakable(Entity* self);
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
void EntityUnkId16(Entity* self);
void EntityBackgroundLightning(Entity* self);
void EntityTransparentWater(Entity* self);
void EntityShuttingWindow(Entity* self);
void EntityCastleDoor(Entity* self);
void EntityBackgroundBushes(Entity* self);
void EntityBackgroundTrees(Entity* self);
void EntityCavernDoorLever(Entity* self);
void EntityCavernDoorPlatform(Entity* self);
void EntityCavernDoor(Entity* self);
void EntityWeightsSwitch(Entity* self);
void EntityPathBlockSmallWeight(Entity* self);
void EntityPathBlockTallWeight(Entity* self);
void EntityTrapDoor(Entity* self);
void EntityMermanRockLeftSide(Entity* self);
void EntityMermanRockRightSide(Entity* self);
void EntityJewelSwordDoor(Entity* self);
void EntityFallingRock2(Entity* self);
void EntityLightningThunder(Entity* self);
void EntityLightningCloud(Entity* self);
void EntityHeartRoomSwitch(Entity* self);
void EntityHeartRoomGoldDoor(Entity* self);
void EntityAlucardWaterEffect(Entity* self);
void EntitySplashWater(Entity* self);
void EntitySurfacingWater(Entity* self);
void EntitySideWaterSplash(Entity* self);
void EntitySmallWaterDrop(Entity* self);
void EntityWaterDrop(Entity* self);
void EntityMerman2(Entity* self);
void EntityMermanWaterSplash(Entity* self);
void EntityMediumWaterSplash(Entity* self);
void EntityHighWaterSplash(Entity* self);
void EntityMermanFireSpit(Entity* self);
void EntityDeadMerman(Entity* self);
void EntityMerman2JumpAir(Entity* self);
void EntityMerman(Entity* self);
void EntityMermanFireball(Entity* self);
void EntityMermanJumpAir(Entity* self);
void EntityMermanExplosion(Entity* self);
void EntityMermanSpawner(Entity* self);
void EntityBoneScimitar(Entity* self);
void EntityBoneScimitarParts(Entity* self);
void EntityBat(Entity* self);
void EntityTilemapShufflerUnused(Entity* self);
void EntityZombie(Entity* self);
void EntityZombieSpawner(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityBloodyZombie(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void EntityStairwayPiece(Entity* self);
void EntityFallingRock(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void EntitySlogra(Entity* self);
void EntitySlograSpear(Entity* self);
void EntitySlograSpearProjectile(Entity* self);
void EntityGaibon(Entity* self);
void EntityGaibonLeg(Entity* self);
void EntitySmallGaibonProjectile(Entity* self);
void EntityLargeGaibonProjectile(Entity* self);
void EntityHammer(Entity* self);
void EntityGurkhaBodyParts(Entity* self);
void EntityHammerWeapon(Entity* self);
void EntityGurkha(Entity* self);
void EntityGurkhaSword(Entity* self);
void EntityBlade(Entity* self);
void EntityBladeSword(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
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
    EntityDummy, // 0x10
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityUnkId16,
    EntityBackgroundLightning,
    EntityTransparentWater,
    EntityShuttingWindow,
    EntityCastleDoor,
    EntityBackgroundBushes,
    EntityBackgroundTrees,
    EntityCavernDoorLever,
    EntityCavernDoorPlatform,
    EntityCavernDoor,
    EntityWeightsSwitch, // 0x20
    EntityPathBlockSmallWeight,
    EntityPathBlockTallWeight,
    EntityTrapDoor,
    EntityMermanRockLeftSide,
    EntityMermanRockRightSide,
    EntityJewelSwordDoor,
    EntityFallingRock2,
    EntityLightningThunder,
    EntityLightningCloud,
    EntityHeartRoomSwitch,
    EntityHeartRoomGoldDoor,
    EntityAlucardWaterEffect,
    EntitySplashWater,
    EntitySurfacingWater,
    EntitySideWaterSplash,
    EntitySmallWaterDrop, // 0x30
    EntityWaterDrop,
    EntityMerman2,
    EntityMermanWaterSplash,
    EntityMediumWaterSplash,
    EntityHighWaterSplash,
    EntityMermanFireSpit,
    EntityDeadMerman,
    EntityMerman2JumpAir,
    EntityMerman,
    EntityMermanFireball,
    EntityMermanJumpAir,
    EntityMermanExplosion,
    EntityMermanSpawner,
    EntityBoneScimitar,
    EntityBoneScimitarParts,
    EntityBat, // 0x40
    EntityTilemapShufflerUnused,
    EntityZombie,
    EntityZombieSpawner,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityBloodyZombie,
    EntityBloodDrips,
    EntityBloodSplatter,
    EntityStairwayPiece,
    EntityFallingRock,
    EntityExplosionPuffOpaque,
    EntitySlogra,
    EntitySlograSpear,
    EntitySlograSpearProjectile, // 0x50
    EntityGaibon,
    EntityGaibonLeg,
    EntitySmallGaibonProjectile,
    EntityLargeGaibonProjectile,
    EntityHammer,
    EntityGurkhaBodyParts,
    EntityHammerWeapon,
    EntityGurkha,
    EntityGurkhaSword,
    EntityBlade,
    EntityBladeSword,
};

EInit OVL_EXPORT(
    EInitBreakable) = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitStInteractable = {ANIMSET_OVL(0x01), 0x00, 0x00, 0x000, 0x005};
EInit g_EInitWaterObject = {ANIMSET_OVL(0x03), 0x01, 0x48, 0x28C, 0x01D};
EInit g_EInitWaterSplash = {ANIMSET_OVL(0x03), 0x00, 0x48, 0x28C, 0x01E};
EInit g_EInitMerman = {ANIMSET_OVL(0x04), 0x01, 0x4A, 0x2B2, 0x01B};
EInit g_EInitMermanFireball = {ANIMSET_OVL(0x04), 0x00, 0x4A, 0x2B2, 0x01C};
EInit g_EInitBoneScimitar = {ANIMSET_OVL(0x02), 0x01, 0x48, 0x2C5, 0x069};
EInit g_EInitScimitarParts = {ANIMSET_OVL(0x02), 0x01, 0x48, 0x2C5, 0x002};
EInit g_EInitBat = {ANIMSET_OVL(0x05), 0x00, 0x4C, 0x2C8, 0x040};
EInit g_EInitZombie = {ANIMSET_OVL(0x07), 0x00, 0x4D, 0x2D3, 0x06E};
EInit g_EInitOwlKnight = {ANIMSET_OVL(0x08), 0x10, 0x49, 0x2CB, 0x014};
EInit g_EInitOwlKnightSword = {ANIMSET_OVL(0x08), 0x00, 0x49, 0x2CB, 0x015};
EInit g_EInitOwl = {ANIMSET_OVL(0x08), 0x01, 0x49, 0x2CB, 0x016};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(0x09), 0x01, 0x4A, 0x2D6, 0x00D};
EInit g_EInitSlograNP3 = {ANIMSET_OVL(0x0A), 0x00, 0x48, 0x2D9, 0x0F3};
EInit g_EInitSlograSpearNP3 = {ANIMSET_OVL(0x0A), 0x00, 0x48, 0x2D9, 0x0F4};
EInit g_EInitSlograProjectileNP3 = {
    ANIMSET_OVL(0x0A), 0x00, 0x48, 0x2D9, 0x0F5};
EInit g_EInitGaibonNP3 = {ANIMSET_OVL(0x0B), 0x00, 0x4C, 0x2E2, 0x0FE};
EInit g_EInitGaibonProjectileNP3 = {
    ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x0FF};
EInit g_EInitGaibonLargeProjectileNP3 = {
    ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x100};
EInit g_EInitGurkhaType0 = {ANIMSET_OVL(0x0C), 0x02, 0x4C, 0x2F0, 0x0BA};
EInit g_EInitGurkhaHammer = {ANIMSET_OVL(0x0C), 0x12, 0x4C, 0x2F0, 0x0BB};
EInit g_EInitGurkhaType1 = {ANIMSET_OVL(0x0C), 0x02, 0x4C, 0x2ED, 0x0BC};
EInit g_EInitGurkhaSword = {ANIMSET_OVL(0x0C), 0x14, 0x4C, 0x2ED, 0x0BD};
EInit g_EInitGurkhaType2 = {ANIMSET_OVL(0x0C), 0x02, 0x4C, 0x2EA, 0x0BE};
EInit g_EInitGurkhaBlade = {ANIMSET_OVL(0x0C), 0x13, 0x4C, 0x2EA, 0x0BF};
