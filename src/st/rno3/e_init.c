// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

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
void EntityDodoBird(Entity* self);

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
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
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
    EntityDodoBird,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitUnused80180938 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitStInteractable = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitFireWarg1 = {ANIMSET_OVL(3), 0x01, 0x4B, PAL_FIRE_WARG, ENEMY_FIRE_WARG};
EInit g_EInitFireWarg2 = {ANIMSET_OVL(3), 0x01, 0x4B, PAL_FIRE_WARG, ENEMY_WARG_RIDER};
EInit g_EInitFireWarg3 = {ANIMSET_DRA(0), 0x00, 0x4B, PAL_FIRE_WARG, ENEMY_FIRE_WARG_UNK_96};
EInit g_EInitJackOBones = {ANIMSET_OVL(4), 0x01, 0x4A, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES};
EInit g_EInitJackOBones2 = {ANIMSET_OVL(4), 0x00, 0x4A, PAL_JACK_O_BONES, ENEMY_PARTICLE};
EInit g_EInitJackOBones3 = {ANIMSET_OVL(4), 0x15, 0x4A, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES_3};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(5), 0x01, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON};
EInit g_EInitNovaSkeleton2 = {ANIMSET_OVL(5), 0x00, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON_LASER};
EInit g_EInitOrobourous = {ANIMSET_OVL(6), 0x01, 0x51, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_OROBOUROUS};
EInit g_EInitOruburos = {ANIMSET_OVL(6), 0x04, 0x51, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_ORUBUROS};
EInit g_EInitOruburosHead = {ANIMSET_OVL(6), 0x04, 0x51, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_PARTICLE};
EInit g_EInitOruburosRider = {ANIMSET_OVL(6), 0x04, 0x51, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_ORUBUROS_RIDER};
EInit g_EInitDragonRider1 = {ANIMSET_OVL(6), 0x01, 0x50, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_DRAGON_RIDER_1};
EInit g_EInitDragonRider2 = {ANIMSET_OVL(6), 0x04, 0x50, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_DRAGON_RIDER_2};
EInit g_EInitDragonRiderHead = {ANIMSET_OVL(6), 0x04, 0x50, PAL_OROBOUROUS_DRAGON_RIDER, ENEMY_PARTICLE};
EInit g_EInitVenusWeedRoot = {ANIMSET_OVL(7), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_BLUE_VENUS_WEED_ROOT};
EInit g_EInitVenusWeedFlower = {ANIMSET_OVL(7), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_BLUE_VENUS_WEED_FLOWER};
EInit g_EInitVenusWeedTendril = {ANIMSET_OVL(7), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_BLUE_VENUS_WEED_TENDRIL};
EInit g_EInitVenusWeedDart = {ANIMSET_OVL(7), 0x37, 0x50, PAL_VENUS_WEED, ENEMY_BLUE_VENUS_WEED_DART};
EInit D_us_80180A34 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit D_us_80180A40 = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitDodoBird = {ANIMSET_OVL(8), 0x01, 0x52, PAL_DODO_BIRD, ENEMY_DODO_BIRD};
// clang-format on
