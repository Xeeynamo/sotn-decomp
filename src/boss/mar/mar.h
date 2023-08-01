#ifndef MAR_H
#define MAR_H

#include "common.h"
#include "stage.h"

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

    /* 0x16 */ E_CLOCKROOM_CONTROLLER = 0x16,
    /* 0x17 */ E_func_80198574,
    /* 0x18 */ E_BIRDCAGE_DOOR,
} EntityIDs;

/* Initializers */
extern u16 D_801803E4[];

extern u16 D_80181280[];
extern u16 D_80181284[];
extern u16 D_80181288[];
extern u16 D_8018128C[];
extern u16 D_80181290[];
extern u16 D_80181294[];
extern u16 D_80181298[];
extern s32 D_801812A0[];
extern u16 D_801812A8[];
extern u8 D_801812C4[];
extern u8 D_801812D0[];
extern s16 D_801812DC[];
extern u16 D_8019AF28[];
extern s16 D_8019AF2A;
#endif