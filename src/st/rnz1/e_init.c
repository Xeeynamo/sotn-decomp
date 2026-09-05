// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

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
void EntityExplosionPuffOpaque(Entity* self);
void EntityClouds(Entity* self);
void EntityBackgroundGears(Entity* self);
void EntityGearSidewaysLarge(Entity* self);
void EntityGearHorizontal(Entity* self);
void EntityGearVertical(Entity* self);
void EntityGearSidewaysSmall(Entity* self);
void EntityWallGear(Entity* self);
void EntityBreakableWall(Entity* self);
void EntitySecretWallDebris(Entity* self);
void EntityRoomExit(Entity* self);
void EntityBreakableWallPartial(Entity* self);
void EntitySecretAreaDoor(Entity* self);
void EntityWaterForeground(Entity* self);
void EntityAlucardWaterEffect(Entity* self);
void EntitySplashWater(Entity* self);
void EntitySurfacingWater(Entity* self);
void EntitySideWaterSplash(Entity* self);
void EntitySmallWaterDrop(Entity* self);
void EntityWaterDrop(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikesDamage(Entity* self);
void EntityDarkwingBat(Entity* self);
void EntityDarkwingBatPerch(Entity* self);
void EntityDarkwingBatWings(Entity* self);
void EntityDarkwingWindDust(Entity* self);
void EntityFadingFireball(Entity* self);
void EntityBossFightManager(Entity* self);
void EntityBossDoors(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityCloakedKnight(Entity* self);
void EntityCloakedKnightCloak(Entity* self);
void EntityCloakedKnightSword(Entity* self);
void EntityCloakedKnightAura(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C8954_from_are(Entity* self);
void func_us_801C8AAC_from_are(Entity* self);
void func_us_801BBE58(Entity* self);
void func_us_801BC650(Entity* self);
void func_us_801BCE4C(Entity* self);
void func_us_801BCA5C(Entity* self);
void func_us_801BCB9C(Entity* self);
void func_us_801BCD80(Entity* self);
void func_us_801BCFC8(Entity* self);
void func_us_801BD398(Entity* self);
void func_us_801BDA24(Entity* self);
void func_us_801BD324(Entity* self);

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
    EntityExplosionPuffOpaque,
    EntityClouds,
    EntityBackgroundGears,
    EntityGearSidewaysLarge,
    EntityGearHorizontal,
    EntityGearVertical,
    EntityGearSidewaysSmall,
    EntityWallGear,
    EntityBreakableWall,
    EntitySecretWallDebris,
    EntityRoomExit,
    EntityBreakableWallPartial,
    EntitySecretAreaDoor,
    EntityWaterForeground,
    EntityAlucardWaterEffect,
    EntitySplashWater,
    EntitySurfacingWater,
    EntitySideWaterSplash,
    EntitySmallWaterDrop,
    EntityWaterDrop,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikesDamage,
    EntityDarkwingBat,
    EntityDarkwingBatPerch,
    EntityDarkwingBatWings,
    EntityDarkwingWindDust,
    EntityFadingFireball,
    EntityBossFightManager,
    EntityBossDoors,
    EntityLifeUpSpawn,
    EntityCloakedKnight,
    EntityCloakedKnightCloak,
    EntityCloakedKnightSword,
    EntityCloakedKnightAura,
    EntityMedusaHeadSpawner,
    EntityMedusaHeadBlue,
    EntityMedusaHeadYellow,
    EntityBreakableDebris,
    EntityValhallaKnight,
    func_us_801C8954_from_are,
    func_us_801C8AAC_from_are,
    func_us_801BBE58,
    func_us_801BC650,
    func_us_801BCE4C,
    func_us_801BCA5C,
    func_us_801BCB9C,
    func_us_801BCD80,
    func_us_801BCFC8,
    func_us_801BD398,
    func_us_801BDA24,
    func_us_801BD324,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitUnused80180B7C = {ANIMSET_OVL(1), 0, 0, 0, 0x003};
EInit g_EInitPlateLord = {ANIMSET_OVL(11), 1, 72, 538, 0x061};
EInit g_EInitUnused80180B94 = {ANIMSET_OVL(11), 22, 72, 538, 0x062};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitUnused80180BAC = {ANIMSET_OVL(3), 0, 0, 0, 0x005};
EInit g_EInitDarkwingBat = {ANIMSET_OVL(5), 1, 72, 512, 0x111};
EInit g_EInitDarkwingBat2 = {ANIMSET_OVL(5), 0, 72, 512, 0x005};
EInit g_EInitCloakedknight = {ANIMSET_OVL(6), 1, 72, 528, 0x10F};
EInit g_EInitCloakedKnightAura = {ANIMSET_OVL(6), 1, 72, 528, 0x002};
EInit D_us_80180BE8 = {ANIMSET_OVL(6), 1, 72, 528, 0x110};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(7), 0, 73, 533, 0x12F};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(7), 0, 73, 534, 0x130};
EInit g_EInitValhallaKnight = {ANIMSET_OVL(8), 1, 76, 562, 0x085};
EInit D_us_80180C18 = {ANIMSET_OVL(8), 1, 76, 562, 0x003};
EInit D_us_80180C24 = {ANIMSET_OVL(0), 0, 0, 0, 0x086};
EInit D_us_80180C30 = {ANIMSET_OVL(0), 0, 0, 0, 0x087};
EInit g_EInitBombKnight = {ANIMSET_OVL(11), 1, 72, 566, 0x0A5};
EInit D_us_80180C48 = {ANIMSET_OVL(11), 36, 72, 566, 0x0A6};
EInit D_us_80180C54 = {ANIMSET_OVL(11), 0, 72, 566, 0x002};
EInit D_us_80180C60 = {ANIMSET_OVL(11), 65, 72, 566, 0x0A8};
EInit g_EInitRockKnight = {ANIMSET_OVL(11), 1, 72, 566, 0x0A7};
EInit D_us_80180C78 = {ANIMSET_OVL(13), 1, 81, 572, 0x005};
// clang-format on
