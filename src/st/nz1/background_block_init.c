// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

static u8 D_us_80180CF0[] = {32, 1, -1, 0};
static u8 D_us_80180CF4[] = {32, 2, -1, 0};
static u8 D_us_80180CF8[] = {32, 3, -1, 0};
static u8 D_us_80180CFC[] = {32, 4, -1, 0};
static u8 D_us_80180D00[] = {32, 5, -1, 0};
static u8 D_us_80180D04[] = {32, 6, -1, 0};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {0x8002, 0x9F, 0x54, 0, 0xD, 0x0000, BLEND_NO, 0x00000000, D_us_80180CF0},
    {0x8002, 0x9F, 0x54, 0, 0xD, 0x0000, BLEND_NO, 0x00000000, D_us_80180CF4},
    {0x8002, 0x9F, 0x54, 0, 0xD, 0x0000, BLEND_NO, 0x00000000, D_us_80180CF8},
    {0x8002, 0x9F, 0x54, 0, 0xD, 0x0000, BLEND_NO, 0x00000000, D_us_80180CFC},
    {0x8002, 0x9F, 0x54, 0, 0xD, 0x0000, BLEND_NO, 0x00000000, D_us_80180D00},
    {0x8002, 0x9F, 0x54, 0, 0xD, 0x0000, BLEND_NO, 0x00000000, D_us_80180D04},
};
