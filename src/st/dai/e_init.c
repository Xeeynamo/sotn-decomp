// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

void OVL_EXPORT(EntityBreakable)(Entity* self);
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
void EntityTowerExit(Entity* self);
void EntityStainedGlass(Entity* self);
void EntityStainedGlassBackground(Entity* self);
void EntityBlock(Entity* self);
void EntityStatue(Entity* self);
void EntityBell(Entity* self);
void EntityCastleWall1(Entity* self);
void EntityCastleWall2(Entity* self);
void EntityStaircase(Entity* self);
void EntityClouds(Entity* self);
void EntityBackgroundSkyLand(Entity* self);
void EntityGargoyleTongue(Entity* self);
void EntityChair(Entity* self);
void EntityConfessionalGhost(Entity* self);
void EntityConfessionalBlades(Entity* self);
void EntityConfessionalBladeDebris(Entity* self);
void EntityBellSpawner(Entity* self);
void EntityCornerGuard(Entity* self);
void EntityCornerGuardAttack(Entity* self);
void EntityBonePillarSkull(Entity* self);
void EntityBonePillarFireBreath(Entity* self);
void EntityBonePillarDeathParts(Entity* self);
void EntityBonePillarSpikeBall(Entity* self);
void EntityEndConfessionalChime(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikesDamage(Entity* self);
void EntityBoneHalberd(Entity* self);
void EntityBoneHalberdNaginata(Entity* self);
void EntityBoneHalberdParts(Entity* self);
void EntityWingedGuard(Entity* self);
void EntityWingedGuardParts(Entity* self);
void EntityBat(Entity* self);
void EntityBlackCrow(Entity* self);
void EntityBlueRaven(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void EntityHuntingGirl(Entity* self);
void EntityHuntingGirlAttack(Entity* self);
void EntitySpectralSword(Entity* self);
void EntitySpectralSwordAura(Entity* self);
void EntitySpectralSwordWeapon(Entity* self);
void EntityWingedGuardSpawner(Entity* self);
void EntitySealedDoor(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void OVL_EXPORT(EntityCutscene)(Entity* self);
void func_us_801C5920(Entity* self);
void func_us_801C5B88(Entity* self);
void EntityMistDoor(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
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
    EntityTowerExit,
    EntityStainedGlass,
    EntityStainedGlassBackground,
    EntityBlock,
    EntityStatue,
    EntityBell,
    EntityCastleWall1,
    EntityCastleWall2,
    EntityStaircase,
    EntityClouds,
    EntityBackgroundSkyLand,
    EntityGargoyleTongue,
    EntityChair,
    EntityConfessionalGhost,
    EntityConfessionalBlades,
    EntityConfessionalBladeDebris,
    EntityBellSpawner,
    EntityCornerGuard,
    EntityCornerGuardAttack,
    EntityBonePillarSkull,
    EntityBonePillarFireBreath,
    EntityBonePillarDeathParts,
    EntityBonePillarSpikeBall,
    EntityEndConfessionalChime,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikesDamage,
    EntityBoneHalberd,
    EntityBoneHalberdNaginata,
    EntityBoneHalberdParts,
    EntityWingedGuard,
    EntityWingedGuardParts,
    EntityBat,
    EntityBlackCrow,
    EntityBlueRaven,
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    EntityHuntingGirl,
    EntityHuntingGirlAttack,
    EntitySpectralSword,
    EntitySpectralSwordAura,
    EntitySpectralSwordWeapon,
    EntityWingedGuardSpawner,
    EntitySealedDoor,
    OVL_EXPORT(EntityBreakableDebris),
    OVL_EXPORT(EntityCutscene),
    func_us_801C5920,
    func_us_801C5B88,
    EntityMistDoor,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 0};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 1};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 2};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 4};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 5};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 2};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 1};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 3};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 3};
EInit g_EInitUnused801809A4 = {ANIMSET_OVL(1), 43, 72, PAL_SKELERANG, 3};
// This seems to be used as a common init and should probably be renamed
EInit g_EInitStatueBlock = {ANIMSET_OVL(1), 0, 0, PAL_NONE, 5};
EInit g_EInitConfessionalGhost = {
    ANIMSET_OVL(2), 0, 72, PAL_CONFESSIONAL_C9, 5};
EInit g_EInitUnused801809C8 = {ANIMSET_OVL(2), 0, 72, PAL_801809C8, 5};
EInit g_EInitConfessionalBlades = {
    ANIMSET_OVL(2), 37, 72, PAL_CONFESSIONAL_C9, 101};
EInit g_EInitCornerGuard = {ANIMSET_OVL(4), 0, 72, PAL_CORNER_GUARD, 180};
EInit g_EInitCornerGuardAttack = {ANIMSET_OVL(0), 0, 0, PAL_NONE, 181};
EInit g_EInitBonePillarSkull = {ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 0x0B7};
EInit g_EInitBonePillarParts = {ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 0x002};
EInit g_EInitBonePillarFireBreath = {
    ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 184};
EInit g_EInitBonePillarSpikeBall = {
    ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 185};
EInit g_EInitBoneHalberd = {ANIMSET_OVL(7), 1, 72, PAL_UNK_22A, 118};
EInit g_EInitBoneHalberdNaginata = {ANIMSET_OVL(0), 0, 0, PAL_NONE, 119};
EInit g_EInitWingedGuard = {ANIMSET_OVL(8), 0, 75, PAL_WINGED_GUARD, 128};
EInit g_EInitWingedGuardParts = {ANIMSET_OVL(8), 0, 75, PAL_WINGED_GUARD, 3};
EInit g_EInitBat = {ANIMSET_OVL(9), 0, 74, PAL_BAT, 64};
EInit g_EInitBlueRaven = {ANIMSET_OVL(10), 0, 79, PAL_CROW, 114};
EInit g_EInitBlackCrow = {ANIMSET_OVL(10), 0, 79, PAL_CROW, 115};
EInit g_EInitSkelerang = {ANIMSET_OVL(11), 1, 72, PAL_SKELERANG, 11};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(11), 43, 72, PAL_SKELERANG, 12};
EInit g_EInitHuntingGirl = {ANIMSET_OVL(12), 0, 84, PAL_HUNTING_GIRL_INIT, 227};
EInit g_EInitSpectralSword = {ANIMSET_OVL(13), 0, 81, PAL_SPECTRAL_SWORD, 136};
EInit g_EInitSpectralSwordAura = {
    ANIMSET_OVL(13), 0, 81, PAL_SPECTRAL_SWORD, 2};
EInit g_EInitSpectralSwordWeapon = {
    ANIMSET_OVL(13), 0, 81, PAL_SPECTRAL_SWORD_WEAPON_1, 137};
