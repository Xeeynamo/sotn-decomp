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
void func_us_801B1BC8(Entity* self);
void func_us_801B2800(Entity* self);
void func_us_801B28F4(Entity* self);
void func_us_801B29E0(Entity* self);
void func_us_801B7290(Entity* self);
void EntityCornerGuardAttack(Entity* self);
void func_us_801B7FF8(Entity* self);
void func_us_801B80E8(Entity* self);
void func_us_801B81CC(Entity* self);
void func_us_801B2B2C(Entity* self);
void func_us_801B3B34(Entity* self);
void func_us_801B4E9C(Entity* self);
void EntityBreakableCeilingSecret(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void EntityBackgroundDoorRubble(Entity* self);
void EntityFountainWater(Entity* self);
void EntityBossTorch(Entity* self);
void EntityBossDoors(Entity* self);
void func_us_801B5448(Entity* self);
void func_us_801B65F8(Entity* self);
void func_us_801B6824(Entity* self);

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
    func_us_801B1BC8,
    func_us_801B2800,
    func_us_801B28F4,
    func_us_801B29E0,
    func_us_801B7290,
    EntityCornerGuardAttack,
    func_us_801B7FF8,
    func_us_801B80E8,
    func_us_801B81CC,
    func_us_801B2B2C,
    func_us_801B3B34,
    func_us_801B4E9C,
    EntityBreakableCeilingSecret,
    OVL_EXPORT(EntityBreakableDebris),
    EntityBackgroundDoorRubble,
    EntityFountainWater,
    EntityBossTorch,
    EntityBossDoors,
    func_us_801B5448,
    func_us_801B65F8,
    func_us_801B6824,
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

EInit D_us_80180778 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0, 0, 0, 0x005};

EInit g_EInitMinotaur = {ANIMSET_OVL(3), 1, 72, 0x200, 0x182};
EInit D_us_8018079C = {ANIMSET_OVL(3), 0, 72, 0x200, 0x183};
EInit D_us_801807A8 = {ANIMSET_DRA(2), 1, 0, 0, 0x002};
EInit D_us_801807B4 = {ANIMSET_DRA(2), 1, 0, 0, 0x184};

EInit g_EInitWerewolfRARE = {ANIMSET_OVL(4), 1, 80, 0x229, 0x185};
EInit D_us_801807CC = {ANIMSET_OVL(4), 0, 80, 0x229, 0x186};
EInit D_us_801807D8 = {ANIMSET_OVL(4), 54, 80, 0x229, 0x187};

EInit g_EInitAzaghal = {ANIMSET_OVL(0), 0, 0, 0, 0x0E0};
EInit D_us_801807F0 = {ANIMSET_DRA(14), 0, 121, 0x2E2, 0x02C};

EInit g_EInitStoneSkull = {ANIMSET_OVL(7), 0, 73, 0x228, 0x180};
