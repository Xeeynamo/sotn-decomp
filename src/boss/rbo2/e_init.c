// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"

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
void func_us_8019B52C(Entity* self);
void func_us_8019C718(Entity* self);
void func_us_8019C924(Entity* self);
void func_us_8019D4CC(Entity* self);
void func_us_8019D950(Entity* self);
void func_us_8019DA04(Entity* self);
void func_us_8019E558(Entity* self);
void func_us_8019E920(Entity* self);
void func_us_8019ECCC(Entity* self);
void func_us_8019F260(Entity* self);
void func_us_8019F4AC(Entity* self);
void EntityCerberusGateDebug(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityCutsceneDialogue(Entity* self);
void func_us_801A17C8(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,     EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay, EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,  EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop, EntityRelicOrb,          EntityPersistentItemDrop,
    EntityEnemyBlood,    EntityMessageBox,        EntityDummy,
    EntityDummy,         EntityBackgroundBlock,   EntityLockCamera,
    EntityUnkId13,       EntityExplosionVariants, EntityGreyPuff,
    func_us_8019B52C,    func_us_8019C718,        func_us_8019C924,
    func_us_8019D4CC,    func_us_8019D950,        func_us_8019DA04,
    func_us_8019E558,    func_us_8019E920,        func_us_8019ECCC,
    func_us_8019F260,    func_us_8019F4AC,        EntityCerberusGateDebug,
    EntityLifeUpSpawn,   EntityCutsceneDialogue,  func_us_801A17C8,
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
EInit g_EInitDeath1 = {ANIMSET_OVL(3), 0, 72, 512, 0x164};
EInit D_us_801804A0 = {ANIMSET_OVL(3), 0, 72, 512, 0x165};
EInit D_us_801804AC = {ANIMSET_OVL(3), 0, 72, 512, 0x166};
EInit D_us_801804B8 = {ANIMSET_OVL(3), 0, 72, 512, 0x167};
EInit D_us_801804C4 = {ANIMSET_OVL(3), 0, 72, 512, 0x002};
EInit g_EInitDeath2 = {ANIMSET_OVL(4), 0, 80, 525, 0x169};
EInit D_us_801804DC = {ANIMSET_OVL(4), 0, 80, 525, 0x002};
EInit D_us_801804E8 = {ANIMSET_OVL(4), 0, 80, 525, 0x16A};
EInit D_us_801804F4 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitUnused80180500 = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
// clang-format on
