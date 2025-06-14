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
    EntityRWarpRoom,
    EntityWarpSmallRocks,
};

// *** Group here all the Entity Init ***
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
u16 g_EInitObtainable[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_EInitParticle[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000,
};
u16 g_EInitInteractable[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 g_EInitUnkId13[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
};
u16 g_EInitLockCamera[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_EInitCommon[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_EInitDamageNum[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 D_801804AC[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_EInitReverseSmallRocks[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 g_EInitSmallRocks[] = {
    0x8002, 0x0000, 0x0000, 0x82E8, 0x0005, 0x0000,
};
// ******
