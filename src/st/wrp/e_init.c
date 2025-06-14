// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

void OVL_EXPORT(EntityRedDoor)(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
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
