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
    EntityEquipItemDrop,   EntityRelicOrb,          EntityPersistentItemDrop,
    EntityEnemyBlood,      EntityMessageBox,        EntityDummy,
    EntityDummy,
    EntityBackgroundBlock, // unused
    EntityLockCamera,      // unused? looks debugging stuff
    EntityUnkId13,         EntityExplosionVariants, EntityGreyPuff,
    EntityRWarpRoom,       EntityWarpSmallRocks,
};

// *** Group here all the Entity Init ***
// clang-format off
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_80180464 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801804AC = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitReverseSmallRocks = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitSmallRocks = {ANIMSET_OVL(2), 0x00, 0x00, PAL_FLAG(PAL_SMALL_ROCKS), ENEMY_INTERACTABLE};
// clang-format on
// ******
