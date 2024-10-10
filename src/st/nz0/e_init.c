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
void EntityMoveableBox(Entity*);
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
void func_801C5D20(Entity*);
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
void EntityWargExplosionPuffOpaque(Entity*);
void EntitySubWeaponContainer(Entity*);
void func_801C7538(Entity*);
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
void EntityMaria(Entity*);
void func_801B8E0C(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
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
    EntityMoveableBox,
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
    func_801C5D20,
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
    EntityWargExplosionPuffOpaque,
    EntitySubWeaponContainer,
    func_801C7538,
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
    EntityMaria,
    func_801B8E0C,
};

u16 g_eBreakableInit[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000};
u16 g_InitializeData0[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_InitializeEntityData0[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_MariaInit[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0004};
u16 g_EInitGeneric[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0005};
u16 g_InitDataEnt13[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0002};
u16 D_80180C10[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_eInitGeneric2[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_eDamageDisplayInit[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
u16 D_80180C34[] = {0x8001, 0x0000, 0x0000, 0x0000, 0x0003};
u16 D_80180C40[] = {0x8002, 0x0000, 0x004C, 0x0200, 0x0046};
u16 g_BoneScimitarInit[] = {0x8003, 0x0001, 0x004D, 0x0204, 0x0069};
u16 g_ScimitarPartsInit[] = {0x8003, 0x0000, 0x004D, 0x0204, 0x0002};
u16 g_EAxeKnightInit[] = {0x8004, 0x0001, 0x0048, 0x0207, 0x00F6};
u16 D_80180C70[] = {0x8004, 0x002F, 0x0048, 0x0205, 0x018F};
u16 g_EBloodyZombieInit[] = {0x8005, 0x0001, 0x004A, 0x0209, 0x000D};
u16 D_80180C88[] = {0x8006, 0x0001, 0x004E, 0x020C, 0x004B};
u16 D_80180C94[] = {0x8006, 0x0000, 0x004E, 0x020C, 0x0002};
u16 D_80180CA0[] = {0x8006, 0x0015, 0x004E, 0x020C, 0x004C};
u16 D_80180CAC[] = {0x8007, 0x0034, 0x0050, 0x020D, 0x0051};
u16 D_80180CB8[] = {0x8007, 0x0040, 0x0050, 0x020D, 0x0052};
u16 D_80180CC4[] = {0x8008, 0x0000, 0x004B, 0x0219, 0x0005};
u16 D_80180CD0[] = {0x8009, 0x0000, 0x004F, 0x0211, 0x0005};
u16 D_80180CDC[] = {0x800A, 0x0000, 0x0053, 0x0215, 0x0005};
u16 D_80180CE8[] = {0x800C, 0x0000, 0x004C, 0x021D, 0x0005};
u16 D_80180CF4[] = {0x800C, 0x0000, 0x004C, 0x021D, 0x0002};
u16 D_80180D00[] = {0x8001, 0x0008, 0x0000, 0x0000, 0x0005};
u16 D_80180D0C[] = {0x800D, 0x0000, 0x0048, 0x0227, 0x00F3};
u16 D_80180D18[] = {0x800D, 0x0000, 0x0048, 0x0227, 0x00F4};
u16 D_80180D24[] = {0x800D, 0x0000, 0x0048, 0x0227, 0x00F5};
u16 D_80180D30[] = {0x800E, 0x0000, 0x004C, 0x022A, 0x00FE};
u16 D_80180D3C[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x00FF};
u16 D_80180D48[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0100};

static u32 D_80180D54[] = {0x00000B10};
static u32 D_80180D58[] = {0x0D080C08, 0x0F080E08, 0x00001008};

ObjInit D_80180D64[] = {
    {0x8001, 0x0069, 0x0000, 0x0000, 0x00, 0x00, 0x00000000, D_80180D54},
    {0x8001, 0x0069, 0x0000, 0x0000, 0x00, 0x30, 0x00000000, D_80180D58},
};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 g_eRedDoorTiles[][8] = {
    0x0761, 0x0769, 0x0771, 0x0779, 0x0130, 0x0138, 0x01C0, 0x01C5,
    0x0763, 0x076B, 0x0773, 0x077B, 0x0175, 0x017A, 0x0200, 0x0203,
    0x0762, 0x076A, 0x0772, 0x077A, 0x0000, 0x0000, 0x0000, 0x0000,
};
