// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

void EntityBreakable(Entity*);
void OVL_EXPORT(EntityExplosion)(Entity*);
void OVL_EXPORT(EntityPrizeDrop)(Entity*);
void OVL_EXPORT(EntityDamageDisplay)(Entity*);
void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void OVL_EXPORT(EntityEquipItemDrop)(Entity*);
void OVL_EXPORT(EntityRelicOrb)(Entity*);
void OVL_EXPORT(EntityHeartDrop)(Entity*);
void EntityEnemyBlood(Entity*);
void OVL_EXPORT(EntityMessageBox)(Entity*);
void OVL_EXPORT(EntityDummy)(Entity*);
void OVL_EXPORT(EntityDummy)(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);

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
    EntityWarpRoom,
    EntityWarpSmallRocks,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#define USE_ENEMY_3
#include "../e_init_common.h"
EInit g_EInitReverseSmallRocks = {ANIMSET_OVL(11), 1, 0x48, 0x21A, 97};
EInit g_EInitSmallRocks = {ANIMSET_OVL(1), 0, 0x00, 0x000, 5};
