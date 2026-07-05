// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

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
void EntityCastleDoor(Entity* self);
void EntityShuttingWindow(Entity* self);
void EntityBackgroundBushes(Entity* self);
void EntityBackgroundTrees(Entity* self);
void EntityBackgroundLightning(Entity* self);
void EntityLightningThunder(Entity* self);
void EntityLightningCloud(Entity* self);
void EntityFireWarg(Entity* self);
void EntityFireWargWaveAttack(Entity* self);
void EntityUnkId2F(Entity* self);
void EntityUnkId30(Entity* self);
void EntityUnkId31(Entity* self);
void EntityExplosion3(Entity* self);
void EntityFireWargDeathBeams(Entity* self);
void EntityJackOBones(Entity* self);
void EntityJackOBonesDeathParts(Entity* self);
void EntityJackOBonesJack(Entity* self);
void EntityNovaSkeleton(Entity* self);
void EntityNovaLaser(Entity* self);
void EntityNovaLaserPulse(Entity* self);
void EntityNovaSkeletonDeathParts(Entity* self);
void EntityOrobourous(Entity* self);
void EntityOrobSegment(Entity* self);
void EntityOrobHeadParts(Entity* self);
void EntityOrobRider(Entity* self);
void EntityOrobHolyAttacker(Entity* self);
void EntityDragonRider(Entity* self);
void EntityDragonSegment(Entity* self);
void EntityDragonHeadParts(Entity* self);
void EntityDragonRiderHitbox(Entity* self);
void EntityVenusWeed(Entity* self);
void EntityVenusWeedFlower(Entity* self);
void EntityVenusWeedTendril(Entity* self);
void EntityVenusWeedDart(Entity* self);
void EntityVenusWeedSpike(Entity* self);
void EntityCavernDoorLever(Entity* self);
void EntityCavernDoorPlatform(Entity* self);
void EntityCavernDoor(Entity* self);
void EntityWeightsSwitch(Entity* self);
void EntityPathBlockSmallWeight(Entity* self);
void EntityPathBlockTallWeight(Entity* self);
void EntityHeartRoomSwitch(Entity* self);
void EntityHeartRoomGoldDoor(Entity* self);
void EntityMermanRockLeftSide(Entity* self);
void EntityMermanRockRightSide(Entity* self);
void EntityJewelSwordDoor(Entity* self);
void EntityFallingRock2(Entity* self);
void EntityStairwayPiece(Entity* self);
void EntityFallingRock(Entity* self);
void EntityTransparentWater(Entity* self);
void EntityAlucardWaterEffect(Entity* self);
void EntitySplashWater(Entity* self);
void EntitySurfacingWater(Entity* self);
void EntitySideWaterSplash(Entity* self);
void EntitySmallWaterDrop(Entity* self);
void EntityWaterDrop(Entity* self);
void func_us_801C8B8C(Entity* self);

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
    EntityDummy,
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityCastleDoor,
    EntityShuttingWindow,
    EntityBackgroundBushes,
    EntityBackgroundTrees,
    EntityBackgroundLightning,
    EntityLightningThunder,
    EntityLightningCloud,
    EntityFireWarg,
    EntityFireWargWaveAttack,
    EntityUnkId2F,
    EntityUnkId30,
    EntityUnkId31,
    EntityExplosion3,
    EntityFireWargDeathBeams,
    EntityJackOBones,
    EntityJackOBonesDeathParts,
    EntityJackOBonesJack,
    EntityNovaSkeleton,
    EntityNovaLaser,
    EntityNovaLaserPulse,
    EntityNovaSkeletonDeathParts,
    EntityOrobourous,
    EntityOrobSegment,
    EntityOrobHeadParts,
    EntityOrobRider,
    EntityOrobHolyAttacker,
    EntityDragonRider,
    EntityDragonSegment,
    EntityDragonHeadParts,
    EntityDragonRiderHitbox,
    EntityVenusWeed,
    EntityVenusWeedFlower,
    EntityVenusWeedTendril,
    EntityVenusWeedDart,
    EntityVenusWeedSpike,
    EntityCavernDoorLever,
    EntityCavernDoorPlatform,
    EntityCavernDoor,
    EntityWeightsSwitch,
    EntityPathBlockSmallWeight,
    EntityPathBlockTallWeight,
    EntityHeartRoomSwitch,
    EntityHeartRoomGoldDoor,
    EntityMermanRockLeftSide,
    EntityMermanRockRightSide,
    EntityJewelSwordDoor,
    EntityFallingRock2,
    EntityStairwayPiece,
    EntityFallingRock,
    EntityTransparentWater,
    EntityAlucardWaterEffect,
    EntitySplashWater,
    EntitySurfacingWater,
    EntitySideWaterSplash,
    EntitySmallWaterDrop,
    EntityWaterDrop,
    func_us_801C8B8C,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit OVL_EXPORT(EInitObtainable) = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit OVL_EXPORT(EInitParticle) = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitUnused80180938 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitStInteractable = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit g_EInitFireWarg1 = {ANIMSET_OVL(3), 1, 75, 512, 0x094};
EInit g_EInitFireWarg2 = {ANIMSET_OVL(3), 1, 75, 512, 0x097};
EInit g_EInitFireWarg3 = {ANIMSET_DRA(0), 0, 75, 512, 0x096};
EInit g_EInitJackOBones = {ANIMSET_OVL(4), 1, 74, 524, 0x074};
EInit D_us_80180980 = {ANIMSET_OVL(4), 0, 74, 524, 0x002};
EInit D_us_8018098C = {ANIMSET_OVL(4), 21, 74, 524, 0x075};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(5), 1, 72, 532, 0x07E};
EInit D_us_801809A4 = {ANIMSET_OVL(5), 0, 72, 532, 0x07F};
EInit g_EInitOrobourous = {ANIMSET_OVL(6), 1, 81, 561, 0x08D};
EInit g_EInitOruburos = {ANIMSET_OVL(6), 4, 81, 561, 0x08E};
EInit D_us_801809C8 = {ANIMSET_OVL(6), 4, 81, 561, 0x002};
EInit g_EInitOruburosRider = {ANIMSET_OVL(6), 4, 81, 561, 0x08F};
EInit g_EInitDragonRider1 = {ANIMSET_OVL(6), 1, 80, 561, 0x090};
EInit g_EInitDragonRider2 = {ANIMSET_OVL(6), 4, 80, 561, 0x091};
EInit D_us_801809F8 = {ANIMSET_OVL(6), 4, 80, 561, 0x002};
EInit g_EInitVenusWeedRoot = {ANIMSET_OVL(7), 0, 80, 576, 0x188};
EInit g_EInitVenusWeedFlower = {ANIMSET_OVL(7), 0, 80, 576, 0x189};
EInit g_EInitVenusWeedTendril = {ANIMSET_OVL(7), 0, 80, 576, 0x18A};
EInit g_EInitVenusWeedDart = {ANIMSET_OVL(7), 55, 80, 576, 0x18B};
EInit D_us_80180A34 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit D_us_80180A40 = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit g_EInitDodoBird = {ANIMSET_OVL(8), 1, 82, 618, 0x068};
// clang-format on
