// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

EntityEntry g_RStage16EntityEntry00 = {NULL, func_060DC040};

u8 g_RStage16BreakableAnimations[24] = {
    5, 1, 5, 2, 5, 3, 5, 4, 0,    0,   5,    6,
    5, 7, 5, 8, 5, 9, 0, 0, 0x10, 0xC, 0xFF, 0xFF,
};

s16 g_RStage16BreakablePrimitiveOffsets[8][5] = {
    {-23, 6, 11, 0, 0},  {-16, 7, 12, 0, 0},  {-23, 6, 11, 0, 0},
    {-17, 8, 13, 0, 0},  {-23, 24, 11, 0, 0}, {-16, 25, 12, 0, 0},
    {-23, 24, 11, 0, 0}, {-17, 26, 13, 0, 0},
};

RStage16BreakableConfig g_RStage16BreakableConfigs[3] = {
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames,
     g_RStage16BreakablePrimitiveOffsets[0], &g_RStage16BreakableAnimations[10],
     0, 8, 0x70, 3, 0, -16},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames,
     g_RStage16BreakablePrimitiveOffsets[4], g_RStage16BreakableAnimations, 0,
     8, 0x70, 3, 0, -40},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, NULL,
     &g_RStage16BreakableAnimations[20], 0, 8, 0, 1, 0, -16},
};

EntityEntry g_RStage16EntityEntry17 = {&g_RStage16SpriteBank16, func_060DC418};

u8 g_RStage16Entity17Animations[6][4] = {
    {0x10, 0x10, 0, 0}, {0x10, 0x11, 0, 0}, {0x10, 0x12, 0, 0},
    {0x10, 0x13, 0, 0}, {0x10, 0x14, 0, 0}, {0x10, 0x15, 0, 0},
};

RStage16Entity17Variant g_RStage16Entity17Variants[6] = {
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, 0, 0x60, 1, 0, 0, 0,
     0, 0, g_RStage16Entity17Animations[0]},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, 0, 0x60, 1, 0, 0, 0,
     0, 0, g_RStage16Entity17Animations[1]},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, 0, 0x60, 1, 0, 0, 0,
     0, 0, g_RStage16Entity17Animations[2]},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, 0, 0x60, 1, 0, 0, 0,
     0, 0, g_RStage16Entity17Animations[3]},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, 0, 0x60, 1, 0, 0, 0,
     0, 0, g_RStage16Entity17Animations[4]},
    {&g_RStage16SpriteBank16, g_RStage16SpriteBank16Frames, 0, 0x60, 1, 0, 0, 0,
     0, 0, g_RStage16Entity17Animations[5]},
};

EntityEntry g_RStage16EntityEntry16 = {NULL, func_060DC4C0};
