// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

// This file should not be used, it exists only to provide correlation with
// no2/e_init.c until those symbols are mapped and the files can be merged.
void EntityUnkBreakable(Entity* self);
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
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_pspeu_092575D8(Entity* self);
void func_pspeu_09257810(Entity* self);
void func_pspeu_09257B10(Entity* self);
void func_pspeu_09257B78(Entity* self);
void func_pspeu_09257C00(Entity* self);
void func_pspeu_09259E40(Entity* self);
void func_pspeu_09259D40(Entity* self);
void func_pspeu_0925A248(Entity* self);
void func_us_801C3D44(Entity* self);
void func_pspeu_0925BBA8(Entity* self);
void func_us_801C379C(Entity* self);
void func_pspeu_092556A0(Entity* self);
void func_pspeu_09256348(Entity* self);
void func_pspeu_09255EF0(Entity* self);
void func_pspeu_092441F8(Entity* self);
void func_pspeu_0925A988(Entity* self);
void func_pspeu_09248B38(Entity* self);
void func_pspeu_09246ED0(Entity* self);
void func_pspeu_0924A940(Entity* self);
void EntityFrozenShadeCrystal(Entity* self);
void func_pspeu_09238E80(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void func_pspeu_0925B730(Entity* self);
void func_us_801C3ED8(Entity* self);
void func_pspeu_0925B278(Entity* self);
void func_pspeu_09257ED8(Entity* self);
void func_pspeu_0923D188(Entity* self);
void func_pspeu_0923DCC0(Entity* self);
void func_pspeu_0923DE98(Entity* self);
void func_pspeu_09253010(Entity* self);
void func_pspeu_09254098(Entity* self);
void func_pspeu_09254520(Entity* self);
void func_pspeu_092515D0(Entity* self);
void func_pspeu_092529B0(Entity* self);
void func_pspeu_0924F990(Entity* self);
void func_pspeu_09250ED0(Entity* self);
void func_pspeu_0924AB98(Entity* self);
void func_us_801D6FC8(Entity* self);
void func_pspeu_0924BF68(Entity* self);
void func_801A8328(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityUnkBreakable,
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
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    func_pspeu_092575D8,
    func_pspeu_09257810,
    func_pspeu_09257B10,
    func_pspeu_09257B78,
    func_pspeu_09257C00,
    func_pspeu_09259E40,
    func_pspeu_09259D40,
    func_pspeu_0925A248,
    func_us_801C3D44,
    func_pspeu_0925BBA8,
    func_us_801C379C,
    func_pspeu_092556A0,
    func_pspeu_09256348,
    func_pspeu_09255EF0,
    func_pspeu_092441F8,
    func_pspeu_0925A988,
    func_pspeu_09248B38,
    func_pspeu_09246ED0,
    func_pspeu_0924A940,
    EntityFrozenShadeCrystal,
    func_pspeu_09238E80,
    EntityBloodDrips,
    EntityBloodSplatter,
    func_pspeu_0925B730,
    func_us_801C3ED8,
    func_pspeu_0925B278,
    func_pspeu_09257ED8,
    func_pspeu_0923D188,
    func_pspeu_0923DCC0,
    func_pspeu_0923DE98,
    func_pspeu_09253010,
    func_pspeu_09254098,
    func_pspeu_09254520,
    func_pspeu_092515D0,
    func_pspeu_092529B0,
    func_pspeu_0924F990,
    func_pspeu_09250ED0,
    func_pspeu_0924AB98,
    func_us_801D6FC8,
    func_pspeu_0924BF68,
    func_801A8328,
};
