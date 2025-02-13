// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO4_H
#define BO4_H

#include <stage.h>

#define OVL_EXPORT(x) BO4_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum {
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

    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
} EntityIDs;

#endif // BO4_H
