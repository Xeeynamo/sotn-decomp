// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

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
void EntityBossTorch(Entity* self);
void EntityBossDoors(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityCoffin(Entity* self);
void OVL_EXPORT(EntityBoss)(Entity* self);
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
    EntityBossTorch,
    EntityBossDoors,
    EntityLifeUpSpawn,
    EntityCoffin,
    OVL_EXPORT(EntityBoss),
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
