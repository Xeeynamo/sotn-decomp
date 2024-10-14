// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

void EntityBreakableNZ0(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void func_801B0958(Entity*);
void func_801B0AA4(Entity*);
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
void func_801C7654(Entity*);
void func_801C77B8(Entity*);
void func_801C7884(Entity*);
void EntityBossFightManager(Entity*);
void EntityBossRoomBlock(Entity*);
void EntitySlogra(Entity*);
void EntitySlograSpear(Entity*);
void EntitySlograSpearProjectile(Entity*);
void EntityGaibon(Entity*);
void func_801B69E8(Entity*);
void EntitySmallGaibonProjectile(Entity*);
void EntityLargeGaibonProjectile(Entity*);
void EntityElevator(Entity*);
void func_801B6DE4(Entity*);
void EntityLifeUpSpawn(Entity*);
void EntityMagicallySealedDoor(Entity*);
void NZ0_EntityCutscene(Entity*);
void EntityMariaNZ0(Entity*);
void func_801B8E0C(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakableNZ0,
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
    func_801B0958,
    func_801B0AA4,
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
    func_801C7654,
    func_801C77B8,
    func_801C7884,
    EntityBossFightManager,
    EntityBossRoomBlock,
    EntitySlogra,
    EntitySlograSpear,
    EntitySlograSpearProjectile,
    EntityGaibon,
    func_801B69E8,
    EntitySmallGaibonProjectile,
    EntityLargeGaibonProjectile,
    EntityElevator,
    func_801B6DE4,
    EntityLifeUpSpawn,
    EntityMagicallySealedDoor,
    OVL_EXPORT(EntityCutscene),
    EntityMariaNZ0,
    func_801B8E0C,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitBloodSkeleton = {0x8002, 0x0000, 0x004C, 0x0200, 0x0046};
EInit g_EInitBoneScimitar = {0x8003, 0x0001, 0x004D, 0x0204, 0x0069};
EInit g_EInitScimitarParts = {0x8003, 0x0000, 0x004D, 0x0204, 0x0002};
EInit g_EInitAxeKnight = {0x8004, 0x0001, 0x0048, 0x0207, 0x00F6};
EInit g_EInitAxeKnightAxe = {0x8004, 0x002F, 0x0048, 0x0205, 0x018F};
EInit g_EInitBloodyZombie = {0x8005, 0x0001, 0x004A, 0x0209, 0x000D};
EInit g_EInitSkeleton = {0x8006, 0x0001, 0x004E, 0x020C, 0x004B};
EInit g_EInitSkeletonPieces = {0x8006, 0x0000, 0x004E, 0x020C, 0x0002};
EInit g_EInitSkeletonBone = {0x8006, 0x0015, 0x004E, 0x020C, 0x004C};
EInit g_EInitSpittleBone = {0x8007, 0x0034, 0x0050, 0x020D, 0x0051};
EInit g_EInitSpittleBoneSpit = {0x8007, 0x0040, 0x0050, 0x020D, 0x0052};
EInit g_EInitTableWithGlobe = {0x8008, 0x0000, 0x004B, 0x0219, 0x0005};
EInit g_EInitLifeMaxTank = {0x8009, 0x0000, 0x004F, 0x0211, 0x0005};
EInit g_EInitPrizeContainer = {0x800A, 0x0000, 0x0053, 0x0215, 0x0005};
EInit g_EInitSubwpnCloche = {0x800C, 0x0000, 0x004C, 0x021D, 0x0005};
EInit g_EInitSubwpnClochePieces = {0x800C, 0x0000, 0x004C, 0x021D, 0x0002};
EInit g_EInitBossDoor = {0x8001, 0x0008, 0x0000, 0x0000, 0x0005};
EInit g_EInitSlogra = {0x800D, 0x0000, 0x0048, 0x0227, 0x00F3};
EInit g_EInitSlograSpear = {0x800D, 0x0000, 0x0048, 0x0227, 0x00F4};
EInit g_EInitSlograProjectile = {0x800D, 0x0000, 0x0048, 0x0227, 0x00F5};
EInit g_EInitGaibon = {0x800E, 0x0000, 0x004C, 0x022A, 0x00FE};
EInit g_EInitGaibonProjectile = {0x0000, 0x0000, 0x0000, 0x0000, 0x00FF};
EInit g_EInitGaibonLargeProjectile = {0x0000, 0x0000, 0x0000, 0x0000, 0x0100};

static u32 D_80180D54[] = {0x00000B10};
static u32 D_80180D58[] = {0x0D080C08, 0x0F080E08, 0x00001008};

ObjInit D_80180D64[] = {
    {0x8001, 0x0069, 0x0000, 0x0000, 0x00, 0x00, 0x00000000, D_80180D54},
    {0x8001, 0x0069, 0x0000, 0x0000, 0x00, 0x30, 0x00000000, D_80180D58},
};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    0x0761, 0x0769, 0x0771, 0x0779, 0x0130, 0x0138, 0x01C0, 0x01C5,
    0x0763, 0x076B, 0x0773, 0x077B, 0x0175, 0x017A, 0x0200, 0x0203,
    0x0762, 0x076A, 0x0772, 0x077A, 0x0000, 0x0000, 0x0000, 0x0000,
};
