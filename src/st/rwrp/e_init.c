// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

void OVL_EXPORT(EntityRedDoor)(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityRWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void OVL_EXPORT(EntityPrizeDrop)(Entity*);
PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
    OVL_EXPORT(EntityExplosion),
    OVL_EXPORT(EntityPrizeDrop),
    OVL_EXPORT(EntityDamageDisplay),
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    OVL_EXPORT(EntityEquipItemDrop),
    OVL_EXPORT(EntityRelicOrb),
    OVL_EXPORT(EntityHeartDrop),
    EntityEnemyBlood,
    OVL_EXPORT(EntityMessageBox),
    OVL_EXPORT(EntityDummy),
    OVL_EXPORT(EntityDummy),
    OVL_EXPORT(EntityBackgroundBlock), // unused
    OVL_EXPORT(EntityLockCamera),      // unused? looks debugging stuff
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityRWarpRoom,
    EntityWarpSmallRocks,
};

// *** Group here all the Entity Init ***
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0x00, 0x00, 0x0000, 0x000};
EInit OVL_EXPORT(EInitObtainable) = {ANIMSET_DRA(3), 0x00, 0x00, 0x0000, 0x001};
EInit OVL_EXPORT(EInitParticle) = {ANIMSET_DRA(3), 0x00, 0x00, 0x0000, 0x002};
EInit D_80180464 = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x004};
EInit OVL_EXPORT(
    EInitInteractable) = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x005};
EInit OVL_EXPORT(EInitUnkId13) = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x002};
EInit OVL_EXPORT(EInitLockCamera) = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x001};
EInit OVL_EXPORT(EInitCommon) = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x003};
EInit OVL_EXPORT(EInitDamageNum) = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x003};
EInit D_801804AC = {ANIMSET_OVL(1), 0x00, 0x00, 0x0000, 0x003};
EInit g_EInitReverseSmallRocks = {ANIMSET_OVL(1), 0x00, 0x00, 0x0000, 0x005};
EInit g_EInitSmallRocks = {ANIMSET_OVL(2), 0x00, 0x00, 0x82E8, 0x005};
// ******
