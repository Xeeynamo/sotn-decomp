#ifndef SATURN_T_BAT_GFX_H
#define SATURN_T_BAT_GFX_H

#include "sattypes.h"

typedef struct {
    u16 dimensions;
    u16 dataOffset;
} BatTextureSlice;

typedef struct {
    BatTextureSlice* textureSlices;
    u16* clutData;
    u16 vramX;
    u16 vramY;
} BatTextureResource;

extern BatTextureSlice g_BatTextureSlices[25];
extern BatTextureResource g_BatTextureResource;
extern BatTextureResource* g_BatResourceDescriptors[2];

#endif
