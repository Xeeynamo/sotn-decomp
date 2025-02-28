// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

AnimationFrame D_800ADBD4[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 4}, {2, 3},  {2, 4},
    {2, 3}, {2, 4}, {2, 5}, {1, 6}, {1, 7}, {1, 8}, {-1, 0},
};

AnimationFrame D_800ADC10[] = {
    {1, 9},  {2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}, {2, 15},
    {2, 16}, {2, 17}, {2, 18}, {3, 19}, {4, 20}, {-1, 0},
};

AnimationFrame D_800ADC44[] = {
    {2, 1}, {2, 2}, {2, 3},  {2, 4},  {2, 5},  {2, 6},  {2, 7},
    {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {-1, 0},
};

u16 D_800ADC7C[] = {PAL_DRA(0x194), PAL_DRA(0x199)};
// disable format to allow for extra spaces, to space these out nicely
// clang-format off
static Point16 D_800ADC80 = { -2, -24};
static Point16 D_800ADC84 = {  0,  -8};
static Point16 D_800ADC88 = {  2,   8};
static Point16 D_800ADC8C = {  0,  24};
static Point16 D_800ADC90 = {  6, -12};
static Point16 D_800ADC94 = {  8,   0};
static Point16 D_800ADC98 = {  7,  12};
static Point16 D_800ADC9C = { -8, -12};
static Point16 D_800ADCA0 = { -9,   0};
static Point16 D_800ADCA4 = { -7,  12};
static Point16 D_800ADCA8 = {-14,  -6};
static Point16 D_800ADCAC = {-15,   7};
static Point16 D_800ADCB0 = { 13,  -7};
static Point16 D_800ADCB4 = { 16,   8};
static Point16 D_800ADCB8 = { -7, -22};
static Point16 D_800ADCBC = {  6, -21};
static Point16 D_800ADCC0 = { -8,  21};
static Point16 D_800ADCC4 = {  7,  22};
// clang-format on
Point16* D_800ADCC8[] = {
    &D_800ADC80, &D_800ADC90, &D_800ADC84, &D_800ADC90, &D_800ADC94,
    &D_800ADC84, &D_800ADC94, &D_800ADC88, &D_800ADC84, &D_800ADC94,
    &D_800ADC98, &D_800ADC88, &D_800ADC98, &D_800ADC8C, &D_800ADC88,
    &D_800ADC88, &D_800ADC8C, &D_800ADCA4, &D_800ADC88, &D_800ADCA4,
    &D_800ADCA0, &D_800ADC84, &D_800ADC88, &D_800ADCA0, &D_800ADC84,
    &D_800ADCA0, &D_800ADC9C, &D_800ADC84, &D_800ADC9C, &D_800ADC80,
    &D_800ADC90, &D_800ADCB0, &D_800ADC94, &D_800ADCB0, &D_800ADCB4,
    &D_800ADC94, &D_800ADCB4, &D_800ADC98, &D_800ADC94, &D_800ADC9C,
    &D_800ADCA0, &D_800ADCA8, &D_800ADCA0, &D_800ADCAC, &D_800ADCA8,
    &D_800ADCA0, &D_800ADCA4, &D_800ADCAC, &D_800ADC80, &D_800ADC9C,
    &D_800ADCB8, &D_800ADC80, &D_800ADCBC, &D_800ADC90, &D_800ADC8C,
    &D_800ADCC0, &D_800ADCA4, &D_800ADC98, &D_800ADCC4, &D_800ADC8C,
    &D_800ADCB8, &D_800ADC9C, &D_800ADCA8, &D_800ADCBC, &D_800ADCB0,
    &D_800ADC90, &D_800ADCAC, &D_800ADCA4, &D_800ADCC0, &D_800ADCB4,
    &D_800ADCC4, &D_800ADC98,
};

s16 D_800ADDE8[22][6] = {
    {0x0000, 0x0000, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0000},
    {0x0000, 0x0000, 0x0100, 0x7000, 0x7000, 0x0200},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x1000},
    {0x0000, 0x0000, 0x7100, 0x0100, 0x7000, 0x0800},
    {0x0000, 0x0000, 0x0100, 0x7100, 0x0100, 0x0400},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0200, 0x7100, 0x0100},
    {0x0000, 0x0000, 0x0100, 0x0400, 0x0400, 0x0100},
    {0x0000, 0x0000, 0x7100, 0x0100, 0x7100, 0x0100},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x0200},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x0400},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0400},
    {0x0A00, 0x0500, 0x0100, 0x0100, 0x0100, 0x0800},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0000, 0x0000, 0x0100, 0x0200, 0x7200, 0x0400},
    {0x0000, 0x0000, 0x0100, 0x0100, 0x7100, 0x0400},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x0400},
    {0x0000, 0x0000, 0x7100, 0x0100, 0x7000, 0x0400},
    {0x0000, 0x0000, 0x0100, 0x7100, 0x0100, 0x0100},
    {0x0000, 0x0000, 0x0100, 0x0200, 0x7100, 0x0100},
    {0x0000, 0x0000, 0x0100, 0x7100, 0x0100, 0x0400},
};

