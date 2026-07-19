// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_SPRITE_H
#define SATURN_SPRITE_H

#include "sattypes.h"

typedef struct {
    u16 attributes;
    s16 offsetX;
    s16 offsetY;
    u16 imageIndex;
} SaturnSpritePart;

typedef struct {
    u16 header;
    u16 commandFlags;
} SaturnSpriteFrameHeader;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[1];
} SaturnSpriteFrame1;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[2];
} SaturnSpriteFrame2;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[3];
} SaturnSpriteFrame3;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[4];
} SaturnSpriteFrame4;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[5];
} SaturnSpriteFrame5;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[6];
} SaturnSpriteFrame6;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[7];
} SaturnSpriteFrame7;

typedef struct {
    u8 storedWidth;
    u8 storedHeight;
    u16 characterOffsetUnits;
} SaturnSpriteImage;

typedef struct {
    u8 width;
    u8 height;
    u8 pixels[512];
} SaturnIndexed4Texture64x16;

typedef struct {
    u16 count;
    u16 colors[3][16];
    u16 padding;
} SaturnSpritePalette3;

typedef struct {
    u16 count;
    u16 colors[4][16];
    u16 padding;
} SaturnSpritePalette4;

typedef struct {
    u16 countAndFlags;
    u16 colors[1][16];
} SaturnSpritePalette1;

typedef struct {
    u16 count;
    u16 colors[10][16];
} SaturnSpritePalette10;

typedef struct {
    u16 countAndFlags;
    u16 colors[11][16];
} SaturnSpritePalette11;

typedef struct {
    SaturnSpriteImage* images;
    u16* palettes;
    s16 allocationIndex;
    u16 flags;
} SaturnSpriteResource;

#endif
