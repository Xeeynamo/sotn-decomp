// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

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
void func_us_801923A8(Entity* self);
void func_us_80192C5C(Entity* self);
void func_us_80192F84(Entity* self);
void func_us_801936FC(Entity* self);
void func_us_80193C2C(Entity* self);
void func_us_80193E24(Entity* self);
void func_us_80194108(Entity* self);
void func_us_801947E4(Entity* self);
void func_us_80194C50(Entity* self);
void EntityBossRoomBlock(Entity* self);
void EntityLifeUpSpawn(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,     EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay, EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,  EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop, EntityRelicOrb,          EntityPersistentItemDrop,
    EntityEnemyBlood,    EntityMessageBox,        EntityDummy,
    EntityDummy,         EntityBackgroundBlock,   EntityLockCamera,
    EntityUnkId13,       EntityExplosionVariants, EntityGreyPuff,
    func_us_801923A8,    func_us_80192C5C,        func_us_80192F84,
    func_us_801936FC,    func_us_80193C2C,        func_us_80193E24,
    func_us_80194108,    func_us_801947E4,        func_us_80194C50,
    EntityBossRoomBlock, EntityLifeUpSpawn,
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
EInit g_EInitBeezelbub = {ANIMSET_OVL(3), 0, 72, 512, 0x144};
EInit g_EInitBeezelbub801804A0 = {ANIMSET_OVL(3), 0, 72, 512, 0x144};
EInit D_us_801804AC = {ANIMSET_OVL(3), 0, 72, 512, 0x145};
EInit D_us_801804B8 = {ANIMSET_OVL(3), 0, 72, 512, 0x146};
EInit D_us_801804C4 = {ANIMSET_OVL(3), 0, 72, 512, 0x005};
EInit D_us_801804D0 = {ANIMSET_OVL(3), 0, 72, 512, 0x002};
EInit D_us_801804DC = {ANIMSET_OVL(1), 8, 0, 0, 0x005};
// clang-format on
