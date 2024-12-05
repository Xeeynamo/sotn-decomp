// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO1

#define OVL_EXPORT(x) NO1_##x
#define CASTLE_FLAG_BANK 0x13

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

typedef enum EntityIDs {
    // /* 0x00 */ E_NONE,
    // /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP = 0x03,
    // /* 0x04 */ E_NUMERIC_DAMAGE,
    // /* 0x05 */ E_RED_DOOR,
    // /* 0x06 */ E_INTENSE_EXPLOSION,
    // /* 0x07 */ E_SOUL_STEAL_ORB,
    // /* 0x08 */ E_ROOM_FOREGROUND,
    // /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0xA,
    // /* 0x0B */ E_RELIC_ORB,
    // /* 0x0C */ E_HEART_DROP,
    // /* 0x0D */ E_ENEMY_BLOOD,
    // /* 0x0E */ E_SAVE_GAME_POPUP,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11 = 0x11,
    // /* 0x13 */ E_UNK_ID_13 = 0x13,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x21 */ E_AXE_KNIGHT,
} EntityIDs;
