// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

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
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityCutscene(Entity*);
void EntityPlatform(Entity*);
void EntityMaria(Entity*);
void EntityRoomDarkness(Entity*);
void EntityElevatorStationary(Entity*);
void EntityUnkId1B(Entity*);
void EntityMovingElevator(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,       EntityExplosion,
    EntityPrizeDrop,       EntityDamageDisplay,
    EntityRedDoor,         EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityRoomForeground,
    EntityStageNamePopup,  EntityEquipItemDrop,
    EntityRelicOrb,        EntityHeartDrop,
    EntityEnemyBlood,      EntityMessageBox,
    EntityDummy,           EntityDummy,
    EntityBackgroundBlock, EntityLockCamera,
    EntityUnkId13,         EntityExplosionVariants,
    EntityGreyPuff,        EntityCutscene,
    EntityPlatform,        EntityMaria,
    EntityRoomDarkness,    EntityElevatorStationary,
    EntityUnkId1B,         EntityMovingElevator,
};

EInit g_EInitBreakable = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitEnemy3 = {ANIMSET_OVL(1), 0, 0x00, 0x000, 3};
EInit g_EInitElevator = {ANIMSET_OVL(11), 1, 0x48, 0x223, 5};

#ifdef VERSION_PSP
EInit g_EInitUnk = {ANIMSET_DRA(0), 0, 0x00, 0, 0x190};
#endif