u32 D_800ADEF0[] = {
    // it might be a struct, used by EntityPlayerPinkEffect
    0x20101001, 0x000000FF, 0x28353535, 0x00000000, 0x0F535353, 0x00000000,
    0x00000080, 0x20101001, 0x000000FF, 0x28353535, 0x00000000, 0x10545454,
    0x00000000, 0x00000081, 0x0000FF02, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000082, 0x0000FF02, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000083, 0x50101001, 0x0000FF20,
    0x28353535, 0x0000002C, 0x070D0C06, 0x00000001, 0x00000004, 0x50101001,
    0x0000FF20, 0x28353535, 0x0000002C, 0x060B0A03, 0x00000003, 0x00000002,
    0x50101001, 0x0000FF20, 0x28353535, 0x0000002C, 0x03090904, 0x00000004,
    0x00000003, 0x50101001, 0x0000FF20, 0x28353535, 0x0000002C, 0x05080801,
    0x00000002, 0x00000001, 0x50101001, 0x0000FF20, 0x28353535, 0x0000002C,
    0x04000000, 0x00000014, 0x00000000, 0x20101001, 0x0000FF20, 0x28353535,
    0x0000002C, 0x084F4F4E, 0x00000045, 0x00000005, 0x20101001, 0x0000FF20,
    0x28353535, 0x0000002C, 0x0950504E, 0x0000004B, 0x00000007, 0x20101001,
    0x0000FF20, 0x28353535, 0x0000002C, 0x0A51514E, 0x0000004C, 0x00000006,
    0x20101001, 0x0000FF20, 0x28353535, 0x0000002C, 0x0B40404E, 0x00000049,
    0x0000000A, 0x20101001, 0x0000FF20, 0x28353535, 0x0000002C, 0x0C45454E,
    0x00000050, 0x00000008, 0x20101001, 0x0000FF20, 0x28353535, 0x0000002C,
    0x0D52524E, 0x0000004D, 0x00000009, 0x20101001, 0x0000FF20, 0x28353535,
    0x0000002C, 0x1255554E, 0x0000005E, 0x0000000B, 0x50101001, 0x0000FF20,
    0x28353535, 0x0000002C, 0x0E120207, 0x00000048, 0x00000084, 0x50101001,
    0x0000FF20, 0x28353535, 0x0000002C, 0x0E120207, 0x00000048, 0x00000085,
    0x50101001, 0x0000FF20, 0x28353535, 0x0000002C, 0x0E120207, 0x00000048,
    0x00000086, 0x50101001, 0x0000FF20, 0x28353535, 0x0000002C, 0x13120207,
    0x0000005F, 0x00000087,
};

u8 D_800AE120[] = {
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x12, 0x12, 0x12, 0x12,
};

RECT D_800AE130 = {512, 256, 32, 80};

RECT D_800AE138 = {512 + 32, 256, 32, 80};

u8 D_800AE140[][8] = {
    0x00, 0x11, 0x21, 0x22, 0x32, 0x43, 0x44, 0x54, 0x90, 0x91, 0x82,
    0x83, 0x94, 0xA5, 0xB6, 0xB7, 0xC7, 0xD8, 0xE8, 0xF7, 0xE9, 0xEA,
    0xEB, 0xEC, 0x7F, 0x7E, 0x7D, 0x8C, 0x9B, 0xAA, 0xB9, 0xA8, 0x07,
    0x17, 0x27, 0x38, 0x47, 0x57, 0x56, 0x58, 0x7A, 0x6B, 0x5C, 0x4D,
    0x3E, 0x2D, 0x1C, 0x0C, 0xE0, 0xF1, 0xF2, 0xF3, 0xF4, 0xE4, 0xF5,
    0xF6, 0xB9, 0xC9, 0xCA, 0xCB, 0xCC, 0xDD, 0xEE, 0xEF,
};

Unkstruct_800AE180 D_800AE180[] = {
    {PAL_DRA(0x19F), 0x0030},
    {PAL_DRA(0x19F), 0x0018},
    {PAL_DRA(0x19F), 0x0000},
    {PAL_DRA(0x19F), 0x0048},
};

s16 D_800AE190[] = {
    0x0000, 0x0200, 0x0400, 0x0600, 0x0800, 0x0A00, 0x0C00, 0x0E00,
    0x1000, 0x1200, 0x1400, 0x1600, 0x1800, 0x1A00, 0x1C00, 0x1E00,
};

s16 D_800AE1B0[] = {
    0x48, 0x48, 0x48, 0x44, 0x44, 0x40, 0x40, 0x3C, 0x40, 0x40, 0x44,
    0x48, 0x4C, 0x50, 0x58, 0x60, 0x60, 0x58, 0x50, 0x4C, 0x48, 0x44,
    0x40, 0x40, 0x3C, 0x40, 0x40, 0x44, 0x44, 0x48, 0x48, 0x48,
};

s16 D_800AE1F0[] = {
    -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,  0,
    0,  0,  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1,
};

u32 D_800AE230[] = {
    7, 0, 1, 2, 3, 4, 5, 6,
};

u32 D_800AE250[] = {
    2, 1, 0, 7, 6, 5, 4, 3,
};

s32 D_800AE270 = 0xFF;
s32 D_800AE274 = 0xFF;
s32 D_800AE278 = 0xFF;
s32 D_800AE27C = 0x7F;
s32 D_800AE280 = 0x7F;
s32 D_800AE284 = 0x3F; 
s32 D_800AE288 = 0x7F;
s32 D_800AE28C = 0x3F;
s32 D_800AE290 = 0x7F;