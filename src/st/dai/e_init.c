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
void EntityBell(Entity* self);
void func_us_801C1EE4(Entity* self);
void func_us_801C2068(Entity* self);
void func_us_801C220C(Entity* self);
void EntityClouds(Entity* self);
void func_us_801C34FC(Entity* self);
void func_us_801C23A4(Entity* self);
void func_us_801C3164(Entity* self);
void EntityPriest(Entity* self);
void EntityPriestBlades(Entity* self);
void EntityPriestBladeDebris(Entity* self);
void EntityBellHelper(Entity* self);
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
void EntityWingedGuard(Entity* self);
void EntityWingedGuardParts(Entity* self);
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
void EntityWingedGuardSpawner(Entity* self);
void EntitySealedDoor(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
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
    EntityBell,
    func_us_801C1EE4,
    func_us_801C2068,
    func_us_801C220C,
    EntityClouds,
    func_us_801C34FC,
    func_us_801C23A4,
    func_us_801C3164,
    EntityPriest,
    EntityPriestBlades,
    EntityPriestBladeDebris,
    EntityBellHelper,
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
    EntityWingedGuard,
    EntityWingedGuardParts,
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
    EntityWingedGuardSpawner,
    EntitySealedDoor,
    OVL_EXPORT(EntityBreakableDebris),
    OVL_EXPORT(EntityCutscene),
    func_us_801C5920,
    func_us_801C5B88,
    EntityMistDoor,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 0};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 1};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 2};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 4};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 5};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 2};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 1};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 3};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 3};
EInit g_EInit_801809A4 = {ANIMSET_OVL(1), 43, 72, PAL_SKELERANG, 3}; // Unused
EInit D_us_801809B0 = {ANIMSET_OVL(1), 0, 0, PAL_NONE, 5};
EInit g_EInitPriest = {ANIMSET_OVL(2), 0, 72, PAL_UNK_C9, 5};
EInit g_EInit_801809C8 = {ANIMSET_OVL(2), 0, 72, PAL_UNK_CA, 5}; // Unused
EInit D_us_801809D4 = {ANIMSET_OVL(2), 37, 72, PAL_UNK_C9, 101};
EInit D_us_801809E0 = {ANIMSET_OVL(4), 0, 72, PAL_UNK_215, 180};
EInit D_us_801809EC = {ANIMSET_OVL(0), 0, 0, PAL_NONE, 181};
EInit g_EInitBonePillarHead = {ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 183};
EInit g_EInitBonePillarPieces = {ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 2};
EInit g_EInitBonePillarFireBreath = {
    ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 184};
EInit g_EInitBonePillarSpikeBall = {
    ANIMSET_OVL(5), 0, 73, PAL_BONE_PILLAR, 185};
EInit D_us_80180A28 = {ANIMSET_OVL(7), 1, 72, PAL_UNK_22A, 118};
EInit D_us_80180A34 = {ANIMSET_OVL(0), 0, 0, PAL_NONE, 119};
EInit g_EInitWingedGuard = {ANIMSET_OVL(8), 0, 75, PAL_WINGED_GUARD, 128};
EInit g_EInitWingedGuardParts = {ANIMSET_OVL(8), 0, 75, PAL_WINGED_GUARD, 3};
EInit g_EInitBat = {ANIMSET_OVL(9), 0, 74, PAL_BAT, 64};
EInit g_EInitBlueRaven = {ANIMSET_OVL(10), 0, 79, PAL_CROW, 114};
EInit g_EInitBlackCrow = {ANIMSET_OVL(10), 0, 79, PAL_CROW, 115};
EInit g_EInitSkelerang = {ANIMSET_OVL(11), 1, 72, PAL_SKELERANG, 11};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(11), 43, 72, PAL_SKELERANG, 12};
EInit D_us_80180A94 = {ANIMSET_OVL(12), 0, 84, PAL_UNK_232, 227};
EInit D_us_80180AA0 = {ANIMSET_OVL(13), 0, 81, PAL_UNK_234, 136};
EInit D_us_80180AAC = {ANIMSET_OVL(13), 0, 81, PAL_UNK_234, 2};
EInit D_us_80180AB8 = {ANIMSET_OVL(13), 0, 81, PAL_UNK_235, 137};
