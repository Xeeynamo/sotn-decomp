// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    u16 crossBoundaryPaletteColor;
    s16 prefix[2];
    s16 records[16][6];
    u16 padding;
} AlucardEffectSpriteMetadata;

AlucardEffectSpriteMetadata g_AlucardEffectSpriteMetadata = {
    0xF39C,
    {0, 0},
    {
        {256, 3, 0, 1, -17, 0},
        {256, 3, 0, 2, -16, 1},
        {256, 3, 0, -2, -7, 2},
        {256, 3, 0, 5, 1, 3},
        {256, 3, 0, 4, 7, 4},
        {256, 3, 0, 4, 6, 4},
        {256, 3, 0, 4, 7, 5},
        {256, 3, 0, 5, 1, 3},
        {256, 3, 0, -2, -8, 2},
        {256, 3, 0, 2, -18, 1},
        {256, 3, 0, 1, -20, 0},
        {256, 3, 0, 2, -20, 1},
        {256, 3, 0, -2, -9, 2},
        {256, 3, 0, 5, 1, 3},
        {256, 3, 0, 4, 8, 4},
        {256, 3, 0, 4, 8, 5},
    },
    0,
};

s16* g_AlucardEffectSpriteMetadataTable[] = {
    g_AlucardEffectSpriteMetadata.prefix,
    g_AlucardEffectSpriteMetadata.records[0],
    g_AlucardEffectSpriteMetadata.records[1],
    g_AlucardEffectSpriteMetadata.records[2],
    g_AlucardEffectSpriteMetadata.records[3],
    g_AlucardEffectSpriteMetadata.records[4],
    g_AlucardEffectSpriteMetadata.records[5],
    g_AlucardEffectSpriteMetadata.records[6],
    g_AlucardEffectSpriteMetadata.records[7],
    g_AlucardEffectSpriteMetadata.records[8],
    g_AlucardEffectSpriteMetadata.records[9],
    g_AlucardEffectSpriteMetadata.records[10],
    g_AlucardEffectSpriteMetadata.records[11],
    g_AlucardEffectSpriteMetadata.records[12],
    g_AlucardEffectSpriteMetadata.records[13],
    g_AlucardEffectSpriteMetadata.records[14],
    g_AlucardEffectSpriteMetadata.records[15],
};
