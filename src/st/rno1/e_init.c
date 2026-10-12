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
void EntityDoorwayBlocker(Entity* self);
void EntityBossAnteRoomDecoration(Entity* self);
void EntityBossRoundDoorHalf(Entity* self);
void EntityBossRoundDoor(Entity* self);

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
    EntityDoorwayBlocker,
    EntityBossAnteRoomDecoration,
    EntityBossRoundDoorHalf,
    EntityBossRoundDoor,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitParanthropus = {ANIMSET_OVL(3), 0x01, 0x4C, PAL_PARANTHROPUS, ENEMY_PARANTHROPUS};
EInit g_EInitParanthropusBoneHitbox = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_PARANTHROPUS_BONE_HITBOX};
EInit g_EInitParanthropusThrownBone = {ANIMSET_OVL(3), 0x36, 0x4C, PAL_PARANTHROPUS, ENEMY_PARANTHROPUS_THROWN_BONE};
EInit g_EInitStoneSkull = {ANIMSET_OVL(4), 0x00, 0x4E, PAL_STONE_SKULL, ENEMY_STONE_SKULL};
EInit g_EInitJackOBones = {ANIMSET_OVL(5), 0x01, 0x4A, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES};
EInit g_EInitJackOBones2 = {ANIMSET_OVL(5), 0x00, 0x4A, PAL_JACK_O_BONES, ENEMY_PARTICLE};
EInit g_EInitJackOBones3 = {ANIMSET_OVL(5), 0x15, 0x4A, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES_3};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(6), 0x01, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON};
EInit g_EInitNovaSkeleton2 = {ANIMSET_OVL(6), 0x00, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON_LASER};
EInit g_EInitElevatorMachine = {ANIMSET_OVL(8), 0x01, 0x4F, PAL_ELEVATOR_MACHINE, ENEMY_INTERACTABLE};
EInit g_EInitSecretWall = {ANIMSET_OVL(2), 0x4B, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitWallSegment = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitSecretElevator = {ANIMSET_OVL(2), 0x66, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitBossNextDecor = {ANIMSET_OVL(11), 0x00, 0x48, PAL_BOSS_NEXT_DECOR, ENEMY_COMMON};
EInit g_EInitHalfRound = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnused80180784 = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EinitDoorwayBlocker = {ANIMSET_OVL(2), 0x5C, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
// clang-format on
