// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
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
void OVL_EXPORT(EntityCutsceneDialogue)(Entity*);
void EntityCSMoveAlucard(Entity*);
void EntityFadeToWhite1(Entity*);
void EntityUnkId23(Entity*);
void EntityFadeToWhite2(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
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
    OVL_EXPORT(EntityCutsceneDialogue),
    EntityCSMoveAlucard,
    EntityFadeToWhite1,
    EntityUnkId23,
    EntityFadeToWhite2,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0, PAL_NULL, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, PAL_NULL, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, PAL_NULL, 0x002};
EInit D_8018047C = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x003};
static EInit __unused__ = {ANIMSET_OVL(1), 0, 0, PAL_NULL, 0x003};
// e_succubus
EInit g_EInitSuccubus = {ANIMSET_OVL(1), 0, 72, PAL_SUCCUBUS, 0x0156};
EInit D_801804DC = {ANIMSET_OVL(1), 0, 72, PAL_SUCCUBUS, 0x0157};
EInit D_801804E8 = {ANIMSET_OVL(1), 0, 72, PAL_SUCCUBUS, 0x0005};
EInit D_801804F4 = {ANIMSET_OVL(1), 0, 72, PAL_SUCCUBUS, 0x0158};
EInit D_80180500 = {ANIMSET_OVL(1), 0, 72, PAL_SUCCUBUS, 0x0159};
EInit D_8018050C = {ANIMSET_OVL(1), 0, 72, PAL_SUCCUBUS, 0x015A};
// clang-format on
