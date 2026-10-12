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
void EntityPersistentItemDrop(Entity*);
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
    EntityRelicOrb,        EntityPersistentItemDrop,
    EntityEnemyBlood,      EntityMessageBox,
    EntityDummy,           EntityDummy,
    EntityBackgroundBlock, EntityLockCamera,
    EntityUnkId13,         EntityExplosionVariants,
    EntityGreyPuff,        EntityCutscene,
    EntityPlatform,        EntityMaria,
    EntityRoomDarkness,    EntityElevatorStationary,
    EntityUnkId1B,         EntityMovingElevator,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
#include "../e_init_common.h"
EInit g_EInitEnemy3 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitElevator = {ANIMSET_OVL(11), 0x01, 0x48, PAL_ELEVATOR, ENEMY_INTERACTABLE};

#ifdef VERSION_PSP
EInit g_EInitUnk = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_MARIA};
#endif
