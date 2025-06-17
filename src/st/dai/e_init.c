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
void EntityFishheadFireBreath(Entity* self);
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
    EntityFishheadFireBreath,
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

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, PAL_DRA(0), 0};

#include "../e_init_common.h"

// Unused, not in psp
EInit g_EInit_801809A4 = {ANIMSET_OVL(1), 43, 72, PAL_DRA(512), 3};
EInit D_us_801809B0 = {ANIMSET_OVL(1), 0, 0, PAL_DRA(0), 5};
EInit D_us_801809BC = {ANIMSET_OVL(2), 0, 72, PAL_DRA(201), 5};
// Unused, not in psp
EInit g_EInit_801809C8 = {ANIMSET_OVL(2), 0, 72, PAL_DRA(202), 5};
EInit D_us_801809D4 = {ANIMSET_OVL(2), 37, 72, PAL_DRA(201), 101};
EInit D_us_801809E0 = {ANIMSET_OVL(4), 0, 72, PAL_DRA(533), 180};
EInit D_us_801809EC = {ANIMSET_OVL(0), 0, 0, PAL_DRA(0), 181};
EInit D_us_801809F8 = {ANIMSET_OVL(5), 0, 73, PAL_DRA(534), 183};
EInit D_us_80180A04 = {ANIMSET_OVL(5), 0, 73, PAL_DRA(534), 2};
EInit D_us_80180A10 = {ANIMSET_OVL(5), 0, 73, PAL_DRA(534), 184};
EInit D_us_80180A1C = {ANIMSET_OVL(5), 0, 73, PAL_DRA(534), 185};
EInit D_us_80180A28 = {ANIMSET_OVL(7), 1, 72, PAL_DRA(554), 118};
EInit D_us_80180A34 = {ANIMSET_OVL(0), 0, 0, PAL_DRA(0), 119};
EInit D_us_80180A40 = {ANIMSET_OVL(8), 0, 75, PAL_DRA(555), 128};
EInit D_us_80180A4C = {ANIMSET_OVL(8), 0, 75, PAL_DRA(555), 3};
EInit D_us_80180A58 = {ANIMSET_OVL(9), 0, 74, PAL_DRA(556), 64};
EInit D_us_80180A64 = {ANIMSET_OVL(10), 0, 79, PAL_DRA(559), 114};
EInit D_us_80180A70 = {ANIMSET_OVL(10), 0, 79, PAL_DRA(559), 115};
EInit D_us_80180A7C = {ANIMSET_OVL(11), 1, 72, PAL_DRA(512), 11};
EInit D_us_80180A88 = {ANIMSET_OVL(11), 43, 72, PAL_DRA(512), 12};
EInit D_us_80180A94 = {ANIMSET_OVL(12), 0, 84, PAL_DRA(562), 227};
EInit D_us_80180AA0 = {ANIMSET_OVL(13), 0, 81, PAL_DRA(564), 136};
EInit D_us_80180AAC = {ANIMSET_OVL(13), 0, 81, PAL_DRA(564), 2};
EInit D_us_80180AB8 = {ANIMSET_OVL(13), 0, 81, PAL_DRA(565), 137};
