// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo7.h"

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
void func_us_801BAB18_from_bo0(Entity* self);
void func_us_80192B38_from_rbo3(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void func_us_801940B4(Entity* self);
void func_us_801957C0(Entity* self);
void EntityHarpyKick(Entity* self);
void func_us_80195A8C(Entity* self);
void func_us_80195D04(Entity* self);
void EntityCtulhuDeath(Entity* self);

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
    func_us_801BAB18_from_bo0,
    func_us_80192B38_from_rbo3,
    EntityLifeUpSpawn,
    func_us_801940B4,
    func_us_801957C0,
    EntityHarpyKick,
    func_us_80195A8C,
    func_us_80195D04,
    EntityCtulhuDeath,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitUnused80180420 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit D_us_8018042C = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit g_EInitAkmodanII = {ANIMSET_OVL(8), 1, 72, 570, 0x10B};
EInit D_us_80180444 = {ANIMSET_OVL(8), 0, 72, 570, 0x10C};
EInit D_us_80180450 = {ANIMSET_OVL(10), 1, 78, 359, 0x10D};
// clang-format on
