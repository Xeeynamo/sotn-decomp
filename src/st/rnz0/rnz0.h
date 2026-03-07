// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNZ0_H
#define RNZ0_H

#include <stage.h>

#define OVL_EXPORT(x) RNZ0_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum EntityIDs {
    E_NONE,
    E_BREAKABLE,
    E_EXPLOSION,
    E_PRIZE_DROP,
    E_NUMERIC_DAMAGE,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_SOUL_STEAL_ORB,
    E_ROOM_FOREGROUND,
    E_STAGE_NAME_POPUP,
    E_EQUIP_ITEM_DROP,
    E_RELIC_ORB,
    E_HEART_DROP,
    E_ENEMY_BLOOD,
    E_MESSAGE_BOX,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_EXPLOSION_VARIANTS,
    E_GREY_PUFF,
    E_WARP,
    E_SMALL_ROCKS,
} EntityIDs;

#endif // RNZ0_H
