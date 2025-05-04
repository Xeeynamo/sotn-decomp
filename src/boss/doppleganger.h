// SPDX-License-Identifier: AGPL-3.0-or-later

#define DOPPLEGANGER g_Entities[STAGE_ENTITY_START]

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_FACTORY,
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

    /* 0x22 */ E_ID_22 = 0x22,

    /* 0x41 */ E_ID_41 = 0x41,
    /* 0x42 */ E_ID_42 = 0x42,
    /* 0x43 */ E_ID_43 = 0x43,
    /* 0x44 */ E_ID_44 = 0x44,
    /* 0x50 */ E_ID_50 = 0x50,

    /* 0x60 */ E_ID_60 = 0x60,
    /* 0x90 */ E_ID_90 = 0x90,
} EntityIDs;

typedef enum {
    Dop_Stand = 1,
    Dop_Walk,
    Dop_Crouch,
    Dop_Fall,
    Dop_Jump,
    Dop_MorphBat,
    Dop_MorphMist = 8,
    Dop_HighJump,
    Dop_UnmorphBat,
    Dop_Hit,
    Dop_StatusStone,
    Dop_UnmorphMist = 15,
    Dop_SwordWarp,
    Dop_Kill,
} Doppleganger_Step;

extern PlayerState g_Dop;

// this is similar to `WeaponAnimation` but
// with fewer fields.
typedef struct {
    AnimationFrame* frames;
    s8* frameProps;
    u16 soundId;
    u8 frameStart;
    u8 soundFrame;
} DopWeaponAnimation;
