// SPDX-License-Identifier: AGPL-3.0-or-later

#define DOPPLEGANGER g_Entities[STAGE_ENTITY_START]

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_ENTITYFACTORY,
    /* 0x02 */ E_EXPLOSION = 2,
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
    /* 0x17 */ E_ID_17 = 0x17,
    /* 0x19 */ E_ID_19 = 0x19,
    /* 0x1A */ E_ID_1A,
    /* 0x1C */ E_ID_1C = 0x1C,
    /* 0x1D */ E_ID_1D,
} EntityIDs;

typedef enum {
    Dop_Stand = 1,
    Dop_Walk = 2,
    Dop_Fall = 4,
    Dop_Jump = 5,
    Dop_MorphBat = 6,
    Dop_UnmorphBat = 10,
    Dop_Hit = 11,
    Dop_Kill = 17,
} Doppleganger_Steps;
