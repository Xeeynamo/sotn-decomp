// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"

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
void func_us_8019AAFC(Entity* self);
void func_us_801ABD24(Entity* self);
void func_us_8019B5A4(Entity* self);
void func_us_8019B6D4(Entity* self);
void func_us_8019B8A8(Entity* self);
void func_us_8019C4EC(Entity* self);
void func_us_8019C610(Entity* self);
void func_us_8019C7B8(Entity* self);
void func_us_8019CDA0(Entity* self);
void func_us_8019CDF8(Entity* self);
void func_us_8019D330(Entity* self);
void OVL_EXPORT(EntityCutsceneDialogue)(Entity* self);
void func_us_8019F148(Entity* self);
void func_us_8019F5F0(Entity* self);
void func_us_8019FE9C(Entity* self);
void EntityUnkId1B(Entity* self);
void func_us_8019F9C0(Entity* self);
void func_us_801B4148_from_bo0(Entity* self);
void func_us_801C123C_from_no4(Entity* self);

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
    func_us_8019AAFC,
    func_us_801ABD24,
    func_us_8019B5A4,
    func_us_8019B6D4,
    func_us_8019B8A8,
    func_us_8019C4EC,
    func_us_8019C610,
    func_us_8019C7B8,
    func_us_8019CDA0,
    func_us_8019CDF8,
    func_us_8019D330,
    OVL_EXPORT(EntityCutsceneDialogue),
    func_us_8019F148,
    func_us_8019F5F0,
    func_us_8019FE9C,
    EntityUnkId1B,
    func_us_8019F9C0,
    func_us_801B4148_from_bo0,
    func_us_801C123C_from_no4,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0, 0, 0x000};
EInit OVL_EXPORT(EInitObtainable) = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit OVL_EXPORT(EInitParticle) = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit OVL_EXPORT(EInitSpawner) = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit OVL_EXPORT(EInitInteractable) = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit OVL_EXPORT(EInitUnkId13) = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit OVL_EXPORT(EInitLockCamera) = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit OVL_EXPORT(EInitCommon) = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit OVL_EXPORT(EInitDamageNum) = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitShaft = {ANIMSET_OVL(3), 0, 72, 512, 0x15F};
EInit D_us_80180570 = {ANIMSET_OVL(3), 0, 72, 512, 0x005};
EInit D_us_8018057C = {ANIMSET_OVL(3), 0, 72, 512, 0x160};
EInit D_us_80180588 = {ANIMSET_DRA(14), 0, 121, 736, 0x161};
EInit D_us_80180594 = {ANIMSET_DRA(0), 0, 0, 0, 0x162};
EInit D_us_801805A0 = {ANIMSET_OVL(12), 1, 72, 576, 0x005};
// clang-format on
