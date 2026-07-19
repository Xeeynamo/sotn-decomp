// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_STAGE_DATA_H
#define SATURN_STAGE_DATA_H

#include "sattypes.h"

typedef struct {
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
    u8 metadata;
    u8 recordId;
} SaturnRoomHeader;

typedef struct {
    u32 characterGraphics;
    u32 palettes;
    u32 tilemap;
} SaturnLayerStreams;

typedef struct {
    SaturnLayerStreams layers[3];
} SaturnLayerMapOffsets;

typedef struct {
    SaturnLayerStreams layers[3];
} SaturnLayerCompressedSizes;

typedef struct {
    u8 scrollDivisorX;
    u8 scrollDivisorY;
    u8 wrapFlags;
} SaturnLayerSetup;

typedef struct {
    SaturnLayerSetup layers[3];
} SaturnRoomLayerSetup;

typedef struct {
    u32 dataOffset;
    u32 dataSize;
} SaturnRoomGraphics;

typedef struct {
    u8 nbg0;
    u8 nbg1;
    u8 nbg2;
    u8 nbg3;
    u8 sprite0;
    u8 sprite1;
    u8 sprite2;
    u8 sprite3;
    u8 sprite4;
    u8 sprite5;
    u8 sprite6;
    u8 sprite7;
} SaturnRoomPriorities;

/*
 * The first stage-header pointer selects EntityEntry records.  Each record
 * carries both a sprite bank and the entity's update callback; the header is
 * therefore not itself a table of function pointers.
 */
typedef struct {
    EntityEntry** entityEntries;
    // Stage-local slots mix SpriteParts tables and resource descriptors.
    void** spriteBanks;
    LayoutEntity** layoutHorizontal;
    LayoutEntity** layoutVertical;
    SaturnRoomHeader* rooms;
    SaturnLayerCompressedSizes* layerCompressedSizes;
    SaturnLayerMapOffsets* layerMapOffsets;
    SaturnRoomLayerSetup* layerSetup;
    SaturnRoomGraphics* roomGraphics;
    SaturnRoomPriorities* roomPriorities;
} SaturnStageDataTables;

#endif
