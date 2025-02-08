// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x1D, 0x25, 0x75, 0x7D, 0xC6, 0xC7, 0xC8, 0xC9},
    {0x1F, 0x27, 0x77, 0x7F, 0xCA, 0xCB, 0xCC, 0xCD},
};

void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityDamageDisplay(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
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
    /* 424 */ EntityBackgroundBlock, // unused
    /* 428 */ EntityUnkId12,         // unused? looks debugging stuff
    /* 42C */ EntityUnkId13,
    /* 430 */ EntityExplosionVariants,
    /* 434 */ EntityGreyPuff,
    /* 438 */ EntityWarpRoom,
    /* 43C */ EntityWarpSmallRocks,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitSmallRocks = {ANIMSET_OVL(1), 0, 0x00, 0x000, 5};
