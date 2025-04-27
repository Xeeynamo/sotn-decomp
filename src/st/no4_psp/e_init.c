// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no4/no4.h"

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
void func_pspeu_0923D568(Entity* self);
void func_pspeu_0923D9E0(Entity* self);
void func_pspeu_0923DD38(Entity* self);
void func_pspeu_0923E368(Entity* self);
void func_pspeu_0923E690(Entity* self);
void func_pspeu_0923EA80(Entity* self);
void func_pspeu_0923EED0(Entity* self);
void func_pspeu_0923F390(Entity* self);
void func_pspeu_0923F860(Entity* self);
void func_pspeu_0923FB88(Entity* self);
void func_pspeu_0923FF60(Entity* self);
void func_pspeu_09240350(Entity* self);
void func_pspeu_09240680(Entity* self);
void func_pspeu_092409A8(Entity* self);
void func_pspeu_09240CD0(Entity* self);
void func_pspeu_09241098(Entity* self);
void func_pspeu_09241410(Entity* self);
void func_pspeu_09239B00(Entity* self);
void func_pspeu_0923B288(Entity* self);
void func_pspeu_0923B378(Entity* self);
void func_pspeu_0923C460(Entity* self);
void func_pspeu_0923D0B8(Entity* self);
void func_pspeu_09238490(Entity* self);
void func_pspeu_09241870(Entity* self);
void func_pspeu_09241B28(Entity* self);
void func_pspeu_09241E38(Entity* self);
void func_pspeu_09242E30(Entity* self);
void func_pspeu_09243478(Entity* self);
void EntitySpearGuardBlock(Entity* self);
void EntityToad(Entity* self);
void EntityFrog(Entity* self);
void func_pspeu_092483A0(Entity* self);
void func_pspeu_092482B0(Entity* self);
void EntityFishheadFireball(Entity* self);
void func_pspeu_09248D90(Entity* self);
void func_pspeu_09249560(Entity* self);
void func_pspeu_09249030(Entity* self);
void func_pspeu_09237700(Entity* self);
void func_pspeu_09256330(Entity* self);
void func_pspeu_09258910(Entity* self);
void func_pspeu_09258E30(Entity* self);
void func_pspeu_09259648(Entity* self);
void func_pspeu_09238E18(Entity* self);
void EntitySpearGuard(Entity* self);
void EntityThrownSpear(Entity* self);
void EntityBoneArcher(Entity* self);
void EntityBoneArcherArrow(Entity* self);
void func_pspeu_0923D180(Entity* self);
void func_pspeu_0925E548(Entity* self);
void func_pspeu_09242200(Entity* self);
void func_pspeu_092391D8(Entity* self);
void func_pspeu_09239568(Entity* self);
void func_pspeu_092423C8(Entity* self);
void func_pspeu_092427C8(Entity* self);
void func_pspeu_09238860(Entity* self);
void EntitySkeletonApe(Entity* self);
void EntitySkeletonApePunch(Entity* self);
void EntitySkeletonApeBarrel(Entity* self);
void EntityThrownBarrel(Entity* self);
void func_pspeu_09238CF0(Entity* self);
void func_pspeu_09242AD0(Entity* self);
void func_pspeu_09242D08(Entity* self);
void func_pspeu_09242FB8(Entity* self);
void func_pspeu_09243260(Entity* self);
void func_pspeu_0923D428(Entity* self);
void func_pspeu_09243320(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    /* 0x00 */ EntityBreakable,
    /* 0x01 */ EntityExplosion,
    /* 0x02 */ EntityPrizeDrop,
    /* 0x03 */ EntityDamageDisplay,
    /* 0x04 */ OVL_EXPORT(EntityRedDoor),
    /* 0x05 */ EntityIntenseExplosion,
    /* 0x06 */ EntitySoulStealOrb,
    /* 0x07 */ EntityRoomForeground,
    /* 0x08 */ EntityStageNamePopup,
    /* 0x09 */ EntityEquipItemDrop,
    /* 0x0A */ EntityRelicOrb,
    /* 0x0B */ EntityHeartDrop,
    /* 0x0C */ EntityEnemyBlood,
    /* 0x0D */ EntityMessageBox,
    /* 0x0E */ EntityDummy,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ OVL_EXPORT(EntityBackgroundBlock),
    /* 0x11 */ EntityLockCamera,
    /* 0x12 */ EntityUnkId13,
    /* 0x13 */ EntityExplosionVariants,
    /* 0x14 */ EntityGreyPuff,
    /* 0x15 */ EntityAlucardWaterEffect,
    /* 0x16 */ EntitySplashWater,
    /* 0x17 */ EntitySurfacingWater,
    /* 0x18 */ EntitySideWaterSplash,
    /* 0x19 */ EntitySmallWaterDrop,
    /* 0x1A */ EntityWaterDrop,
    /* 0x1B */ func_pspeu_0923D568,
    /* 0x1C */ func_pspeu_0923D9E0,
    /* 0x1D */ func_pspeu_0923DD38,
    /* 0x1E */ func_pspeu_0923E368,
    /* 0x1F */ func_pspeu_0923E690,
    /* 0x20 */ func_pspeu_0923EA80,
    /* 0x21 */ func_pspeu_0923EED0,
    /* 0x22 */ func_pspeu_0923F390,
    /* 0x23 */ func_pspeu_0923F860,
    /* 0x24 */ func_pspeu_0923FB88,
    /* 0x25 */ func_pspeu_0923FF60,
    /* 0x26 */ func_pspeu_09240350,
    /* 0x27 */ func_pspeu_09240680,
    /* 0x28 */ func_pspeu_092409A8,
    /* 0x29 */ func_pspeu_09240CD0,
    /* 0x2A */ func_pspeu_09241098,
    /* 0x2B */ func_pspeu_09241410,
    /* 0x2C */ func_pspeu_09239B00,
    /* 0x2D */ func_pspeu_0923B288,
    /* 0x2E */ func_pspeu_0923B378,
    /* 0x2F */ func_pspeu_0923C460,
    /* 0x30 */ func_pspeu_0923D0B8,
    /* 0x31 */ EntityDummy,
    /* 0x32 */ EntityDummy,
    /* 0x33 */ EntityDummy,
    /* 0x34 */ func_pspeu_09238490,
    /* 0x35 */ func_pspeu_09241870,
    /* 0x36 */ func_pspeu_09241B28,
    /* 0x37 */ func_pspeu_09241E38,
    /* 0x38 */ func_pspeu_09242E30,
    /* 0x39 */ func_pspeu_09243478,
    /* 0x3A */ EntitySpearGuardBlock,
    /* 0x3B */ EntityToad,
    /* 0x3C */ EntityFrog,
    /* 0x3D */ func_pspeu_092483A0,
    /* 0x3E */ func_pspeu_092482B0,
    /* 0x3F */ EntityFishheadFireball,
    /* 0x40 */ func_pspeu_09248D90,
    /* 0x41 */ func_pspeu_09249560,
    /* 0x42 */ func_pspeu_09249030,
    /* 0x43 */ func_pspeu_09237700,
    /* 0x44 */ func_pspeu_09256330,
    /* 0x45 */ func_pspeu_09258910,
    /* 0x46 */ func_pspeu_09258E30,
    /* 0x47 */ func_pspeu_09259648,
    /* 0x48 */ func_pspeu_09238E18,
    /* 0x49 */ EntitySpearGuard,
    /* 0x4A */ EntityThrownSpear,
    /* 0x4B */ EntityBoneArcher,
    /* 0x4C */ EntityBoneArcherArrow,
    /* 0x4D */ func_pspeu_0923D180,
    /* 0x4E */ func_pspeu_0925E548,
    /* 0x4F */ func_pspeu_09242200,
    /* 0x50 */ func_pspeu_092391D8,
    /* 0x51 */ func_pspeu_09239568,
    /* 0x52 */ func_pspeu_092423C8,
    /* 0x53 */ func_pspeu_092427C8,
    /* 0x54 */ func_pspeu_09238860,
    /* 0x55 */ EntitySkeletonApe,
    /* 0x56 */ EntitySkeletonApePunch,
    /* 0x57 */ EntitySkeletonApeBarrel,
    /* 0x58 */ EntityThrownBarrel,
    /* 0x59 */ func_pspeu_09238CF0,
    /* 0x5A */ func_pspeu_09242AD0,
    /* 0x5B */ func_pspeu_09242D08,
    /* 0x5C */ func_pspeu_09242FB8,
    /* 0x5D */ func_pspeu_09243260,
    /* 0x5E */ func_pspeu_0923D428,
    /* 0x5F */ func_pspeu_09243320,
};

