// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef struct {
    /* 0x00 */ u8* scriptCur;         // ptr to dialogue next character
    /* 0x04 */ s16 nextCharX;         // starting x coord
    /* 0x06 */ s16 nextCharY;         // next char y coord
    /* 0x08 */ s16 portraitAnimTimer; // portrait animation timer
    /* 0x0A */ u8 nextCharTimer;
    /* 0x0B */ u8 unkB;
    // Of course, offsets beyond here won't be right on PSP
#if defined(VERSION_PSP)
    /* 0x0C */ Primitive* prim[6]; // for dialogue graphics rendering
#else
    /* 0x0C */ Primitive* prim[4]; // for dialogue graphics rendering
#endif
    /* 0x1C */ s32 primIndex[3]; // primIndices: unk, actorName, unk
} OVL_EXPORT(Dialogue);          // size = 0x28
