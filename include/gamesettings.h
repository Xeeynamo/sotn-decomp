#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "types.h"
#include "gamepad.h"
#include "item.h"
#include "timeattack.h"

typedef struct {
    /* 0x000, 0x8003C9F8 */ u32 buttonConfig[BUTTON_COUNT];
    /* 0x020, 0x8003CA18 */ u16 buttonMask[BUTTON_COUNT];
    /* 0x030, 0x8003CA28 */ s32 timeAttackRecords[TIMEATTACK_EVENT_END];
    /* 0x0B0, 0x8003CAA8 */ s32 cloakColors[6];
    /* 0x0C8, 0x8003CAC0 */ s32 windowColors[3];
    /* 0x0D4, 0x8003CACC */ s32 equipOrderTypes[ITEM_END];
    /* 0x100, 0x8003CAF8 */ s32 isCloakLiningReversed;
    /* 0x104, 0x8003CAFC */ s32 isSoundMono;
    /* 0x108, 0x8003CB00 */ s32 D_8003CB00;
    /* 0x10C, 0x8003CB04 */ s32 D_8003CB04;
} GameSettings; /* size=0x110 */

/* 0x8003C9F8 */ extern GameSettings g_Settings;

#endif // GAMESETTINGS_H
