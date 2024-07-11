#ifndef UI_H
#define UI_H

#include "types.h"
#include "primitive.h"

typedef struct {
    /* 0x00 */ const char* nextCharDialogue; // ptr to dialogue next character
    /* 0x04 */ s16 startX;                   // starting x coord
    /* 0x06 */ s16 nextLineY;                // next line y coord
    /* 0x08 */ s16 startY;                   // starting y coord
    /* 0x0A */ s16 nextCharX;                // next char x coord
    /* 0x0C */ s16 nextLineX;                // next line x coord
    /* 0x0E */ s16 nextCharY;                // next char y coord
    /* 0x10 */ s16 portraitAnimTimer;        // portrait animation timer
    /* 0x12 */ u16 unk12;                    // unknown
    /* 0x14 */ u16 clutIndex;                // CLUT index
    /* 0x16 */ u8 nextCharTimer;             // timer to next character
    /* 0x17 */ u8 unk17;                     // unknown
    /* 0x18 */ Primitive* prim[6];           // for dialogue graphics rendering
    /* 0x30 */ s32 primIndex[3];             // primIndices: unk, actorName, unk
    /* 0x3C */ u16 unk3C;                    // maybe it is a begin flag?
    /* 0x3E */ u16 timer;                    // global timer
    /* 0x40 */ const char* unk40;            // dialogue settings, maybe?
} Dialogue;                                  // size = 0x44


#endif // UI_H
