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
    /* 0x17 */ E_CLOCK_HANDS,
    /* 0x18 */ E_BIRDCAGE_DOOR,
    /* 0x19 */ E_STATUE,
    /* 0x1A */ E_STATUE_GEAR,
    /* 0x1B */ E_STONE_DOOR,
    /* 0x1C */ E_func_80199114,
    /* 0x1D */ E_DUMMY_1D,
} EntityIDs;

/* Initializers */
extern u16 D_801803B4[];
extern u16 D_801803E4[];

extern u8 D_80180690[];
extern u8 D_801806A4[];
extern u8 D_801806B8[];
extern u8 D_801806CC[];
extern u8 D_801806E4[];
extern u8 D_801806EC[];
extern u8 D_80180700[];
extern u8 D_80180718[];
extern u8 D_80180724[];
extern u8 D_80180738[];

extern s16 D_80181280[];
extern s16 D_80181284[];
extern u16 D_80181288[];
extern u16 D_8018128C[];
extern u16 D_80181290[];
extern u16 D_80181294[];
extern u16 D_80181298[];
extern s32 D_801812A0[];
extern u16 D_801812A8[];
extern u8 D_801812C4[];
extern u8 D_801812D0[];
extern s16 g_StoneDoorTiles[];
extern u16 g_Statues[];

extern s32 D_8019AE70;
extern s32 D_8019AF20;

#endif