// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

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
void EntityBossTorch(Entity* self);
void EntityBossDoors(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityCoffin(Entity* self);
void EntityBoss(Entity* self);
void EntityFakeRalph(Entity* self);
void EntityFakeGrant(Entity* self);
void EntityFakeSypha(Entity* self);
void EntityBoneCross(Entity* self);
void EntityBoneCrossAfterImage(Entity* self);
void EntityGiantBoneCross(Entity* self);
void EntityDagger(Entity* self);
void EntityHolyWaterFlask(Entity* self);
void EntityHolyWaterFlame(Entity* self);
void EntityVerticalDagger(Entity* self);
void EntityHorizontalDagger(Entity* self);
void func_us_80197764(Entity* self);
void func_us_80196768(Entity* self);
void EntityDeathFlames(Entity* self);
void EntityFlameAttack(Entity* self);
void EntityPetrifyCloud(Entity* self);
void EntityHolyLightning(Entity* self);
void EntitySummonAttack(Entity* self);

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
    EntityBossTorch,
    EntityBossDoors,
    EntityLifeUpSpawn,
    EntityCoffin,
    EntityBoss,
    EntityFakeRalph,
    EntityFakeGrant,
    EntityFakeSypha,
    EntityBoneCross,
    EntityBoneCrossAfterImage,
    EntityGiantBoneCross,
    EntityDagger,
    EntityHolyWaterFlask,
    EntityHolyWaterFlame,
    EntityVerticalDagger,
    EntityHorizontalDagger,
    func_us_80197764,
    func_us_80196768,
    EntityDeathFlames,
    EntityFlameAttack,
    EntityPetrifyCloud,
    EntityHolyLightning,
    EntitySummonAttack,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_us_8018044C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_us_80180494 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit D_us_801804AC = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_TREVOR};
EInit D_us_801804B8 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_GRANT};
EInit D_us_801804C4 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_SYPHA};
EInit D_us_801804D0 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_FAKE_TREVOR_UNK_149};
EInit D_us_801804DC = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_TREVOR_UNK_14A};
EInit D_us_801804E8 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_PARTICLE};
EInit D_us_801804F4 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_TREVOR_UNK_14B};
EInit D_us_80180500 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_TREVOR_UNK_14C};
EInit D_us_8018050C = {ANIMSET_DRA(14), 0x00, 0x79, PAL_UNK_169, ENEMY_FAKE_TREVOR_UNK_14D};
EInit D_us_80180518 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_GRANT_UNK_150};
EInit D_us_80180524 = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_FAKE_GRANT_UNK_14F};
EInit D_us_80180530 = {ANIMSET_DRA(14), 0x00, 0x79, PAL_UNK_2E4, ENEMY_FAKE_SYPHA_UNK_152};
EInit D_us_8018053C = {ANIMSET_DRA(14), 0x00, 0x79, PAL_UNK_2E9, ENEMY_FAKE_SYPHA_UNK_153};
EInit D_us_80180548 = {ANIMSET_OVL(5), 0x00, 0x57, PAL_UNK_2EF, ENEMY_FAKE_SYPHA_UNK_154};
EInit D_us_80180554 = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_210, ENEMY_FAKE_SYPHA_UNK_155};
// clang-format on
