// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

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
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_801BA388_from_cat(Entity* self);
void func_us_801BA164_from_cat(Entity* self);
void func_us_801A1878(Entity* self);
void func_us_801A2F2C(Entity* self);
void func_us_801A3480(Entity* self);
void func_us_801A38EC(Entity* self);
void func_us_801A2774(Entity* self);
void func_us_801A2BC4(Entity* self);
void func_us_801A2CC4(Entity* self);
void func_us_801A2D90(Entity* self);
void func_us_801A4394(Entity* self);
void func_us_801A45D0(Entity* self);
void func_us_801A518C(Entity* self);
void func_us_801A493C(Entity* self);
void func_us_801A4AF4(Entity* self);
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
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801BA388_from_cat,
    func_us_801BA164_from_cat,
    func_us_801A1878,
    func_us_801A2F2C,
    func_us_801A3480,
    func_us_801A38EC,
    func_us_801A2774,
    func_us_801A2BC4,
    func_us_801A2CC4,
    func_us_801A2D90,
    func_us_801A4394,
    func_us_801A45D0,
    func_us_801A518C,
    func_us_801A493C,
    func_us_801A4AF4,
    EntityLifeUpSpawn,
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
EInit D_us_80180AF8 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitUnused80180B04 = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitGranfaloon1 = {ANIMSET_OVL(3), 0, 72, 512, 0x127};
EInit D_us_80180B1C = {ANIMSET_OVL(3), 0, 72, 512, 0x005};
EInit D_us_80180B28 = {ANIMSET_OVL(3), 0, 72, 512, 0x12A};
EInit D_us_80180B34 = {ANIMSET_DRA(0), 0, 0, 0, 0x12A};
EInit g_EInitGranfaloon2 = {ANIMSET_OVL(3), 0, 72, 512, 0x128};
EInit D_us_80180B4C = {ANIMSET_OVL(3), 0, 72, 512, 0x005};
EInit D_us_80180B58 = {ANIMSET_OVL(3), 0, 72, 512, 0x129};
// clang-format on
