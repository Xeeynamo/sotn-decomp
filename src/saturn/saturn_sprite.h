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
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[8];
} SaturnSpriteFrame8;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[9];
} SaturnSpriteFrame9;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[10];
} SaturnSpriteFrame10;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[11];
} SaturnSpriteFrame11;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[12];
} SaturnSpriteFrame12;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[13];
} SaturnSpriteFrame13;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[14];
} SaturnSpriteFrame14;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[15];
} SaturnSpriteFrame15;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[16];
} SaturnSpriteFrame16;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[17];
} SaturnSpriteFrame17;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[18];
} SaturnSpriteFrame18;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[19];
} SaturnSpriteFrame19;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[20];
} SaturnSpriteFrame20;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[21];
} SaturnSpriteFrame21;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[22];
} SaturnSpriteFrame22;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[23];
} SaturnSpriteFrame23;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[24];
} SaturnSpriteFrame24;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[25];
} SaturnSpriteFrame25;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[26];
} SaturnSpriteFrame26;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[27];
} SaturnSpriteFrame27;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[28];
} SaturnSpriteFrame28;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[29];
} SaturnSpriteFrame29;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[30];
} SaturnSpriteFrame30;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[31];
} SaturnSpriteFrame31;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[32];
} SaturnSpriteFrame32;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[33];
} SaturnSpriteFrame33;

typedef struct {
    SaturnSpriteFrameHeader header;
    SaturnSpritePart parts[34];
} SaturnSpriteFrame34;

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
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding;
} SaturnSpritePalette2;

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
    u16 allocationIndex;
    u16 flags;
} SaturnSpriteResource;

#endif
