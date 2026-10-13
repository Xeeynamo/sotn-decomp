// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

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
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
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
void EntityCutscene(Entity* self);
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
    EntityDummy, // 0x10
    EntityBackgroundBlock,
    EntityLockCamera,
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
    EntityCutscene,
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

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
#include "../e_init_common.h"
EInit g_EInitStInteractable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitFireWarg1 = {ANIMSET_OVL(6), 0x01, 0x48, PAL_FIRE_WARG, ENEMY_FIRE_WARG};
EInit g_EInitFireWarg2 = {ANIMSET_OVL(6), 0x01, 0x48, PAL_FIRE_WARG, ENEMY_WARG_RIDER};
EInit g_EInitFireWarg3 = {ANIMSET_DRA(0), 0x00, 0x48, PAL_FIRE_WARG, ENEMY_FIRE_WARG_UNK_96};
EInit g_EInitWaterObject = {ANIMSET_OVL(3), 0x01, 0x48, PAL_MERMAN_2, ENEMY_MERMAN_2};
EInit g_EInitWaterSplash = {ANIMSET_OVL(3), 0x00, 0x48, PAL_MERMAN_2, ENEMY_MERMAN_2_WATER_SPLASH};
EInit g_EInitMerman = {ANIMSET_OVL(4), 0x01, 0x4A, PAL_MERMAN, ENEMY_MERMAN};
EInit g_EInitMermanFireball = {ANIMSET_OVL(4), 0x00, 0x4A, PAL_MERMAN, ENEMY_MERMAN_FIREBALL};
EInit g_EInitBoneScimitar = {ANIMSET_OVL(2), 0x01, 0x48, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};
EInit g_EInitScimitarParts = {ANIMSET_OVL(2), 0x01, 0x48, PAL_BONE_SCIMITAR, ENEMY_PARTICLE};
EInit g_EInitBat = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_BAT, ENEMY_BAT};
EInit g_EInitWarg = {ANIMSET_OVL(6), 0x07, 0x48, PAL_WARG, ENEMY_WARG};
EInit g_EInitZombie = {ANIMSET_OVL(7), 0x00, 0x4D, PAL_ZOMBIE, ENEMY_ZOMBIE};
