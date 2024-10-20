// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef MAR_H
#define MAR_H

#include <stage.h>

#define OVL_EXPORT(x) MAR_##x

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
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,

    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_ID_15,
    /* 0x16 */ E_CLOCKROOM_CONTROLLER,
    /* 0x17 */ E_CLOCK_HANDS,
    /* 0x18 */ E_BIRDCAGE_DOOR,
    /* 0x19 */ E_STATUE,
    /* 0x1A */ E_STATUE_GEAR,
    /* 0x1B */ E_STONE_DOOR,
    /* 0x1C */ E_ID_1C,
    /* 0x1D */ E_DUMMY_1D,
} EntityIDs;

typedef enum Statues {
    /* 0 */ RIGHT_STATUE,
    /* 1 */ LEFT_STATUE,
} Statues;

extern u16 g_eInitGeneric2[];
extern s32 D_800973FC;
extern u16 g_Statues[];
extern u16 D_80180A60[];

#endif
