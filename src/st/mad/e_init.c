// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

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
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,       EntityExplosion,
    EntityPrizeDrop,       EntityDamageDisplay,
    EntityRedDoor,         EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityRoomForeground,
    EntityStageNamePopup,  EntityEquipItemDrop,
    EntityRelicOrb,        EntityHeartDrop,
    EntityEnemyBlood,      EntityDummy,
    EntityDummy,           EntityDummy,
    EntityBackgroundBlock, EntityLockCamera,
    EntityUnkId13,         EntityExplosionVariants,
    EntityGreyPuff,
};

EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
