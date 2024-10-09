// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

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
    /* 0x14 */ Primitive* prim[1]; // for dialogue graphics rendering
    /* 0x18 */ s32 primIndex[8];   // primIndices: unk, actorName, unk
    /* 0x38 */ u16 unk3C;          // maybe it is a begin flag?
    /* 0x3A */ u16 timer;          // global timer
    /* 0x3C */ u8* scriptEnd;      // pointer to the end of the script
} Dialogue2;                       // size = 0x40
