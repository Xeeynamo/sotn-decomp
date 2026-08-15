// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

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
void EntityDummy(Entity* self);
void EntitySplashWater(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityWaterDrop(Entity* self);
void func_us_801C12B0_from_no4(Entity* self);
void func_us_801C15F8_from_no4(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void func_us_801A07CC(Entity* self);
void func_us_801A0A80(Entity* self);
void func_us_801A1120(Entity* self);
void func_us_801A16E4(Entity* self);
void func_us_801A2AEC(Entity* self);
void func_us_801A3CD8(Entity* self);
void func_us_801A365C(Entity* self);
void func_us_801A3EE0(Entity* self);
void func_us_801A42A8(Entity* self);
void func_us_801A4680(Entity* self);
void func_us_801A4988(Entity* self);
void func_us_801A4C0C(Entity* self);
void func_us_801A4E24(Entity* self);
void func_us_801A5338(Entity* self);
void func_us_801A57A4(Entity* self);
void func_us_801A5948(Entity* self);
void func_us_801A5F0C(Entity* self);
void func_us_801A1BE8(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void func_us_801A6370(Entity* self);
void func_us_801A6568(Entity* self);
void func_us_801C123C_from_no4(Entity* self);

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
    EntityDummy,
    EntitySplashWater,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityWaterDrop,
    func_us_801C12B0_from_no4,
    func_us_801C15F8_from_no4,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    func_us_801A07CC,
    func_us_801A0A80,
    func_us_801A1120,
    func_us_801A16E4,
    func_us_801A2AEC,
    func_us_801A3CD8,
    func_us_801A365C,
    func_us_801A3EE0,
    func_us_801A42A8,
    func_us_801A4680,
    func_us_801A4988,
    func_us_801A4C0C,
    func_us_801A4E24,
    func_us_801A5338,
    func_us_801A57A4,
    func_us_801A5948,
    func_us_801A5F0C,
    func_us_801A1BE8,
    EntityBreakableWallDebris,
    EntityLifeUpSpawn,
    func_us_801A6370,
    func_us_801A6568,
    func_us_801C123C_from_no4,
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
EInit g_EInitScylla = {ANIMSET_OVL(2), 0, 72, 512, 0x11F};
EInit D_us_801805AC = {ANIMSET_OVL(2), 0, 72, 512, 0x120};
EInit D_us_801805B8 = {ANIMSET_OVL(2), 0, 72, 512, 0x005};
EInit D_us_801805C4 = {ANIMSET_OVL(2), 0, 72, 512, 0x121};
EInit D_us_801805D0 = {ANIMSET_OVL(2), 0, 72, 512, 0x122};
EInit D_us_801805DC = {ANIMSET_OVL(2), 0, 72, 512, 0x124};
EInit D_us_801805E8 = {ANIMSET_OVL(2), 0, 72, 512, 0x125};
EInit D_us_801805F4 = {ANIMSET_OVL(2), 0, 72, 512, 0x002};
EInit g_EInitScyllawyrm = {ANIMSET_OVL(2), 0, 72, 512, 0x126};
// clang-format on
