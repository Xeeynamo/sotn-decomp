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
void func_801CD540(Entity* self);
void func_801CD620(Entity* self);
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
    func_801CD540,
    func_801CD620,
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

EInit OVL_EXPORT(EInitBreakable) = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000};
u16 g_EInitObtainable[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_EInitParticle[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EInitSpawner[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0004};
u16 g_EInitInteractable[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0005};
u16 g_EInitUnkId13[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EInitLockCamera[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_EInitCommon[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_EInitDamageNum[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_EInitStInteractable[] = {0x8001, 0x0000, 0x0000, 0x0000, 0x0005};
u16 g_EInitWaterObject[] = {0x8003, 0x0001, 0x0048, 0x028C, 0x001D};
u16 g_EInitWaterSplash[] = {0x8003, 0x0000, 0x0048, 0x028C, 0x001E};
u16 g_EInitMerman[] = {0x8004, 0x0001, 0x004A, 0x02B2, 0x001B};
u16 g_EInitMermanFireball[] = {0x8004, 0x0000, 0x004A, 0x02B2, 0x001C};
u16 g_EInitBoneScimitar[] = {0x8002, 0x0001, 0x0048, 0x02C5, 0x0069};
u16 g_EInitScimitarParts[] = {0x8002, 0x0001, 0x0048, 0x02C5, 0x0002};
u16 g_EInitBat[] = {0x8005, 0x0000, 0x004C, 0x02C8, 0x0040};
u16 g_EInitZombie[] = {0x8007, 0x0000, 0x004D, 0x02D3, 0x006E};
u16 D_80180B14[] = {0x8008, 0x0010, 0x0049, 0x02CB, 0x0014};
u16 D_80180B20[] = {0x8008, 0x0000, 0x0049, 0x02CB, 0x0015};
u16 g_EInitOwl[] = {0x8008, 0x0001, 0x0049, 0x02CB, 0x0016};
u16 g_EInitBloodyZombie[] = {0x8009, 0x0001, 0x004A, 0x02D6, 0x000D};
u16 g_EInitSlograNP3[] = {0x800A, 0x0000, 0x0048, 0x02D9, 0x00F3};
u16 g_EInitSlograSpearNP3[] = {0x800A, 0x0000, 0x0048, 0x02D9, 0x00F4};
u16 g_EInitSlograProjectileNP3[] = {0x800A, 0x0000, 0x0048, 0x02D9, 0x00F5};
u16 g_EInitGaibonNP3[] = {0x800B, 0x0000, 0x004C, 0x02E2, 0x00FE};
u16 g_EInitGaibonProjectileNP3[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x00FF};
u16 g_EInitGaibonLargeProjectileNP3[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0100};
u16 g_EInitGurkhaType0[] = {0x800C, 0x0002, 0x004C, 0x02F0, 0x00BA};
u16 g_EInitGurkhaHammer[] = {0x800C, 0x0012, 0x004C, 0x02F0, 0x00BB};
u16 g_EInitGurkhaType1[] = {0x800C, 0x0002, 0x004C, 0x02ED, 0x00BC};
u16 g_EInitGurkhaSword[] = {0x800C, 0x0014, 0x004C, 0x02ED, 0x00BD};
u16 g_EInitGurkhaType2[] = {0x800C, 0x0002, 0x004C, 0x02EA, 0x00BE};
u16 g_EInitGurkhaBlade[] = {0x800C, 0x0013, 0x004C, 0x02EA, 0x00BF};
