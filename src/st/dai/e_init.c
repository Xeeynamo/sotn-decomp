// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

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
void EntityBoneHalberdAttack(Entity* self);
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
void EntityBreakableDebris(Entity* self);
void EntityCutsceneDialogue(Entity* self);
void EntityCutsceneStage(Entity* self);
void EntityCutsceneMaria(Entity* self);
void EntityMistDoor(Entity* self);

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
    EntityBoneHalberdAttack,
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
    EntityBreakableDebris,
    EntityCutsceneDialogue,
    EntityCutsceneStage,
    EntityCutsceneMaria,
    EntityMistDoor,
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
EInit g_EInitUnused801809A4 = {ANIMSET_OVL(1), 0x2B, 0x48, PAL_SKELERANG, ENEMY_COMMON};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitConfessionalGhost = {ANIMSET_OVL(2), 0x00, 0x48, PAL_CONFESSIONAL_GHOST, ENEMY_INTERACTABLE};
EInit g_EInitUnused801809C8 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_UNUSED, ENEMY_INTERACTABLE};
EInit g_EInitConfessionalBlades = {ANIMSET_OVL(2), 0x25, 0x48, PAL_CONFESSIONAL_GHOST, ENEMY_CONFESSIONAL_BLADES};
EInit g_EInitCornerGuard = {ANIMSET_OVL(4), 0x00, 0x48, PAL_CORNER_GUARD, ENEMY_CORNER_GUARD};
EInit g_EInitCornerGuardAttack = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_CORNER_GUARD_ATTACK};
EInit g_EInitBonePillarSkull = {ANIMSET_OVL(5), 0x00, 0x49, PAL_BONE_PILLAR, ENEMY_BONE_PILLAR_SKULL};
EInit g_EInitBonePillarParts = {ANIMSET_OVL(5), 0x00, 0x49, PAL_BONE_PILLAR, ENEMY_PARTICLE};
EInit g_EInitBonePillarFireBreath = {ANIMSET_OVL(5), 0x00, 0x49, PAL_BONE_PILLAR, ENEMY_BONE_PILLAR_FIRE_BREATH};
EInit g_EInitBonePillarSpikeBall = {ANIMSET_OVL(5), 0x00, 0x49, PAL_BONE_PILLAR, ENEMY_SPIKED_BALL};
EInit g_EInitBoneHalberd = {ANIMSET_OVL(7), 0x01, 0x48, PAL_BONE_HALBERD, ENEMY_BONE_HALBERD};
EInit g_EInitBoneHalberdAttack = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_BONE_HALBERD_ATTACK};
EInit g_EInitWingedGuard = {ANIMSET_OVL(8), 0x00, 0x4B, PAL_WINGED_GUARD, ENEMY_WINGED_GUARD};
EInit g_EInitWingedGuardParts = {ANIMSET_OVL(8), 0x00, 0x4B, PAL_WINGED_GUARD, ENEMY_COMMON};
EInit g_EInitBat = {ANIMSET_OVL(9), 0x00, 0x4A, PAL_BAT, ENEMY_BAT};
EInit g_EInitBlueRaven = {ANIMSET_OVL(10), 0x00, 0x4F, PAL_CROW, ENEMY_BLUE_RAVEN};
EInit g_EInitBlackCrow = {ANIMSET_OVL(10), 0x00, 0x4F, PAL_CROW, ENEMY_BLACK_CROW};
EInit g_EInitSkelerang = {ANIMSET_OVL(11), 0x01, 0x48, PAL_SKELERANG, ENEMY_SKELERANG};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(11), 0x2B, 0x48, PAL_SKELERANG, ENEMY_SKELERANG_BOOMERANG};
EInit g_EInitHuntingGirl = {ANIMSET_OVL(12), 0x00, 0x54, PAL_HUNTING_GIRL_INIT, ENEMY_HUNTING_GIRL};
EInit g_EInitSpectralSword = {ANIMSET_OVL(13), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_DAI};
EInit g_EInitSpectralSwordAura = {ANIMSET_OVL(13), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_PARTICLE};
EInit g_EInitSpectralSwordWeapon = {ANIMSET_OVL(13), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPECTRAL_SWORD_WEAPON};
// clang-format on
