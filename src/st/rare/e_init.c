// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

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
void EntityMinotaur(Entity* self);
void EntityMinotaurAttackHitbox(Entity* self);
void EntityMinotaurFireball(Entity* self);
void EntityMinotaurSpitLiquid(Entity* self);
void EntityWerewolf(Entity* self);
void EntityWerewolfAttackHitbox(Entity* self);
void EntityWerewolfEnergyWave(Entity* self);
void EntityWerewolfSpinAttackAfterImage(Entity* self);
void EntityWerewolfDeathFlames(Entity* self);
void EntityMinotaurDeathPuff(Entity* self);
void EntityAzaghal(Entity* self);
void EntityAzaghalSwordHitbox(Entity* self);
void EntityBreakableFloorSecret(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void EntityBackgroundDoorRubble(Entity* self);
void EntityFountainWater(Entity* self);
void EntityBossTorch(Entity* self);
void EntityBossDoors(Entity* self);
void EntityWhiteDragon(Entity* self);
void EntityWhiteDragonFlameBreath(Entity* self);
void EntityStoneSkull(Entity* self);

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
    EntityMinotaur,
    EntityMinotaurAttackHitbox,
    EntityMinotaurFireball,
    EntityMinotaurSpitLiquid,
    EntityWerewolf,
    EntityWerewolfAttackHitbox,
    EntityWerewolfEnergyWave,
    EntityWerewolfSpinAttackAfterImage,
    EntityWerewolfDeathFlames,
    EntityMinotaurDeathPuff,
    EntityAzaghal,
    EntityAzaghalSwordHitbox,
    EntityBreakableFloorSecret,
    OVL_EXPORT(EntityBreakableDebris),
    EntityBackgroundDoorRubble,
    EntityFountainWater,
    EntityBossTorch,
    EntityBossDoors,
    EntityWhiteDragon,
    EntityWhiteDragonFlameBreath,
    EntityStoneSkull,
};

// animSet, animCurFrame, unk5A, palette, enemyID
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};

EInit g_EInitEnvironmentBreakable = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0, 0, 0, 0x005};

EInit g_EInitMinotaur = {ANIMSET_OVL(3), 1, 72, 0x200, 0x182};
EInit g_EInitMinotaurAttackHitbox = {ANIMSET_OVL(3), 0, 72, 0x200, 0x183};
EInit g_EInitMinotaurFireball = {ANIMSET_DRA(2), 1, 0, 0, 0x002};
EInit g_EInitMinotaurSpitLiquid = {ANIMSET_DRA(2), 1, 0, 0, 0x184};

EInit g_EInitWerewolf = {ANIMSET_OVL(4), 1, 80, 0x229, 0x185};
EInit g_EInitWerewolfAttackHitbox = {ANIMSET_OVL(4), 0, 80, 0x229, 0x186};
EInit g_EInitWerewolfEnergyWave = {ANIMSET_OVL(4), 54, 80, 0x229, 0x187};

EInit g_EInitAzaghal = {ANIMSET_OVL(0), 0, 0, 0, 0x0E0};

// nb. Main White Dragon entity uses a g_EInitSpawner to initialise
EInit g_EInitWhiteDragonFlameBreath = {ANIMSET_DRA(14), 0, 121, 0x2E2, 0x02C};

EInit g_EInitStoneSkull = {ANIMSET_OVL(7), 0, 73, 0x228, 0x180};
