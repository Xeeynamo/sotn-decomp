// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityDamageDisplay(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);

// not sure what to do about *[] vs ** typing issue
PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    /* 3E4 */ EntityBreakable,
    /* 3E8 */ EntityExplosion,
    /* 3EC */ EntityPrizeDrop,
    /* 3F0 */ EntityDamageDisplay,
    /* 3F4 */ OVL_EXPORT(EntityRedDoor),
    /* 3F8 */ EntityIntenseExplosion,
    /* 3FC */ EntitySoulStealOrb,
    /* 400 */ EntityRoomForeground,
    /* 404 */ EntityStageNamePopup,
    /* 408 */ EntityEquipItemDrop,
    /* 40C */ EntityRelicOrb,
    /* 410 */ EntityHeartDrop,
    /* 414 */ EntityEnemyBlood,
    /* 418 */ EntityMessageBox,
    /* 41C */ EntityDummy,
    /* 420 */ EntityDummy,
    /* 424 */ OVL_EXPORT(EntityBackgroundBlock), // unused
    /* 428 */ OVL_EXPORT(EntityLockCamera), // unused? looks debugging stuff
    /* 42C */ EntityUnkId13,
    /* 430 */ EntityExplosionVariants,
    /* 434 */ EntityGreyPuff,
    /* 438 */ EntityWarpRoom,
    /* 43C */ EntityWarpSmallRocks,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#define USE_ENEMY_3
#include "../e_init_common.h"
EInit g_EInitSmallRocks = {ANIMSET_OVL(1), 0, 0x00, 0x000, 5};
