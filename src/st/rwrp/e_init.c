// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

void EntityRedDoor(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityRWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
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
    EntityRWarpRoom,       EntityWarpSmallRocks,
};

// *** Group here all the Entity Init ***
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0x00, 0x00, 0x0000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, 0x0000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, 0x0000, 0x002};
EInit D_80180464 = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, 0x0000, 0x003};
EInit D_801804AC = {ANIMSET_OVL(1), 0x00, 0x00, 0x0000, 0x003};
EInit g_EInitReverseSmallRocks = {ANIMSET_OVL(1), 0x00, 0x00, 0x0000, 0x005};
EInit g_EInitSmallRocks = {ANIMSET_OVL(2), 0x00, 0x00, 0x82E8, 0x005};
// ******
