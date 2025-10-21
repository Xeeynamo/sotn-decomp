// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

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
void EntityDeathSkySwirl(Entity* self);
void EntityLightningThunder(Entity* self);
void EntityLightningCloud(Entity* self);
void EntityHeartRoomSwitch(Entity* self);
void EntityHeartRoomGoldDoor(Entity* self);
void EntityFireWarg(Entity* self);
void EntityFireWargWaveAttack(Entity* self);
void EntityUnkId2F(Entity* self);
void EntityUnkId30(Entity* self);
void EntityUnkId31(Entity* self);
void EntityExplosion3(Entity* self);
void EntityFireWargDeathBeams(Entity* self);
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
void EntityWarg(Entity* self);
void EntityUnkId4B(Entity* self);
void EntityZombie(Entity* self);
void EntityZombieSpawner(Entity* self);
void EntityPushAlucard(Entity* self);
void EntityForegroundTree(Entity* self);
void EntityFoliageMaker(Entity* self);
void EntityBackgroundPineTrees(Entity* self);
void EntityDistantTreeMaker(Entity* self);
void EntityCastleDoorTransition(Entity* self);
void EntityCastleBridge(Entity* self);
void EntityDistantBackgroundTrees(Entity* self);
void EntityBackgroundCastleWall(Entity* self);
void OVL_EXPORT(EntityCutscene)(Entity* self);
void EntityDeathCutsceneManager(Entity* self);
void EntityDeathStolenItem(Entity* self);
void EntityDeath(Entity* self);
void EntityDeathScythe(Entity* self);
void EntityStairwayPiece(Entity* self);
void EntityFallingRock(Entity* self);
void EntityDeathScytheShadow(Entity* self);
void EntityFlyingOwlAndLeaves(Entity* self);
void EntityFallingLeaf(Entity* self);
void EntityWargExplosionPuffTransparent(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);

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
    EntityDeathSkySwirl,
    EntityLightningThunder,
    EntityLightningCloud,
    EntityHeartRoomSwitch,
    EntityHeartRoomGoldDoor,
    EntityFireWarg,
    EntityFireWargWaveAttack,
    EntityUnkId2F,
    EntityUnkId30, // 0x30
    EntityUnkId31,
    EntityExplosion3,
    EntityFireWargDeathBeams,
    EntityAlucardWaterEffect,
    EntitySplashWater,
    EntitySurfacingWater,
    EntitySideWaterSplash,
    EntitySmallWaterDrop,
    EntityWaterDrop,
    EntityMerman2,
    EntityMermanWaterSplash,
    EntityMediumWaterSplash,
    EntityHighWaterSplash,
    EntityMermanFireSpit,
    EntityDeadMerman,
    EntityMerman2JumpAir, // 0x40
    EntityMerman,
    EntityMermanFireball,
    EntityMermanJumpAir,
    EntityMermanExplosion,
    EntityMermanSpawner,
    EntityBoneScimitar,
    EntityBoneScimitarParts,
    EntityBat,
    EntityTilemapShufflerUnused,
    EntityWarg,
    EntityUnkId4B,
    EntityZombie,
    EntityZombieSpawner,
    EntityPushAlucard,
    EntityForegroundTree,
    EntityFoliageMaker, // 0x50
    EntityBackgroundPineTrees,
    EntityDistantTreeMaker,
    EntityCastleDoorTransition,
    EntityCastleBridge,
    EntityDistantBackgroundTrees,
    EntityBackgroundCastleWall,
    OVL_EXPORT(EntityCutscene),
    EntityDeathCutsceneManager,
    EntityDeathStolenItem,
    EntityDeath,
    EntityDeathScythe,
    EntityStairwayPiece,
    EntityFallingRock,
    EntityDeathScytheShadow,
    EntityFlyingOwlAndLeaves,
    EntityFallingLeaf, // 0x60
    EntityWargExplosionPuffTransparent,
    EntityExplosionPuffOpaque};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitStInteractable = {0x8001, 0, 0x0, 0x0, 5};
EInit g_EInitFireWarg1 = {0x8006, 1, 0x48, 0x2cb, 148};
EInit g_EInitFireWarg2 = {0x8006, 1, 0x48, 0x2cb, 151};
EInit g_EInitFireWarg3 = {0x0, 0, 0x48, 0x2cb, 150};
EInit g_EInitWaterObject = {0x8003, 1, 0x48, 0x28c, 29};
EInit g_EInitWaterSplash = {0x8003, 0, 0x48, 0x28c, 30};
EInit g_EInitMerman = {0x8004, 1, 0x4a, 0x2b2, 27};
EInit g_EInitMermanFireball = {0x8004, 0, 0x4a, 0x2b2, 28};
EInit g_EInitBoneScimitar = {0x8002, 1, 0x48, 0x2c5, 105};
EInit g_EInitScimitarParts = {0x8002, 1, 0x48, 0x2c5, 2};
EInit g_EInitBat = {0x8005, 0, 0x4c, 0x2c8, 64};
EInit g_EInitWarg = {0x8006, 7, 0x48, 0x2d0, 175};
EInit g_EInitZombie = {0x8007, 0, 0x4d, 0x2d3, 110};
