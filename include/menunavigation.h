#ifndef MENUNAVIGATION_H
#define MENUNAVIGATION_H

#include "types.h"
#include "item.h"
#include "psxsdk/libgpu.h"

typedef struct {
    /* 0x00, 8003C9A8 */ s32 cursorMain;
    /* 0x04, 8003C9AC */ s32 cursorRelic;
    /* 0x08, 8003C9B0 */ s32 cursorEquip;
    /* 0x0C, 8003C9B4 */ s32 cursorEquipType[NUM_EQUIP_KINDS];
    /* 0x20, 8003C9C8 */ s32 scrollEquipType[NUM_EQUIP_KINDS];
    /* 0x34, 8003C9DC */ s32 cursorSpells;
    /* 0x38, 8003C9E0 */ s32 cursorSettings;
    /* 0x3C, 8003C9E4 */ s32 cursorCloak;
    /* 0x40, 8003C9E8 */ s32 cursorButtons;
    /* 0x44, 8003C9EC */ s32 cursorWindowColors;
    /* 0x48, 8003C9F0 */ s32 cursorTimeAttack;
} MenuNavigation; /* size=0x4C */


typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ s16 cursorW;
    /* 0x06 */ s16 cursorH;
    /* 0x08 */ RECT unk1;
    /* 0x10 */ s16 w;
    /* 0x12 */ s16 h;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 otIdx;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
} MenuContext; // size = 0x1E
#define SIZEOF_MENUCONTEXT (0x1E)

/* 0x8003C9A8 */ extern MenuNavigation g_MenuNavigation;

extern u32 g_MenuStep;
extern s32 D_800973EC; // flag to check if the menu is shown

#endif // MENUNAVIGATION_H
