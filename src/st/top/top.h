// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef TOP_H
#define TOP_H

#define STAGE_IS_TOP

#include <stage.h>

#define OVL_EXPORT(x) TOP_##x

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_ID_11 = 0x11,
    /* 0x13 */ E_UNK_ID_13 = 0x13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x17 */ E_STAIR_SWITCH = 0x17,
    /* 0x18 */ E_SECRET_STAIRS,
    /* 0x21 */ E_FLEA_RIDER = 0x21,
    /* 0x23 */ E_CUTSCENE = 0x23,
    /* 0x27 */ E_BREAKABLE_2 = 0x27,
    /* 0x28 */ E_AXE_KNIGHT_BLUE,
    /* 0x29 */ E_AXE_KNIGHT_AXE,
    /* 0x2A */ E_AXE_KNIGHT_AXE_2,
    /* 0x2B */ E_UNK_ENTITY,
};

#endif // TOP_H
