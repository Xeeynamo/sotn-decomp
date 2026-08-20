// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

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
void func_us_801AF280_from_lib(Entity* self);
void func_us_801AF538_from_lib(Entity* self);
void func_us_801AF7B8_from_lib(Entity* self);
void func_us_801AFA80_from_lib(Entity* self);
void func_us_801AE8E8_from_lib(Entity* self);
void func_us_801AE7AC_from_lib(Entity* self);
void func_us_801ADBE8(Entity* self);
void EntityHarpyKick(Entity* self);
void func_us_801AE414(Entity* self);
void func_us_801AE534(Entity* self);
void func_us_801AED4C(Entity* self);
void func_us_801D8D44_from_no4(Entity* self);
void func_us_801AEFE0(Entity* self);
void func_us_801AF11C(Entity* self);
void func_us_801AF448(Entity* self);
void func_us_801AF9E8(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void func_us_801AFC88(Entity* self);
void func_us_801AE84C_from_lib(Entity* self);
void func_us_801BAF60_from_lib(Entity* self);

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
    func_us_801AF280_from_lib,
    func_us_801AF538_from_lib,
    func_us_801AF7B8_from_lib,
    func_us_801AFA80_from_lib,
    func_us_801AE8E8_from_lib,
    func_us_801AE7AC_from_lib,
    func_us_801ADBE8,
    EntityHarpyKick,
    func_us_801AE414,
    func_us_801AE534,
    func_us_801AED4C,
    func_us_801D8D44_from_no4,
    func_us_801AEFE0,
    func_us_801AF11C,
    func_us_801AF448,
    func_us_801AF9E8,
    EntityExplosionPuffOpaque,
    func_us_801AFC88,
    func_us_801AE84C_from_lib,
    func_us_801BAF60_from_lib,
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
EInit g_EInitLion = {ANIMSET_OVL(3), 1, 80, 512, 0x106};
EInit D_us_8018064C = {ANIMSET_OVL(0), 0, 0, 0, 0x107};
EInit D_us_80180658 = {ANIMSET_OVL(3), 0, 80, 512, 0x002};
EInit g_EInitTinman = {ANIMSET_OVL(4), 1, 83, 518, 0x108};
EInit D_us_80180670 = {ANIMSET_OVL(4), 5, 83, 518, 0x109};
EInit D_us_8018067C = {ANIMSET_OVL(4), 0, 83, 518, 0x10A};
EInit D_us_80180688 = {ANIMSET_OVL(4), 0, 83, 518, 0x002};
EInit g_EInitScarecrow = {ANIMSET_OVL(5), 0, 84, 542, 0x142};
EInit D_us_801806A0 = {ANIMSET_OVL(5), 0, 84, 542, 0x005};
EInit g_EInitSchmoo = {ANIMSET_OVL(5), 8, 84, 539, 0x143};
EInit D_us_801806B8 = {ANIMSET_OVL(6), 0, 80, 527, 0x005};
// clang-format on
