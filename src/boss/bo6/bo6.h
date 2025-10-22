// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO6_H
#define BO6_H

#include <stage.h>

#define OVL_EXPORT(x) BO6_##x

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_FACTORY,
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
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,

    /* 0x40 */ E_RICHTER = STAGE_ENTITY_START,
    /* 0x41 */ E_ID_41,
    /* 0x42 */ E_ID_42,
    /* 0x43 */ E_ID_43,
    /* 0x44 */ E_ID_44,
    /* 0x90 */ E_ID_90 = 0x90,
} EntityIDs;

// same as `RicSteps`, but like Doppleganger, offset by 1
typedef enum {
    /* 0x01 */ PL_S_STAND = 1,
    /* 0x02 */ PL_S_WALK,
    /* 0x03 */ PL_S_CROUCH,
    /* 0x04 */ PL_S_FALL,
    /* 0x05 */ PL_S_JUMP,
    /* 0x06 */ PL_S_5, // unused
    /* 0x07 */ PL_S_6, // unused
    /* 0x08 */ PL_S_7, // unused
    /* 0x09 */ PL_S_HIGHJUMP,
    /* 0x0A */ PL_S_9, // unused
    /* 0x0B */ PL_S_HIT,
    /* 0x0C */ PL_S_11, // unused
    /* 0x0D */ PL_S_BOSS_GRAB,
    /* 0x0E */ PL_S_13, // unused
    /* 0x0F */ PL_S_14, // unused
    /* 0x10 */ PL_S_15, // unused
    /* 0x11 */ PL_S_DEAD,
    /* 0x12 */ PL_S_17, // unused
    /* 0x13 */ PL_S_STAND_IN_AIR,
    /* 0x14 */ PL_S_FLAME_WHIP,
    /* 0x15 */ PL_S_HYDROSTORM,
    /* 0x16 */ PL_S_THROW_DAGGERS,
    /* 0x17 */ PL_S_DEAD_PROLOGUE,
    /* 0x18 */ PL_S_SLIDE,
    /* 0x19 */ PL_S_BLADEDASH,
    /* 0x1A */ PL_S_RUN,
    /* 0x1B */ PL_S_SLIDE_KICK,
    /* 0x1C */ PL_S_SUBWPN_CRASH,
    /* 0x1D */ PL_S_28, // unused
    /* 0x1E */ PL_S_29, // unused
    /* 0x1F */ PL_S_30, // unused
    /* 0x20 */ PL_S_31, // unused
    /* 0x21 */ PL_S_INIT,
    /* 0x40 */ PL_S_64 = 0x40,
    /* 0x50 */ PL_S_80 = 0x50,
    /* 0x60 */ PL_S_96 = 0x60,
    /* 0x70 */ PL_S_112 = 0x70,
    /* 0xF0 */ PL_S_DEBUG = 0xF0,
} OVL_EXPORT(RicSteps);

// TODO: share with richter
enum RicTimers {
    PL_T_POISON,
    PL_T_CURSE,
    PL_T_2,
    PL_T_3,
    PL_T_4,
    PL_T_5,
    PL_T_6,
    PL_T_7,
    PL_T_8,
    PL_T_ATTACK,
    PL_T_10,
    PL_T_RUN,
    PL_T_12,
    PL_T_INVINCIBLE_SCENE, // "dying" in the prologue
    PL_T_INVINCIBLE,
    PL_T_AFTERIMAGE_DISABLE,
};

#define RIC g_Entities[STAGE_ENTITY_START]

extern PlayerState g_Ric;

#endif // BO6_H
