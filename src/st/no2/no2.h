// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO2

#define OVL_EXPORT(x) NO2_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum EntityIDs {
    /* 0x00 */ // E_NONE,
    /* 0x01 */ // E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ // E_NUMERIC_DAMAGE,
    /* 0x05 */ // E_RED_DOOR,
    /* 0x06 */ // E_INTENSE_EXPLOSION,
    /* 0x07 */ // E_SOUL_STEAL_ORB,
    /* 0x08 */ // E_ROOM_FOREGROUND,
    /* 0x09 */ // E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0x0A,
    /* 0x0B */ // E_RELIC_ORB,
    /* 0x0C */ // E_HEART_DROP,
    /* 0x0D */ // E_ENEMY_BLOOD,
    /* 0x0E */ // E_MESSAGE_BOX,
    /* 0x0F */ // E_DUMMY_0F,
    /* 0x10 */ // E_DUMMY_10,
    /* 0x11 */ // E_BACKGROUND_BLOCK,
    /* 0x12 */ // E_LOCK_CAMERA,
    /* 0x13 */ // E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ // E_ID_16,
    /* 0x17 */ // E_ID_17,
    /* 0x18 */ // E_ID_18,
    /* 0x19 */ // E_ID_19,
    /* 0x1A */ // E_ID_1A,
    /* 0x1B */ // E_ID_1B,
    /* 0x1C */ // E_ID_1C,
    /* 0x1D */ // E_ID_1D,
    /* 0x1E */ // E_ID_1E,
    /* 0x1F */ // E_ID_1F,
    /* 0x20 */ // E_ID_20,
    /* 0x21 */ // E_ID_21,
    /* 0x22 */ // E_ID_22,
    /* 0x23 */ // E_ID_23,
    /* 0x24 */ // E_ID_24,
    /* 0x25 */ // E_ID_25,
    /* 0x26 */ // E_ID_26,
    /* 0x27 */ E_ID_27 = 0x27,
} EntityIDs;

extern u16 g_EInitParticle[];
