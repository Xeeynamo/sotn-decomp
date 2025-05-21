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

    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x17 */ E_ID_17 = 0x17,
    /* 0x19 */ E_ID_19 = 0x19,
    /* 0x1A */ E_ID_1A,
    /* 0x1B */ E_ID_1B,
    /* 0x1C */ E_ID_1C,
    /* 0x1D */ E_ID_1D,

    /* 0x22 */ E_MIST = 0x22,

    /* 0x41 */ E_ID_41 = 0x41,
    /* 0x42 */ E_ID_42 = 0x42,
    /* 0x43 */ E_ID_43 = 0x43,
    /* 0x44 */ E_ID_44 = 0x44,
    /* 0x50 */ E_ID_50 = 0x50, // may be E_WEAPON

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

enum BlueprintKind {
    B_KIND_0,
    B_KIND_1,
    B_KIND_2,
    B_KIND_3,
    B_KIND_4,
    B_KIND_5,
    B_KIND_6,
    B_KIND_7,
    B_KIND_8,
    B_KIND_9,
    NUM_BLUEPRINT_KIND,
};
enum BlueprintOrigin {
    // Spawned entities have a life-cycle on their own and
    B_ORIGIN_DEFAULT,

    B_ORIGIN_1,
    B_ORIGIN_2,
    B_ORIGIN_3,
    B_ORIGIN_4,
    B_ORIGIN_5,
    B_ORIGIN_6,
    B_ORIGIN_7,
    B_ORIGIN_8,
    B_ORIGIN_9,
    B_ORIGIN_10,
    B_ORIGIN_11,
    B_ORIGIN_12,
    B_ORIGIN_13,
    B_ORIGIN_14,
};
