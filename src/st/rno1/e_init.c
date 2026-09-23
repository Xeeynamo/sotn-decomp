// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

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
void EntityFog(Entity* self);
void EntityRain(Entity* self);
void EntityFadeRainSound(Entity* self);
void EntityParanthropus(Entity* self);
void EntityParanthropusBoneHitbox(Entity* self);
void EntityParanthropusSkull(Entity* self);
void EntityParanthropusThrownBone(Entity* self);
void EntityStoneSkull(Entity* self);
void EntityJackOBones(Entity* self);
void EntityJackOBonesDeathParts(Entity* self);
void EntityJackOBonesJack(Entity* self);
void EntityNovaSkeleton(Entity* self);
void EntityNovaLaser(Entity* self);
void EntityNovaLaserPulse(Entity* self);
void EntityNovaSkeletonDeathParts(Entity* self);
void EntityElevatorMachine(Entity* self);
void EntitySecretElevatorWall(Entity* self);
void EntityBreakableWallSegment(Entity* self);
void EntityWallParticles(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntitySecretElevator(Entity* self);
void EntityBreakableDebris(Entity* self);
void func_us_801A9BEC(Entity* self);
void func_us_801B9028_from_no1(Entity* self);
void func_us_80198A18_from_rbo4(Entity* self);
void func_us_801A9A8C(Entity* self);

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
    EntityFog,
    EntityRain,
    EntityFadeRainSound,
    EntityParanthropus,
    EntityParanthropusBoneHitbox,
    EntityParanthropusSkull,
    EntityParanthropusThrownBone,
    EntityStoneSkull,
    EntityJackOBones,
    EntityJackOBonesDeathParts,
    EntityJackOBonesJack,
    EntityNovaSkeleton,
    EntityNovaLaser,
    EntityNovaLaserPulse,
    EntityNovaSkeletonDeathParts,
    EntityElevatorMachine,
    EntitySecretElevatorWall,
    EntityBreakableWallSegment,
    EntityWallParticles,
    EntityBreakableWallDebris,
    EntitySecretElevator,
    EntityBreakableDebris,
    func_us_801A9BEC,
    func_us_801B9028_from_no1,
    func_us_80198A18_from_rbo4,
    func_us_801A9A8C,
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
EInit g_EInitParanthropus = {ANIMSET_OVL(3), 1, 76, 512, 0x0D3};
EInit g_EInitParanthropusBoneHitbox = {ANIMSET_OVL(0), 0, 0, 0, 0x0D4};
EInit g_EInitParanthropusThrownBone = {ANIMSET_OVL(3), 54, 76, 512, 0x0D5};
EInit g_EInitStoneSkull = {ANIMSET_OVL(4), 0, 78, 515, 0x180};
EInit g_EInitJackOBones = {ANIMSET_OVL(5), 1, 74, 524, 0x074};
EInit g_EInitJackOBones2 = {ANIMSET_OVL(5), 0, 74, 524, 0x002};
EInit g_EInitJackOBones3 = {ANIMSET_OVL(5), 21, 74, 524, 0x075};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(6), 1, 72, 532, 0x07E};
EInit g_EInitNovaSkeleton2 = {ANIMSET_OVL(6), 0, 72, 532, 0x07F};
EInit g_EInitElevatorMachine = {ANIMSET_OVL(8), 1, 79, 537, 0x005};
EInit g_EInitSecretWall = {ANIMSET_OVL(2), 75, 0, 0, 0x005};
EInit g_EInitWallSegment = {ANIMSET_DRA(0), 0, 0, 0, 0x000};
EInit g_EInitSecretElevator = {ANIMSET_OVL(2), 102, 0, 0, 0x005};
EInit D_us_8018076C = {ANIMSET_OVL(11), 0, 72, 564, 0x003};
EInit D_us_80180778 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitUnused80180784 = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit D_us_80180790 = {ANIMSET_OVL(2), 92, 0, 0, 0x005};
// clang-format on
