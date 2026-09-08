// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

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
void func_us_8019D330_from_rcen(Entity* self);
void func_us_8019DB9C(Entity* self);
void func_us_8019FBC0(Entity* self);
void func_us_8019FB04(Entity* self);
void func_us_8019EADC(Entity* self);
void func_us_8019EE30(Entity* self);
void func_us_8019F1CC(Entity* self);
void func_us_8019FA78(Entity* self);
void func_us_8019FCB4(Entity* self);
void func_us_801A01A4(Entity* self);
void func_us_801A0710(Entity* self);
void func_us_801A0860(Entity* self);
void func_us_801A0AB4(Entity* self);
void func_us_801A0DC0(Entity* self);
void func_us_801A11DC(Entity* self);
void func_us_801A1B38(Entity* self);
void func_us_801A1150(Entity* self);
void func_us_801A362C(Entity* self);
void func_us_801A367C(Entity* self);
void func_us_801A9208_from_bo6(Entity* self);
void func_us_801A37B4(Entity* self);
void func_us_801A399C(Entity* self);
void func_us_801A3BE0(Entity* self);
void func_us_801A4028(Entity* self);
void EntityBackgroundVortex(Entity* self);
void func_us_801B1738(Entity* self);
void func_us_801B2864(Entity* self);
void func_us_801A4594(Entity* self);
void func_us_801A4F14(Entity* self);

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
    func_us_8019D330_from_rcen,
    func_us_8019DB9C,
    func_us_8019FBC0,
    func_us_8019FB04,
    func_us_8019EADC,
    func_us_8019EE30,
    func_us_8019F1CC,
    func_us_8019FA78,
    func_us_8019FCB4,
    func_us_801A01A4,
    func_us_801A0710,
    func_us_801A0860,
    func_us_801A0AB4,
    func_us_801A0DC0,
    func_us_801A11DC,
    func_us_801A1B38,
    func_us_801A1150,
    func_us_801A362C,
    func_us_801A367C,
    func_us_801A9208_from_bo6,
    func_us_801A37B4,
    func_us_801A399C,
    func_us_801A3BE0,
    func_us_801A4028,
    EntityBackgroundVortex,
    func_us_801B1738,
    func_us_801B2864,
    func_us_801A4594,
    func_us_801A4F14,
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
EInit g_EInitDraculaLvl98 = {ANIMSET_OVL(1), 0, 72, 512, 0x17B};
EInit D_us_80180540 = {ANIMSET_OVL(1), 0, 72, 512, 0x005};
EInit D_us_8018054C = {ANIMSET_OVL(1), 0, 72, 512, 0x17D};
EInit D_us_80180558 = {ANIMSET_OVL(1), 0, 72, 512, 0x17C};
EInit D_us_80180564 = {ANIMSET_OVL(1), 0, 72, 512, 0x17E};
EInit D_us_80180570 = {ANIMSET_OVL(1), 0, 72, 512, 0x17F};
// clang-format on
