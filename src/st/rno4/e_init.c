// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

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
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityDummy(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntityAlucardWaterEffect(Entity* self);
void EntitySplashWater(Entity* self);
void EntitySurfacingWater(Entity* self);
void EntitySideWaterSplash(Entity* self);
void EntitySmallWaterDrop(Entity* self);
void EntityWaterDrop(Entity* self);
void func_us_801C12B0_from_no4(Entity* self);
void func_us_801C15F8_from_no4(Entity* self);
void func_us_801C5364(Entity* self);
void EntityBgColumnsParallax_from_no4(Entity* self);
void func_us_801C1EE4_from_no4(Entity* self);
void func_us_801C5C78(Entity* self);
void func_us_801C5EE4(Entity* self);
void func_us_801C2850_from_no4(Entity* self);
void func_us_801C2B78_from_no4(Entity* self);
void func_us_801C2E60_from_no4(Entity* self);
void func_us_801C3160_from_no4(Entity* self);
void func_us_801C34EC_from_no4(Entity* self);
void func_us_801C37C8_from_no4(Entity* self);
void func_us_801C3A04_from_no4(Entity* self);
void func_us_801C3CC4_from_no4(Entity* self);
void func_us_801C3FB0_from_no4(Entity* self);
void func_us_801C4228_from_no4(Entity* self);
void RNO4_Unused801C8768(Entity* self);
void RNO4_Unused801C8770(Entity* self);
void EntityBoatElevatorChains(Entity* self);
void RNO4_Unused801C8BD4(Entity* self);
void RNO4_Unused801C8BDC(Entity* self);
void func_us_801A07CC_from_bo3(Entity* self);
void EntityWaterBox(Entity* self);
void func_us_801C81C8(Entity* self);
void EntityFloatingIcePlatform(Entity* self);
void func_us_801C5518_from_no4(Entity* self);
void func_us_801C8C54(Entity* self);
void func_us_801C909C(Entity* self);
void func_us_801C4BD8_from_no4(Entity* self);
void func_us_801C8668(Entity* self);
void RNO4_Unused801C8704(Entity* self);
void func_us_801C123C_from_no4(Entity* self);
void func_us_801D511C(Entity* self);
void func_us_801D58FC(Entity* self);
void func_us_801D5BA4(Entity* self);
void func_us_801D5E90(Entity* self);
void func_us_801D68E0(Entity* self);
void func_us_801D6B8C(Entity* self);
void EntityVenusWeed(Entity* self);
void EntityVenusWeedFlower(Entity* self);
void EntityVenusWeedTendril(Entity* self);
void EntityVenusWeedDart(Entity* self);
void EntityVenusWeedSpike(Entity* self);
void func_us_801BBE58_from_rnz1(Entity* self);
void func_us_801BC650_from_rnz1(Entity* self);
void func_us_801BCE4C_from_rnz1(Entity* self);
void func_us_801BCA5C_from_rnz1(Entity* self);
void func_us_801BCB9C_from_rnz1(Entity* self);
void func_us_801BCD80_from_rnz1(Entity* self);
void func_us_801BCFC8_from_rnz1(Entity* self);
void func_us_801C870C(Entity* self);
void EntityBreakableCrystalFloor(Entity* self);
void EntityBreakableWall(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntityJackOBones(Entity* self);
void EntityJackOBonesDeathParts(Entity* self);
void EntityJackOBonesJack(Entity* self);
void EntityNovaSkeleton(Entity* self);
void EntityNovaLaser(Entity* self);
void EntityNovaLaserPulse(Entity* self);
void EntityBladeSoldierDeathParts(Entity* self);
void EntityImp(Entity* self);
void EntityImpSmoke(Entity* self);
void EntityRdaiUnk33(Entity* self);
void EntityImpDeathParticle(Entity* self);
void EntityKillerFish(Entity* self);
void EntityKillerFishDeathPuff(Entity* self);

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
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityDummy,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityAlucardWaterEffect,
    EntitySplashWater,
    EntitySurfacingWater,
    EntitySideWaterSplash,
    EntitySmallWaterDrop,
    EntityWaterDrop,
    func_us_801C12B0_from_no4,
    func_us_801C15F8_from_no4,
    func_us_801C5364,
    EntityBgColumnsParallax_from_no4,
    func_us_801C1EE4_from_no4,
    func_us_801C5C78,
    func_us_801C5EE4,
    func_us_801C2850_from_no4,
    func_us_801C2B78_from_no4,
    func_us_801C2E60_from_no4,
    func_us_801C3160_from_no4,
    func_us_801C34EC_from_no4,
    func_us_801C37C8_from_no4,
    func_us_801C3A04_from_no4,
    func_us_801C3CC4_from_no4,
    func_us_801C3FB0_from_no4,
    func_us_801C4228_from_no4,
    RNO4_Unused801C8768,
    RNO4_Unused801C8770,
    EntityBoatElevatorChains,
    RNO4_Unused801C8BD4,
    RNO4_Unused801C8BDC,
    func_us_801A07CC_from_bo3,
    EntityWaterBox,
    func_us_801C81C8,
    EntityFloatingIcePlatform,
    func_us_801C5518_from_no4,
    func_us_801C8C54,
    func_us_801C909C,
    func_us_801C4BD8_from_no4,
    func_us_801C8668,
    RNO4_Unused801C8704,
    func_us_801C123C_from_no4,
    func_us_801D511C,
    func_us_801D58FC,
    func_us_801D5BA4,
    func_us_801D5E90,
    func_us_801D68E0,
    func_us_801D6B8C,
    EntityVenusWeed,
    EntityVenusWeedFlower,
    EntityVenusWeedTendril,
    EntityVenusWeedDart,
    EntityVenusWeedSpike,
    func_us_801BBE58_from_rnz1,
    func_us_801BC650_from_rnz1,
    func_us_801BCE4C_from_rnz1,
    func_us_801BCA5C_from_rnz1,
    func_us_801BCB9C_from_rnz1,
    func_us_801BCD80_from_rnz1,
    func_us_801BCFC8_from_rnz1,
    func_us_801C870C,
    EntityBreakableCrystalFloor,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    EntityJackOBones,
    EntityJackOBonesDeathParts,
    EntityJackOBonesJack,
    EntityNovaSkeleton,
    EntityNovaLaser,
    EntityNovaLaserPulse,
    EntityBladeSoldierDeathParts,
    EntityImp,
    EntityImpSmoke,
    EntityRdaiUnk33,
    EntityImpDeathParticle,
    EntityKillerFish,
    EntityKillerFishDeathPuff,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDarkOctopus = {ANIMSET_OVL(3), 1, 75, 544, 0x026};
EInit D_us_80180B54 = {ANIMSET_OVL(3), 17, 75, 544, 0x027};
EInit g_EInitCaveTroll = {ANIMSET_OVL(4), 0, 72, 551, 0x099};
EInit D_us_80180B6C = {ANIMSET_OVL(4), 0, 72, 551, 0x09A};
EInit D_us_80180B78 = {ANIMSET_OVL(4), 0, 72, 551, 0x09A};
EInit g_EInitBlueVenusWeed1 = {ANIMSET_OVL(7), 0, 80, 564, 0x188};
EInit g_EInitBlueVenusWeed2 = {ANIMSET_OVL(7), 0, 80, 564, 0x189};
EInit D_us_80180B9C = {ANIMSET_OVL(7), 0, 80, 564, 0x18A};
EInit D_us_80180BA8 = {ANIMSET_OVL(7), 55, 80, 564, 0x18B};
EInit g_EInitBombKnight = {ANIMSET_OVL(5), 1, 76, 552, 0x0A5};
EInit g_EInitRockKnight = {ANIMSET_OVL(5), 1, 76, 552, 0x0A7};
EInit D_us_80180BCC = {ANIMSET_OVL(5), 36, 76, 552, 0x0A6};
EInit D_us_80180BD8 = {ANIMSET_OVL(5), 0, 76, 552, 0x002};
EInit D_us_80180BE4 = {ANIMSET_OVL(5), 65, 76, 552, 0x0A8};
EInit g_EInitJackOBones = {ANIMSET_OVL(10), 1, 82, 528, 0x074};
EInit D_us_80180BFC = {ANIMSET_OVL(10), 0, 82, 528, 0x002};
EInit D_us_80180C08 = {ANIMSET_OVL(10), 21, 82, 528, 0x075};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(11), 1, 72, 532, 0x07E};
EInit D_us_80180C20 = {ANIMSET_OVL(11), 0, 72, 532, 0x07F};
EInit g_EInitImp = {ANIMSET_OVL(12), 1, 79, 640, 0x11C};
EInit D_us_80180C38 = {ANIMSET_OVL(12), 1, 79, 640, 0x002};
EInit g_EInitBalloonpod = {ANIMSET_OVL(12), 19, 79, 640, 0x11D};
EInit D_us_80180C50 = {ANIMSET_OVL(12), 42, 79, 640, 0x11E};
EInit g_EInitKillerFish = {ANIMSET_OVL(13), 1, 83, 616, 0x15E};
// clang-format on
