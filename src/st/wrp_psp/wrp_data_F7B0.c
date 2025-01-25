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
PfnEntityUpdate D_psp_09246E30[] = {
    /* 3E4 */ (PfnEntityUpdate)EntityBreakable,
    /* 3E8 */ (PfnEntityUpdate)EntityExplosion,
    /* 3EC */ (PfnEntityUpdate)EntityPrizeDrop,
    /* 3F0 */ (PfnEntityUpdate)EntityDamageDisplay,
    /* 3F4 */ (PfnEntityUpdate)OVL_EXPORT(EntityRedDoor),
    /* 3F8 */ (PfnEntityUpdate)EntityIntenseExplosion,
    /* 3FC */ (PfnEntityUpdate)EntitySoulStealOrb,
    /* 400 */ (PfnEntityUpdate)EntityRoomForeground,
    /* 404 */ (PfnEntityUpdate)EntityStageNamePopup,
    /* 408 */ (PfnEntityUpdate)EntityEquipItemDrop,
    /* 40C */ (PfnEntityUpdate)EntityRelicOrb,
    /* 410 */ (PfnEntityUpdate)EntityHeartDrop,
    /* 414 */ (PfnEntityUpdate)EntityEnemyBlood,
    /* 418 */ (PfnEntityUpdate)EntityMessageBox,
    /* 41C */ (PfnEntityUpdate)EntityDummy,
    /* 420 */ (PfnEntityUpdate)EntityDummy,
    /* 424 */ (PfnEntityUpdate)EntityBackgroundBlock, // unused
    /* 428 */ (PfnEntityUpdate)EntityUnkId12, // unused? looks debugging stuff
    /* 42C */ (PfnEntityUpdate)EntityUnkId13,
    /* 430 */ (PfnEntityUpdate)EntityExplosionVariants,
    /* 434 */ (PfnEntityUpdate)EntityGreyPuff,
    /* 438 */ (PfnEntityUpdate)EntityWarpRoom,
    /* 43C */ (PfnEntityUpdate)EntityWarpSmallRocks,
};
