// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

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
void EntityAlucardWaterEffect(Entity* self);
void EntitySplashWater(Entity* self);
void EntitySurfacingWater(Entity* self);
void EntitySideWaterSplash(Entity* self);
void EntitySmallWaterDrop(Entity* self);
void EntityWaterDrop(Entity* self);
void func_us_801C12B0(Entity* self);
void func_us_801C15F8(Entity* self);
void func_us_801C1844(Entity* self);
void EntityBgColumnsParallax(Entity* self);
void func_us_801C1EE4(Entity* self);
void func_us_801C21AC(Entity* self);
void func_us_801C2474(Entity* self);
void func_us_801C2850(Entity* self);
void func_us_801C2B78(Entity* self);
void func_us_801C2E60(Entity* self);
void func_us_801C3160(Entity* self);
void func_us_801C34EC(Entity* self);
void func_us_801C37C8(Entity* self);
void func_us_801C3A04(Entity* self);
void func_us_801C3CC4(Entity* self);
void func_us_801C3FB0(Entity* self);
void func_us_801C4228(Entity* self);
void EntityFerrymanController(Entity* self);
void EntityFerryman(Entity* self);
void EntityBoatElevatorChains(Entity* self);
void EntityBoatElevatorController(Entity* self);
void EntityFerrymanUnused(Entity* self);
void func_us_801C123C(Entity* self);
void EntityWaterBox(Entity* self);
void EntityWaterSpray(Entity* self);
void EntityFloatingIcePlatform(Entity* self);
void func_us_801C5518(Entity* self);
void func_us_801C82B8(Entity* self);
void EntitySpearGuardBlock(Entity* self);
void EntityToad(Entity* self);
void EntityFrog(Entity* self);
void EntityFishhead(Entity* self);
void EntityFishheadSpawner(Entity* self);
void EntityFishheadFireball(Entity* self);
void EntityFishheadParticles(Entity* self);
void EntityFishheadDeathParts(Entity* self);
void EntityFishheadFireBreath(Entity* self);
void EntityBat(Entity* self);
void EntityFrozenShade(Entity* self);
void EntityFrozenShadeCrystal(Entity* self);
void EntityFrozenShadeIcicle(Entity* self);
void EntityFrozenShadeIcicleUnk(Entity* self);
void EntityBreakableCrystalFloor(Entity* self);
void EntitySpearGuard(Entity* self);
void EntityThrownSpear(Entity* self);
void EntityBoneArcher(Entity* self);
void EntityBoneArcherArrow(Entity* self);
void EntityFerrymanGateController(Entity* self);
void EntityCutscene(Entity* self);
void func_us_801C4BD8(Entity* self);
void EntityBreakableWall(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void func_us_801C4D2C(Entity* self);
void func_us_801C5020(Entity* self);
void EntityKillerFish(Entity* self);
void EntitySkeletonApe(Entity* self);
void EntitySkeletonApePunch(Entity* self);
void EntitySkeletonApeBarrel(Entity* self);
void EntityThrownBarrel(Entity* self);
void EntityKillerFishDeathPuff(Entity* self);
void func_us_801C5268(Entity* self);
void func_us_801C542C(Entity* self);
void func_us_801C5628(Entity* self);
void func_us_801C582C(Entity* self);
void func_us_801C8248(Entity* self);
void func_us_801C58A0(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    /* 0x01 */ EntityBreakable,
    /* 0x02 */ EntityExplosion,
    /* 0x03 */ EntityPrizeDrop,
    /* 0x04 */ EntityDamageDisplay,
    /* 0x05 */ EntityRedDoor,
    /* 0x06 */ EntityIntenseExplosion,
    /* 0x07 */ EntitySoulStealOrb,
    /* 0x08 */ EntityRoomForeground,
    /* 0x09 */ EntityStageNamePopup,
    /* 0x0A */ EntityEquipItemDrop,
    /* 0x0B */ EntityRelicOrb,
    /* 0x0C */ EntityPersistentItemDrop,
    /* 0x0D */ EntityEnemyBlood,
    /* 0x0E */ EntityMessageBox,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ EntityDummy,
    /* 0x11 */ EntityBackgroundBlock,
    /* 0x12 */ EntityLockCamera,
    /* 0x13 */ EntityUnkId13,
    /* 0x14 */ EntityExplosionVariants,
    /* 0x15 */ EntityGreyPuff,
    /* 0x16 */ EntityAlucardWaterEffect,
    /* 0x17 */ EntitySplashWater,
    /* 0x18 */ EntitySurfacingWater,
    /* 0x19 */ EntitySideWaterSplash,
    /* 0x1A */ EntitySmallWaterDrop,
    /* 0x1B */ EntityWaterDrop,
    /* 0x1C */ func_us_801C12B0,
    /* 0x1D */ func_us_801C15F8,
    /* 0x1E */ func_us_801C1844,
    /* 0x1F */ EntityBgColumnsParallax,
    /* 0x20 */ func_us_801C1EE4,
    /* 0x21 */ func_us_801C21AC,
    /* 0x22 */ func_us_801C2474,
    /* 0x23 */ func_us_801C2850,
    /* 0x24 */ func_us_801C2B78,
    /* 0x25 */ func_us_801C2E60,
    /* 0x26 */ func_us_801C3160,
    /* 0x27 */ func_us_801C34EC,
    /* 0x28 */ func_us_801C37C8,
    /* 0x29 */ func_us_801C3A04,
    /* 0x2A */ func_us_801C3CC4,
    /* 0x2B */ func_us_801C3FB0,
    /* 0x2C */ func_us_801C4228,
    /* 0x2D */ EntityFerrymanController,
    /* 0x2E */ EntityFerryman,
    /* 0x2F */ EntityBoatElevatorChains,
    /* 0x30 */ EntityBoatElevatorController,
    /* 0x31 */ EntityFerrymanUnused,
    /* 0x32 */ EntityDummy,
    /* 0x33 */ EntityDummy,
    /* 0x34 */ EntityDummy,
    /* 0x35 */ func_us_801C123C,
    /* 0x36 */ EntityWaterBox,
    /* 0x37 */ EntityWaterSpray,
    /* 0x38 */ EntityFloatingIcePlatform,
    /* 0x39 */ func_us_801C5518,
    /* 0x3A */ func_us_801C82B8,
    /* 0x3B */ EntitySpearGuardBlock,
    /* 0x3C */ EntityToad,
    /* 0x3D */ EntityFrog,
    /* 0x3E */ EntityFishhead,
    /* 0x3F */ EntityFishheadSpawner,
    /* 0x40 */ EntityFishheadFireball,
    /* 0x41 */ EntityFishheadParticles,
    /* 0x42 */ EntityFishheadDeathParts,
    /* 0x43 */ EntityFishheadFireBreath,
    /* 0x44 */ EntityBat,
    /* 0x45 */ EntityFrozenShade,
    /* 0x46 */ EntityFrozenShadeCrystal,
    /* 0x47 */ EntityFrozenShadeIcicle,
    /* 0x48 */ EntityFrozenShadeIcicleUnk,
    /* 0x49 */ EntityBreakableCrystalFloor,
    /* 0x4A */ EntitySpearGuard,
    /* 0x4B */ EntityThrownSpear,
    /* 0x4C */ EntityBoneArcher,
    /* 0x4D */ EntityBoneArcherArrow,
    /* 0x4E */ EntityFerrymanGateController,
    /* 0x4F */ EntityCutscene,
    /* 0x50 */ func_us_801C4BD8,
    /* 0x51 */ EntityBreakableWall,
    /* 0x52 */ EntityBreakableWallDebris,
    /* 0x53 */ func_us_801C4D2C,
    /* 0x54 */ func_us_801C5020,
    /* 0x55 */ EntityKillerFish,
    /* 0x56 */ EntitySkeletonApe,
    /* 0x57 */ EntitySkeletonApePunch,
    /* 0x58 */ EntitySkeletonApeBarrel,
    /* 0x59 */ EntityThrownBarrel,
    /* 0x5A */ EntityKillerFishDeathPuff,
    /* 0x5B */ func_us_801C5268,
    /* 0x5C */ func_us_801C542C,
    /* 0x5D */ func_us_801C5628,
    /* 0x5E */ func_us_801C582C,
    /* 0x5F */ func_us_801C8248,
    /* 0x60 */ func_us_801C58A0,
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
EInit D_us_80180BF8 = {ANIMSET_OVL(2), 0x05, 0x48, PAL_SPEAR_GUARD, ENEMY_SPEAR_GUARD};
EInit g_EInitToad = {ANIMSET_OVL(3), 0x01, 0x4B, PAL_TOAD_FROG, ENEMY_TOAD};
EInit g_EInitFrog = {ANIMSET_OVL(3), 0x01, 0x4B, PAL_TOAD_FROG, ENEMY_FROG};
EInit g_EInitFishhead = {ANIMSET_OVL(4), 0x01, 0x4A, PAL_FISHHEAD, ENEMY_FISHHEAD};
EInit g_EInitFishheadSpawner = {ANIMSET_OVL(4), 0x13, 0x4A, PAL_FISHHEAD, ENEMY_INTERACTABLE};
EInit g_EInitFishheadFireball = {ANIMSET_OVL(4), 0x00, 0x4A, PAL_FISHHEAD, ENEMY_FISHHEAD_FIREBALL};
EInit g_EInitFishheadPieces = {ANIMSET_OVL(4), 0x00, 0x4A, PAL_FISHHEAD, ENEMY_PARTICLE};
EInit g_EInitFishheadFireBreath = {ANIMSET_OVL(4), 0x00, 0x4A, PAL_FISHHEAD, ENEMY_FISHHEAD_FIRE_BREATH};
EInit g_EInitBat = {ANIMSET_OVL(6), 0x00, 0x4F, PAL_BAT, ENEMY_BAT};
EInit g_EInitFrozenShade = {ANIMSET_OVL(7), 0x01, 0x4C, PAL_FROZEN_SHADE, ENEMY_FROZEN_SHADE};
EInit g_EInitFrozenShadeCrystal = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_FROZEN_SHADE_CRYSTAL};
EInit g_EInitFrozenShadeIcicle = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_FROZEN_SHADE_ICICLE};
EInit g_EInitSpearGuard = {ANIMSET_OVL(2), 0x05, 0x48, PAL_SPEAR_GUARD, ENEMY_SPEAR_GUARD};
EInit g_EInitThrownSpear = {ANIMSET_OVL(2), 0x05, 0x48, PAL_SPEAR_GUARD, ENEMY_SPEAR_GUARD_THROWN_SPEAR};
EInit g_EInitBoneArcher = {ANIMSET_OVL(8), 0x01, 0x4E, PAL_BONE_ARCHER, ENEMY_BONE_ARCHER};
EInit g_EInitBoneArcherArrow = {ANIMSET_OVL(8), 0x00, 0x4E, PAL_BONE_ARCHER, ENEMY_BONE_ARCHER_ARROW};
EInit D_us_80180CB8 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitSkeletonApe = {ANIMSET_OVL(10), 0x01, 0x4C, PAL_SKELETON_APE, ENEMY_SKELETON_APE};
EInit g_EInitSkeletonApeBarrel = {ANIMSET_OVL(10), 0x28, 0x4C, PAL_SKELETON_APE, ENEMY_SKELETON_APE_BARREL};
EInit g_EInitSkeletonApePunch = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SKELETON_APE_PUNCH};
EInit g_EInitKillerFish = {ANIMSET_OVL(9), 0x01, 0x50, PAL_KILLER_FISH, ENEMY_KILLER_FISH};
