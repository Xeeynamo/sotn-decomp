// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

#ifdef VERSION_PSP
typedef struct {
    /* 0x0927B1C8 */ u8* scriptCur;   // ptr to dialogue next character
    /* 0x04 */ s16 startX;            // starting x coord
    /* 0x06 */ s16 nextLineY;         // next line y coord
    /* 0x08 */ s16 startY;            // starting y coord
    /* 0x0A */ s16 nextCharX;         // next char x coord
    /* 0x0C */ s16 nextLineX;         // next line x coord
    /* 0x0E */ u16 nextCharY;         // next char y coord
    /* 0x10 */ u16 portraitAnimTimer; // portrait animation timer
    /* 0x12 */ u8 unk12;              // unknown
    /* 0x13 */ u8 clutIndex;
    /* 0x14 */ u8 nextCharTimer; // timer to next character
    /* 0x15 */ u8 unk17;         // unknown
    /* 0x16 */ Primitive* prim;  // for dialogue graphics rendering
    /* 0x1A */ u32 primIndex;
    /* 0x1C */ u16* unk20;
    /* 0x20 */ u32 : 32;
    /* 0x24 */ u16* clutIndexes;
    /* 0x28 */ u32 : 32;
    /* 0x2C */ s32 clutArrLength;
    /* 0x30 */ u32 : 32;
    /* 0x34 */ u8* script;
    /* 0x38 */ u8* scriptEnd; // pointer to the end of the script
} Dialogue2;                  // size: 0x3C
#else
typedef struct {
    /* 0x00 */ u8* scriptCur;         // ptr to dialogue next character
    /* 0x04 */ s16 startX;            // starting x coord
    /* 0x06 */ s16 nextLineY;         // next line y coord
    /* 0x08 */ s16 startY;            // starting y coord
    /* 0x0A */ s16 nextCharX;         // next char x coord
    /* 0x0C */ s16 nextLineX;         // next line x coord
    /* 0x0E */ u16 nextCharY;         // next char y coord
    /* 0x10 */ u16 portraitAnimTimer; // portrait animation timer
    /* 0x12 */ u8 unk12;              // unknown
    /* 0x13 */ u8 clutIndex;
    /* 0x14 */ Primitive* prim; // for dialogue graphics rendering
    /* 0x18 */ u32 primIndex;
    /* 0x1C */ s32 : 32;
    /* 0x20 */ s32 : 32;
    /* 0x24 */ s32 : 32;
    /* 0x28 */ s32 : 32;
    /* 0x2C */ s32 : 32;
    /* 0x30 */ s32 : 32;
    /* 0x34 */ s32 : 32;
    /* 0x38 */ u16 unk3C;     // maybe it is a begin flag?
    /* 0x3A */ u16 timer;     // global timer
    /* 0x3C */ u8* scriptEnd; // pointer to the end of the script
} Dialogue2;                  // size = 0x40
#endif
