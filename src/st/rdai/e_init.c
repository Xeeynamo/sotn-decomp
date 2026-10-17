// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

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
void func_us_801B1C34(Entity* self);
void EntityCastleWall1(Entity* self);
void EntityCastleWall2(Entity* self);
void EntityStaircase(Entity* self);
void func_us_801B2C28(Entity* self);
void func_us_801B3368(Entity* self);
void func_us_801BFE6C(Entity* self);
void func_us_801C0240(Entity* self);
void func_us_801BF830(Entity* self);
void EntityRdaiUnk1F(Entity* self);
void func_us_801C0528(Entity* self);
void func_us_801C0898(Entity* self);
void func_us_801C0C44(Entity* self);
void EntitySpectralSwordAura(Entity* self);
void func_us_801C17E8(Entity* self);
void func_us_801C1DE8(Entity* self);
void func_us_801C2418(Entity* self);
void func_us_801C3580(Entity* self);
void EntityImp(Entity* self);
void EntityImpSmoke(Entity* self);
void EntityClouds(Entity* self);
void EntityBackgroundSkyLand(Entity* self);
void EntityRbo3Door(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikesDamage(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityBlackPanther(Entity* self);
void EntityBalloonPod(Entity* self);
void EntityImpDeathParticle(Entity* self);

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
    func_us_801B1C34,
    EntityCastleWall1,
    EntityCastleWall2,
    EntityStaircase,
    func_us_801B2C28,
    func_us_801B3368,
    func_us_801BFE6C,
    func_us_801C0240,
    func_us_801BF830,
    EntityRdaiUnk1F,
    func_us_801C0528,
    func_us_801C0898,
    func_us_801C0C44,
    EntitySpectralSwordAura,
    func_us_801C17E8,
    func_us_801C1DE8,
    func_us_801C2418,
    func_us_801C3580,
    EntityImp,
    EntityImpSmoke,
    EntityClouds,
    EntityBackgroundSkyLand,
    EntityRbo3Door,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikesDamage,
    EntityBreakableDebris,
    EntityBlackPanther,
    EntityBalloonPod,
    EntityImpDeathParticle,
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
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_Rbo3DoorInit = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitRdaiUnk1F = {ANIMSET_OVL(3), 0x00, 0x48, PAL_ARCHER, ENEMY_INTERACTABLE};
EInit g_EInitArcher = {ANIMSET_OVL(3), 0x00, 0x48, PAL_ARCHER, ENEMY_ARCHER};
EInit D_us_80180884 = {ANIMSET_OVL(3), 0x00, 0x48, PAL_ARCHER, ENEMY_ARCHER_UNK_132};
EInit D_us_80180890 = {ANIMSET_OVL(3), 0x00, 0x48, PAL_ARCHER, ENEMY_PARTICLE};
EInit g_EInitSpectralSwordRDAI = {ANIMSET_OVL(4), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_RDAI};
EInit g_EInitSpectralSwordAura = {ANIMSET_OVL(4), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_PARTICLE};
EInit g_EInitSpear = {ANIMSET_OVL(4), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_SPEAR};
EInit g_EInitShield = {ANIMSET_OVL(4), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_SHIELD};
EInit g_EInitSniperOfGoth = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_SNIPER_OF_GOTH, ENEMY_SNIPER_OF_GOTH};
EInit D_us_801808D8 = {ANIMSET_OVL(5), 0x11, 0x4C, PAL_SNIPER_OF_GOTH, ENEMY_SNIPER_OF_GOTH_UNK_C4};
EInit D_us_801808E4 = {ANIMSET_OVL(5), 0x3A, 0x4C, PAL_SNIPER_OF_GOTH, ENEMY_SNIPER_OF_GOTH_UNK_C5};
EInit g_EInitImp = {ANIMSET_OVL(6), 0x01, 0x4F, PAL_IMP, ENEMY_IMP};
EInit g_EInitImpSmoke = {ANIMSET_OVL(6), 0x01, 0x4F, PAL_IMP, ENEMY_PARTICLE};
EInit g_EInitBalloonPod = {ANIMSET_OVL(6), 0x13, 0x4F, PAL_IMP, ENEMY_BALLOON_POD};
EInit g_EInitImpDeathParticle = {ANIMSET_OVL(6), 0x2A, 0x4F, PAL_IMP, ENEMY_IMP_DEATH_PARTICLE};
EInit g_EInitBlackPanther = {ANIMSET_OVL(9), 0x00, 0x4A, PAL_BLACK_PANTHER, ENEMY_BLACK_PANTHER};
// clang-format on