EInit D_pspeu_09267A90 = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit D_pspeu_09267AF0 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit D_us_80180BF8 = {ANIMSET_OVL(0x02), 0x05, 0x48, 0x201, 0x05D};
EInit g_EInitToad = {ANIMSET_OVL(0x03), 0x01, 0x4B, 0x204, 0x06A};
EInit g_EInitFrog = {ANIMSET_OVL(0x03), 0x01, 0x4B, 0x204, 0x06B};
EInit D_pspeu_09267B40 = {ANIMSET_OVL(0x04), 0x01, 0x4A, 0x206, 0x115};
EInit D_pspeu_09267B50 = {ANIMSET_OVL(0x04), 0x13, 0x4A, 0x206, 0x005};
EInit g_EInitFishheadFireball = {ANIMSET_OVL(0x04), 0x00, 0x4A, 0x206, 0x116};
EInit D_pspeu_09267B70 = {ANIMSET_OVL(0x04), 0x00, 0x4A, 0x206, 0x002};
EInit D_pspeu_09267B80 = {ANIMSET_OVL(0x04), 0x00, 0x4A, 0x206, 0x117};
EInit D_pspeu_09267B90 = {ANIMSET_OVL(0x06), 0x00, 0x4F, 0x216, 0x040};
EInit D_pspeu_09267BA0 = {ANIMSET_OVL(0x07), 0x01, 0x4C, 0x219, 0x063};
EInit D_pspeu_09267BB0 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x064};
EInit D_pspeu_09267BC0 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x0D2};
EInit g_EInitSpearGuard = {ANIMSET_OVL(0x02), 0x05, 0x48, 0x201, 0x05D};
EInit g_EInitThrownSpear = {ANIMSET_OVL(0x02), 0x05, 0x48, 0x201, 0x060};
EInit g_EInitBoneArcher = {ANIMSET_OVL(0x08), 0x01, 0x4E, 0x21A, 0x06C};
EInit g_EInitBoneArcherArrow = {ANIMSET_OVL(0x08), 0x00, 0x4E, 0x21A, 0x06D};
EInit D_us_80180CB8 = {ANIMSET_OVL(0x01), 0x00, 0x00, 0x000, 0x005};
EInit g_EInitSkeletonApe = {ANIMSET_OVL(0x0A), 0x01, 0x4C, 0x21D, 0x053};
EInit g_EInitSkeletonApeBarrel = {ANIMSET_OVL(0x0A), 0x28, 0x4C, 0x21D, 0x054};
EInit g_EInitSkeletonApePunch = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x181};
EInit D_pspeu_09267C40 = {ANIMSET_OVL(0x09), 0x01, 0x50, 0x21B, 0x15E};
