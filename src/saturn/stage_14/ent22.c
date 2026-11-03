// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include <saturn_sprite.h>
#include "stage_14.h"

typedef struct {
    SaturnSpriteResource* resource;
    SaturnSpriteFrameHeader** frames;
    u16 spriteFlags;
    u16 drawPriority;
    u8 drawMode;
    u8 palette;
    u8 facing;
    u8 hitboxWidth;
    u32 state;
    u32 entityFlags;
    u8* animation;
} Stage14Entity16Variant;

EntityEntry g_Stage14EntityEntry22 = {&g_Stage14SpriteBank16, func_060DDC64};
EntityEntry g_Stage14EntityMariaCutscene = {
    &g_Stage14SpriteBank20, func_060DE850};
EntityEntry g_Stage14EntityEntry24 = {&g_Stage14SpriteBank20, func_060DE578};

u16 g_Stage14Entity22Data0[8] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
u16 g_Stage14Entity22Data1[8] = {
    0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003,
};
u8 g_Stage14Entity16Animation[4] = {
    0x40,
    0x07,
    0xFF,
    0xFF,
};
Stage14Entity16Variant g_Stage14Entity16Variant = {
    &g_Stage14SpriteBank16,
    g_Stage14SpriteBank16Frames,
    0x0,
    0x81,
    1,
    0,
    0,
    0,
    0x0,
    0x0,
    g_Stage14Entity16Animation,
};

EntityEntry g_Stage14EntityEntry16 = {&g_Stage14SpriteBank16, func_060DE970};

s16 g_Stage14Entity17Data0[4] = {
    320,
    256,
    640,
    512,
};
s16 g_Stage14Entity17Data1[4] = {
    0,
    0,
    960,
    512,
};

EntityEntry g_Stage14EntityEntry17 = {NULL, func_060DEAE4};
