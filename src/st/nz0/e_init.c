// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

void EntityBreakableNZ0(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityPersistentItemDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityPurpleBrickScrollingBackground(Entity*);
void EntityLeftSecretRoomWall(Entity*);
void EntityBottomSecretRoomFloor(Entity*);
void BoxPuzzleFloorButton(Entity*);
void BoxPuzzleSpikes(Entity*);
void EntityMovableBox(Entity*);
void EntityCannonLever(Entity*);
void EntityCannon(Entity*);
void EntityCannonShot(Entity*);
void EntityCannonWall(Entity*);
void EntityBloodSkeleElevButton(Entity*);
void EntityElevator2(Entity*);
void EntitySecretWallDebris(Entity*);
void EntityRedEyeBust(Entity*);
void EntityFloorButton(Entity*);
void EntityFloorSpikes(Entity*);
void EntityBloodSkeleton(Entity*);
void EntityBoneScimitar(Entity*);
void EntityBoneScimitarParts(Entity*);
void EntityAxeKnight(Entity*);
void EntityAxeKnightThrowingAxe(Entity*);
void EntityBloodyZombie(Entity*);
void EntityBloodDrips(Entity*);
void EntityBloodSplatter(Entity*);
void EntitySkeleton(Entity*);
void EntitySkeletonThrownBone(Entity*);
void EntitySkeletonPieces(Entity*);
void EntitySpittleBone(Entity*);
void EntityRotateSpittlebone(Entity*);
void EntitySpittleBoneSpit(Entity*);
void EntityTableWithGlobe(Entity*);
void EntityLifeMaxTank(Entity*);
void EntityBlueFlameTable(Entity*);
void EntityRelicContainer(Entity*);
void EntityExplosionPuffOpaque(Entity*);
void EntitySubWeaponContainer(Entity*);
void EntitySubWpnContGlass(Entity*);
void EntityFallingLiquid(Entity*);
void EntityBubbles(Entity*);
void EntitySubwpnInContainer(Entity*);
void EntityBossFightManager(Entity*);
void EntityBossRoomBlock(Entity*);
void EntitySlogra(Entity*);
void EntitySlograSpear(Entity*);
void EntitySlograSpearProjectile(Entity*);
void EntityGaibon(Entity*);
void EntityGaibonLeg(Entity*);
void EntitySmallGaibonProjectile(Entity*);
void EntityLargeGaibonProjectile(Entity*);
void EntityElevator(Entity*);
void func_801B6DE4(Entity*);
void EntityLifeUpSpawn(Entity*);
void EntitySealedDoor(Entity*);
void EntityCutscene(Entity*);
void EntityMariaNZ0(Entity*);
void func_801B8E0C(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakableNZ0,
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
    EntityPurpleBrickScrollingBackground,
    EntityLeftSecretRoomWall,
    EntityBottomSecretRoomFloor,
    BoxPuzzleFloorButton,
    BoxPuzzleSpikes,
    EntityMovableBox,
    EntityCannonLever,
    EntityCannon,
    EntityCannonShot,
    EntityCannonWall,
    EntityBloodSkeleElevButton,
    EntityElevator2,
    EntitySecretWallDebris,
    EntityRedEyeBust,
    EntityFloorButton,
    EntityFloorSpikes,
    EntityBloodSkeleton,
    EntityBoneScimitar,
    EntityBoneScimitarParts,
    EntityAxeKnight,
    EntityAxeKnightThrowingAxe,
    EntityBloodyZombie,
    EntityBloodDrips,
    EntityBloodSplatter,
    EntitySkeleton,
    EntitySkeletonThrownBone,
    EntitySkeletonPieces,
    EntitySpittleBone,
    EntityRotateSpittlebone,
    EntitySpittleBoneSpit,
    EntityTableWithGlobe,
    EntityLifeMaxTank,
    EntityBlueFlameTable,
    EntityRelicContainer,
    EntityExplosionPuffOpaque,
    EntitySubWeaponContainer,
    EntitySubWpnContGlass,
    EntityFallingLiquid,
    EntityBubbles,
    EntitySubwpnInContainer,
    EntityBossFightManager,
    EntityBossRoomBlock,
    EntitySlogra,
    EntitySlograSpear,
    EntitySlograSpearProjectile,
    EntityGaibon,
    EntityGaibonLeg,
    EntitySmallGaibonProjectile,
    EntityLargeGaibonProjectile,
    EntityElevator,
    func_801B6DE4,
    EntityLifeUpSpawn,
    EntitySealedDoor,
    EntityCutscene,
    EntityMariaNZ0,
    func_801B8E0C,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
#include "../e_init_common.h"
EInit g_EInitEnemy3 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitBloodSkeleton = {ANIMSET_OVL(2), 0x00, 0x4C, PAL_BLOOD_SKELETON, ENEMY_BLOOD_SKELETON};
EInit g_EInitBoneScimitar = {ANIMSET_OVL(3), 0x01, 0x4D, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};
EInit g_EInitScimitarParts = {ANIMSET_OVL(3), 0x00, 0x4D, PAL_BONE_SCIMITAR, ENEMY_PARTICLE};
EInit g_EInitAxeKnight = {ANIMSET_OVL(4), 0x01, 0x48, PAL_AXE_KNIGHT, ENEMY_BLUE_AXE_KNIGHT};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(4), 0x2F, 0x48, PAL_AXE_KNIGHT_AXE, ENEMY_BLUE_AXE_KNIGHT_AXE};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(5), 0x01, 0x4A, PAL_BLOODY_ZOMBIE, ENEMY_BLOODY_ZOMBIE};
EInit g_EInitSkeleton = {ANIMSET_OVL(6), 0x01, 0x4E, PAL_SKELETON, ENEMY_SKELETON};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(6), 0x00, 0x4E, PAL_SKELETON, ENEMY_PARTICLE};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(6), 0x15, 0x4E, PAL_SKELETON, ENEMY_SKELETON_BONE};
EInit g_EInitSpittleBone = {ANIMSET_OVL(7), 0x34, 0x50, PAL_SPITTLE_BONE, ENEMY_SPITTLE_BONE};
EInit g_EInitSpittleBoneSpit = {ANIMSET_OVL(7), 0x40, 0x50, PAL_SPITTLE_BONE, ENEMY_SPITTLE_BONE_SPIT};
EInit g_EInitTableWithGlobe = {ANIMSET_OVL(8), 0x00, 0x4B, PAL_BREAKABLE, ENEMY_INTERACTABLE};
EInit g_EInitLifeMaxTank = {ANIMSET_OVL(9), 0x00, 0x4F, PAL_LIFE_MAX_TANK, ENEMY_INTERACTABLE};
EInit g_EInitPrizeContainer = {ANIMSET_OVL(10), 0x00, 0x53, PAL_PRIZE_CONTAINER, ENEMY_INTERACTABLE};
EInit g_EInitSubwpnCloche = {ANIMSET_OVL(12), 0x00, 0x4C, PAL_SUBWPN_CLOCHE, ENEMY_INTERACTABLE};
EInit g_EInitSubwpnClochePieces = {ANIMSET_OVL(12), 0x00, 0x4C, PAL_SUBWPN_CLOCHE, ENEMY_PARTICLE};
EInit g_EInitBossDoor = {ANIMSET_OVL(1), 0x08, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitSlogra = {ANIMSET_OVL(13), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA};
EInit g_EInitSlograSpear = {ANIMSET_OVL(13), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA_SPEAR};
EInit g_EInitSlograProjectile = {ANIMSET_OVL(13), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA_PROJECTILE};
EInit g_EInitGaibon = {ANIMSET_OVL(14), 0x00, 0x4C, PAL_GAIBON, ENEMY_GAIBON};
EInit g_EInitGaibonProjectile = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GAIBON_PROJECTILE};
EInit g_EInitGaibonLargeProjectile = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GAIBON_LARGE_PROJECTILE};
