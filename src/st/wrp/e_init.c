// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

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
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,       EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay,   EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop,   EntityRelicOrb,          EntityHeartDrop,
    EntityEnemyBlood,      EntityMessageBox,        EntityDummy,
    EntityDummy,
    EntityBackgroundBlock, // unused
    EntityLockCamera,      // unused? looks debugging stuff
    EntityUnkId13,         EntityExplosionVariants, EntityGreyPuff,
    EntityWarpRoom,        EntityWarpSmallRocks,
};

EInit g_EInitBreakable = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitEnemy3 = {ANIMSET_OVL(1), 0, 0x00, 0x000, 3};
EInit g_EInitReverseSmallRocks = {ANIMSET_OVL(11), 1, 0x48, 0x21A, 97};
EInit g_EInitSmallRocks = {ANIMSET_OVL(1), 0, 0x00, 0x000, 5};
