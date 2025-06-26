// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

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
void EntityBonePillarHead(Entity* self);
void EntityBonePillarFireBreath(Entity* self);
void EntityBonePillarDeathParts(Entity* self);
void EntityBonePillarSpikeBall(Entity* self);
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
void EntityBlackCrow(Entity* self);
void EntityBlueRaven(Entity* self);
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
void EntityBreakableDebris(Entity* self);
void OVL_EXPORT(EntityCutscene)(Entity* self);
void func_us_801C5920(Entity* self);
void func_us_801C5B88(Entity* self);
void EntityMistDoor(Entity* self);

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
    EntityBonePillarHead,
    EntityBonePillarFireBreath,
    EntityBonePillarDeathParts,
    EntityBonePillarSpikeBall,
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
    EntityBlackCrow,
    EntityBlueRaven,
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
    EntityBreakableDebris,
    OVL_EXPORT(EntityCutscene),
    func_us_801C5920,
    func_us_801C5B88,
    EntityMistDoor,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 0};

#include "../e_init_common.h"

// Unused, not in psp
EInit g_EInit_801809A4 = {ANIMSET_OVL(1), 43, 72, PAL_SKELERANG, 3};
EInit D_us_801809B0 = {ANIMSET_OVL(1), 0, 0, PAL_NONE, 5};
EInit D_us_801809BC = {ANIMSET_OVL(2), 0, 72, PAL_UNKC9, 5};
// Unused, not in psp
EInit g_EInit_801809C8 = {ANIMSET_OVL(2), 0, 72, PAL_UNKCA, 5};
EInit D_us_801809D4 = {ANIMSET_OVL(2), 37, 72, PAL_UNKC9, 101};
EInit D_us_801809E0 = {ANIMSET_OVL(4), 0, 72, PAL_UNK215, 180};
EInit D_us_801809EC = {ANIMSET_OVL(0), 0, 0, PAL_NONE, 181};
EInit g_EInitBonePillarHead = {ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 183};
EInit g_EInitBonePillarPieces = {ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 2};
EInit g_EInitBonePillarFireBreath = {
    ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 184};
EInit g_EInitBonePillarSpikeBall = {
    ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 185};
EInit D_us_80180A28 = {ANIMSET_OVL(7), 1, 72, PAL_UNK22A, 118};
EInit D_us_80180A34 = {ANIMSET_OVL(0), 0, 0, PAL_NONE, 119};
EInit D_us_80180A40 = {ANIMSET_OVL(8), 0, 75, PAL_UNK22B, 128};
EInit D_us_80180A4C = {ANIMSET_OVL(8), 0, 75, PAL_UNK22B, 3};
EInit g_EInitBat = {ANIMSET_OVL(9), 0, 74, PAL_BAT, 64};
EInit g_EInitBlueRaven = {ANIMSET_OVL(10), 0, 79, PAL_UNK22F, 114};
EInit g_EInitBlackCrow = {ANIMSET_OVL(10), 0, 79, PAL_UNK22F, 115};
EInit g_EInitSkelerang = {ANIMSET_OVL(11), 1, 72, PAL_SKELERANG, 11};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(11), 43, 72, PAL_SKELERANG, 12};
EInit D_us_80180A94 = {ANIMSET_OVL(12), 0, 84, PAL_UNK232, 227};
EInit D_us_80180AA0 = {ANIMSET_OVL(13), 0, 81, PAL_UNK234, 136};
EInit D_us_80180AAC = {ANIMSET_OVL(13), 0, 81, PAL_UNK234, 2};
EInit D_us_80180AB8 = {ANIMSET_OVL(13), 0, 81, PAL_UNK235, 137};
