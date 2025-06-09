// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

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
void func_us_801C0BA4(Entity* self);
void func_us_801D97D0(Entity* self);
void func_us_801D9F5C(Entity* self);
void func_us_801C0F8C(Entity* self);
void func_us_801C1184(Entity* self);
void func_us_801C1298(Entity* self);
void func_us_801C1EE4(Entity* self);
void func_us_801C2068(Entity* self);
void func_us_801C220C(Entity* self);
void EntityClouds(Entity* self);
void func_us_801C34FC(Entity* self);
void func_us_801C23A4(Entity* self);
void func_us_801C3164(Entity* self);
void func_us_801C2534(Entity* self);
void func_us_801C2CD4(Entity* self);
void func_us_801C2FF0(Entity* self);
void func_us_801C1E18(Entity* self);
void func_us_801D1204(Entity* self);
void func_us_801D1C24(Entity* self);
void func_us_801D1D00(Entity* self);
void func_us_801D2908(Entity* self);
void func_us_801D2CFC(Entity* self);
void func_us_801D2444(Entity* self);
void func_us_801C3644(Entity* self);
void func_us_801C3D44(Entity* self);
void func_us_801C3850(Entity* self);
void func_us_801C379C(Entity* self);
void func_us_801C3ED8(Entity* self);
void func_us_801D2FA4(Entity* self);
void func_us_801D36EC(Entity* self);
void EntitySkeletonPieces(Entity* self);
void func_us_801D37C4(Entity* self);
void func_us_801D3A40(Entity* self);
void EntityBat(Entity* self);
void func_us_801D3FD8(Entity* self);
void func_us_801D43BC(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_us_801D56F4(Entity* self);
void func_us_801D636C(Entity* self);
void func_us_801D64A0(Entity* self);
void func_us_801D6FC8(Entity* self);
void func_us_801D70A0(Entity* self);
void func_us_801D3BD4(Entity* self);
void EntitySealedDoor(Entity* self);
void func_801A8328(Entity* self);
void OVL_EXPORT(EntityCutscene)(Entity* self);
void func_us_801C5920(Entity* self);
void func_us_801C5B88(Entity* self);
void EntityMistDoor(Entity* self);

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
    func_us_801C0BA4,
    func_us_801D97D0,
    func_us_801D9F5C,
    func_us_801C0F8C,
    func_us_801C1184,
    func_us_801C1298,
    func_us_801C1EE4,
    func_us_801C2068,
    func_us_801C220C,
    EntityClouds,
    func_us_801C34FC,
    func_us_801C23A4,
    func_us_801C3164,
    func_us_801C2534,
    func_us_801C2CD4,
    func_us_801C2FF0,
    func_us_801C1E18,
    func_us_801D1204,
    func_us_801D1C24,
    func_us_801D1D00,
    func_us_801D2908,
    func_us_801D2CFC,
    func_us_801D2444,
    func_us_801C3644,
    func_us_801C3D44,
    func_us_801C3850,
    func_us_801C379C,
    func_us_801C3ED8,
    func_us_801D2FA4,
    func_us_801D36EC,
    EntitySkeletonPieces,
    func_us_801D37C4,
    func_us_801D3A40,
    EntityBat,
    func_us_801D3FD8,
    func_us_801D43BC,
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    func_us_801D56F4,
    func_us_801D636C,
    func_us_801D64A0,
    func_us_801D6FC8,
    func_us_801D70A0,
    func_us_801D3BD4,
    EntitySealedDoor,
    func_801A8328,
    OVL_EXPORT(EntityCutscene),
    func_us_801C5920,
    func_us_801C5B88,
    EntityMistDoor,
};
