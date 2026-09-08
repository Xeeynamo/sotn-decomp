// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo7.h"

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
void EntityDemonSwitchWall(Entity* self);
void EntityDemonSwitch(Entity* self);
void EntityBreakableWall(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityCerberusGateDebug(Entity* self);
void func_us_80194D3C(Entity* self);
void func_us_801959E0(Entity* self);
void func_us_80195AF0(Entity* self);
void func_us_80195C50(Entity* self);
void func_us_801963D8(Entity* self);
void EntityLifeUpSpawn(Entity* self);

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
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    EntityBreakableDebris,
    EntityCerberusGateDebug,
    func_us_80194D3C,
    func_us_801959E0,
    func_us_80195AF0,
    func_us_80195C50,
    func_us_801963D8,
    EntityLifeUpSpawn,
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
EInit D_us_80180454 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitCerberos = {ANIMSET_OVL(2), 0, 72, 512, 0x16B};
EInit D_us_8018046C = {ANIMSET_OVL(2), 0, 72, 512, 0x16C};
EInit D_us_80180478 = {ANIMSET_DRA(14), 0, 121, 736, 0x16D};
// clang-format on
