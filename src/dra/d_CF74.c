// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "sfx.h"

s32 g_AlucardChairSleepTimer = 0;

s16 D_800ACF7C[] = {
    1,
    31,
    0,
    27,
};

s16 g_SfxPainGrunts[] = {
    SFX_VO_ALU_YELL,   SFX_VO_ALU_SILENCE, SFX_VO_ALU_PAIN_E, SFX_VO_ALU_PAIN_D,
    SFX_VO_ALU_PAIN_C, SFX_VO_ALU_PAIN_B,  SFX_VO_ALU_PAIN_A,
};

// rotation angles
s16 D_800ACF94[] = {
    0x0000, 0x0000, 0x0100, 0x0000, 0xFF00, 0x0000, 0x0100, 0x0000,
    0xFF00, 0xFE00, 0xFF00, 0x0000, 0x0100, 0x0200, 0x0100, 0x0000,
};

// TODO AnimationFrames*[]
unionD_800ACFB4 D_800ACFB4[] = {
    {0x10, 0x7F, 0x3F, 0x00}, {0x10, 0x7F, 0x00, 0x00},
    {0x10, 0x3F, 0x3F, 0x3F}, {0x10, 0x5F, 0x2F, 0x00},
    {0x0C, 0x7F, 0x3F, 0x00}, {0x0C, 0x7F, 0x3F, 0x7F},
    {0x02, 0x7F, 0x3F, 0x7F}, {0x06, 0x00, 0x3F, 0x7F},
    {0x06, 0x3F, 0x3F, 0x3F}, {0x10, 0x3F, 0x3F, 0x7F},
    {0x10, 0xFF, 0xFF, 0xFF}, {0x12, 0x7F, 0x00, 0x00},
    {0x12, 0x7F, 0x7F, 0x7F}, {0x08, 0x7F, 0x7F, 0x7F}};

// probably a struct
u32 D_800ACFEC[] = {
    0x52594A43, 0x00010185, 0x5B66534E, 0x000101B1, 0x5B365320,
    0x000101B1, 0x5B4D5337, 0x000101B1, 0x526F4A5A, 0x00010182,
};

u8 D_800AD014[] = {
    0x20, 0x5c, 0x2d, 0x64, 0x82, 0x01, 0x01, 0x00,
};

u8 D_800AD01C[] = {
    0x20, 0x6e, 0x5b, 0x76, 0x82, 0x01, 0x01, 0x00, 0x67, 0x53, 0x7c, 0x5b,
    0x82, 0x01, 0x01, 0x00, 0x3b, 0x65, 0x59, 0x6d, 0xb4, 0x01, 0x02, 0x00,
    0x5a, 0x65, 0x78, 0x6d, 0xb4, 0x01, 0x02, 0x00, 0x20, 0x65, 0x3a, 0x6d,
    0xb4, 0x01, 0x02, 0x00, 0x51, 0x5c, 0x7f, 0x64, 0xb4, 0x01, 0x02, 0x00,
    0x2e, 0x5c, 0x50, 0x64, 0xb4, 0x01, 0x02, 0x00, 0x5c, 0x6e, 0x6c, 0x76,
    0xb8, 0x01, 0x03, 0x00, 0x33, 0x77, 0x3f, 0x7f, 0xb8, 0x01, 0x03, 0x00,
    0x40, 0x77, 0x5e, 0x7f, 0xb8, 0x01, 0x03, 0x00, 0x20, 0x53, 0x36, 0x5b,
    0xb8, 0x01, 0x03, 0x00, 0x20, 0x77, 0x32, 0x7f, 0xb8, 0x01, 0x03, 0x00,
    0x37, 0x53, 0x4d, 0x5b, 0xb8, 0x01, 0x03, 0x00, 0x6d, 0x6e, 0x7f, 0x76,
    0xb8, 0x01, 0x03, 0x00, 0x20, 0x77, 0x32, 0x7f, 0xb8, 0x01, 0x03, 0x00};
