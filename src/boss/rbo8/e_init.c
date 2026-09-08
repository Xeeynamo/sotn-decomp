// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo8.h"

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
void func_us_80195D80(Entity* self);
void func_us_80197B1C(Entity* self);
void func_us_801980E4(Entity* self);
void func_us_80198210(Entity* self);
void func_us_801983EC(Entity* self);
void func_us_8019C7B8_from_rcen(Entity* self);
void func_us_80198964(Entity* self);
void func_us_801991D4(Entity* self);
void EntityMinotaurSpitLiquid(Entity* self);
void func_us_8019921C(Entity* self);
void func_us_8019943C(Entity* self);
void func_us_8019953C(Entity* self);
void func_us_80199A58(Entity* self);
void EntityLifeUpSpawn(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,     EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay, EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,  EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop, EntityRelicOrb,          EntityPersistentItemDrop,
    EntityEnemyBlood,    EntityMessageBox,        EntityDummy,
    EntityDummy,         EntityBackgroundBlock,   EntityLockCamera,
    EntityUnkId13,       EntityExplosionVariants, EntityGreyPuff,
    func_us_80195D80,    func_us_80197B1C,        func_us_801980E4,
    func_us_80198210,    func_us_801983EC,        func_us_8019C7B8_from_rcen,
    func_us_80198964,    func_us_801991D4,        EntityMinotaurSpitLiquid,
    func_us_8019921C,    func_us_8019943C,        func_us_8019953C,
    func_us_80199A58,    EntityLifeUpSpawn,
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
EInit D_us_80180A68 = {ANIMSET_OVL(4), 0, 0, 0, 0x005};
EInit g_EInitGalamothLvl50 = {ANIMSET_OVL(1), 0, 72, 512, 0x0C6};
EInit g_EInitGalamothLvl0 = {ANIMSET_OVL(1), 0, 72, 512, 0x0C7};
EInit D_us_80180A8C = {ANIMSET_OVL(1), 0, 72, 512, 0x0C8};
EInit D_us_80180A98 = {ANIMSET_OVL(1), 0, 72, 512, 0x0C9};
EInit D_us_80180AA4 = {ANIMSET_OVL(2), 0, 76, 539, 0x002};
EInit D_us_80180AB0 = {ANIMSET_OVL(3), 0, 79, 539, 0x002};
// clang-format on
