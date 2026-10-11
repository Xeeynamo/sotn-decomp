// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

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
void EntityGurkhaWeapon(Entity* self);
void EntityBlade(Entity* self);
void EntityBladeWeapon(Entity* self);

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
    EntityGurkhaWeapon,
    EntityBlade,
    EntityBladeWeapon,
};

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
EInit g_EInitStInteractable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitWaterObject = {ANIMSET_OVL(3), 0x01, 0x48, PAL_MERMAN_2, ENEMY_MERMAN_2};
EInit g_EInitWaterSplash = {ANIMSET_OVL(3), 0x00, 0x48, PAL_MERMAN_2, ENEMY_MERMAN_2_WATER_SPLASH};
EInit g_EInitMerman = {ANIMSET_OVL(4), 0x01, 0x4A, PAL_MERMAN, ENEMY_MERMAN};
EInit g_EInitMermanFireball = {ANIMSET_OVL(4), 0x00, 0x4A, PAL_MERMAN, ENEMY_MERMAN_FIREBALL};
EInit g_EInitBoneScimitar = {ANIMSET_OVL(2), 0x01, 0x48, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};
EInit g_EInitScimitarParts = {ANIMSET_OVL(2), 0x01, 0x48, PAL_BONE_SCIMITAR, ENEMY_PARTICLE};
EInit g_EInitBat = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_BAT, ENEMY_BAT};
EInit g_EInitZombie = {ANIMSET_OVL(7), 0x00, 0x4D, PAL_ZOMBIE, ENEMY_ZOMBIE};
EInit g_EInitOwlKnight = {ANIMSET_OVL(8), 0x10, 0x49, PAL_OWL_KNIGHT_OWL, ENEMY_OWL_KNIGHT};
EInit g_EInitOwlKnightSword = {ANIMSET_OVL(8), 0x00, 0x49, PAL_OWL_KNIGHT_OWL, ENEMY_OWL_KNIGHT_SWORD};
EInit g_EInitOwl = {ANIMSET_OVL(8), 0x01, 0x49, PAL_OWL_KNIGHT_OWL, ENEMY_OWL};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(9), 0x01, 0x4A, PAL_BLOODY_ZOMBIE, ENEMY_BLOODY_ZOMBIE};
EInit g_EInitSlograNP3 = {ANIMSET_OVL(10), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA};
EInit g_EInitSlograSpearNP3 = {ANIMSET_OVL(10), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA_SPEAR};
EInit g_EInitSlograProjectileNP3 = {ANIMSET_OVL(10), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA_PROJECTILE};
EInit g_EInitGaibonNP3 = {ANIMSET_OVL(11), 0x00, 0x4C, PAL_GAIBON, ENEMY_GAIBON};
EInit g_EInitGaibonProjectileNP3 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GAIBON_PROJECTILE};
EInit g_EInitGaibonLargeProjectile = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GAIBON_LARGE_PROJECTILE};
EInit g_EInitHammer = {ANIMSET_OVL(12), 0x02, 0x4C, PAL_HAMMER, ENEMY_HAMMER};
EInit g_EInitHammerWeapon = {ANIMSET_OVL(12), 0x12, 0x4C, PAL_HAMMER, ENEMY_HAMMER_WEAPON};
EInit g_EInitGurkha = {ANIMSET_OVL(12), 0x02, 0x4C, PAL_GURKHA, ENEMY_GURKHA};
EInit g_EInitGurkhaWeapon = {ANIMSET_OVL(12), 0x14, 0x4C, PAL_GURKHA, ENEMY_GURKHA_WEAPON};
EInit g_EInitBlade = {ANIMSET_OVL(12), 0x02, 0x4C, PAL_BLADE, ENEMY_BLADE};
EInit g_EInitBladeWeapon = {ANIMSET_OVL(12), 0x13, 0x4C, PAL_BLADE, ENEMY_BLADE_WEAPON};
