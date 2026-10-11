// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityPersistentItemDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void Entity3DBackgroundHouse(Entity*);
void Entity3DHouseSpawner(Entity*);
void EntityBackgroundClouds(Entity*);
void EntitySuccubus(Entity*);
void EntitySuccubusPetal(Entity*);
void EntitySuccubusWingOverlay(Entity*);
void EntitySuccubusClone(Entity*);
void EntityPinkBallProjectile(Entity*);
void EntitySuccubusWingSpike(Entity*);
void EntitySuccubusWingSpikeTip(Entity*);
void EntityCutsceneDialogue(Entity*);
void EntityCSMoveAlucard(Entity*);
void EntityFadeToWhite1(Entity*);
void EntityUnkId23(Entity*);
void EntityFadeToWhite2(Entity*);

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
    Entity3DBackgroundHouse,
    Entity3DHouseSpawner,
    EntityBackgroundClouds,
    EntitySuccubus,
    EntitySuccubusPetal,
    EntitySuccubusWingOverlay,
    EntitySuccubusClone,
    EntityPinkBallProjectile,
    EntitySuccubusWingSpike,
    EntitySuccubusWingSpikeTip,
    EntityCutsceneDialogue,
    EntityCSMoveAlucard,
    EntityFadeToWhite1,
    EntityUnkId23,
    EntityFadeToWhite2,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_8018047C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
static EInit __unused__ = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
// e_succubus
EInit g_EInitSuccubus = {ANIMSET_OVL(1), 0x00, 0x48, PAL_SUCCUBUS, ENEMY_SUCCUBUS};
EInit D_801804DC = {ANIMSET_OVL(1), 0x00, 0x48, PAL_SUCCUBUS, ENEMY_SUCCUBUS_PETAL};
EInit D_801804E8 = {ANIMSET_OVL(1), 0x00, 0x48, PAL_SUCCUBUS, ENEMY_INTERACTABLE};
EInit D_801804F4 = {ANIMSET_OVL(1), 0x00, 0x48, PAL_SUCCUBUS, ENEMY_SUCCUBUS_CLONE};
EInit D_80180500 = {ANIMSET_OVL(1), 0x00, 0x48, PAL_SUCCUBUS, ENEMY_SUCCUBUS_PINK_BALL_PROJECTILE};
EInit D_8018050C = {ANIMSET_OVL(1), 0x00, 0x48, PAL_SUCCUBUS, ENEMY_SUCCUBUS_WING_SPIKE_TIP};
// clang-format on
