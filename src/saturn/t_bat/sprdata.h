#ifndef SATURN_T_BAT_SPRDATA_H
#define SATURN_T_BAT_SPRDATA_H

#include "sattypes.h"

typedef struct {
    u16 flags;
    u16 reserved;
    u16 variant;
    u16 size;
    s16 xOffset;
    u16 frameIndex;
} SaturnBatSpritePart;

extern u32 g_BatEmptySpritePart;
extern SaturnBatSpritePart g_BatSpriteParts[34];

#endif
