// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

EntityEntry g_RStage16EntityWight = {&g_RStage16SpriteBankWight, func_060E4EDC};

s16 g_RStage16Entity28InitOffset[2] = {
    0,
    23,
};

EntityEntry g_RStage16EntityEntry28 = {
    &g_RStage16SpriteBankWight, func_060E56DC};

EntityEntry g_RStage16EntityEntry29 = {
    &g_RStage16SpriteBankWight, func_060E5CB0};

s16 g_RStage16Entity29Offset0[2] = {
    0,
    0,
};

u16 g_RStage16Entity29Offset1[4] = {
    0,
    0,
    0xFF,
    0,
};

u8 g_RStage16Entity30Anim[36] = {
    4, 0x14, 4, 0x15, 4, 0x14, 4, 0x15, 4,    0x16, 4, 0x17,
    4, 0x18, 4, 0x19, 4, 0x18, 4, 0x17, 4,    0x16, 4, 0x17,
    4, 0x16, 4, 0x15, 4, 0x14, 4, 0x15, 0xFF, 0,    0, 0,
};

EntityEntry g_RStage16EntityEntry30 = {
    &g_RStage16SpriteBankWight, func_060E5E70};

s16 g_RStage16Entity30Offset[2] = {
    0,
    0,
};

u8 g_RStage16WightPartAnimationData[76] = {
    0x18, 1,    0x18, 2,    0x18, 3,    0x18, 2,    0xFF, 0xFF, 0x18,
    4,    0x18, 5,    0x18, 6,    0x18, 5,    0xFF, 0xFF, 0x18, 7,
    0x18, 8,    0x18, 9,    0x18, 8,    0xFF, 0xFF, 0x20, 7,    0x20,
    0xA,  0xFF, 0xFF, 0x80, 1,    8,    0xB,  8,    0xC,  8,    0xD,
    8,    0xE,  8,    0xF,  0xFF, 0xFF, 1,    0x10, 1,    0x11, 0xFF,
    0xFF, 1,    0x12, 1,    0x13, 0xFF, 0xFF, 2,    0x14, 2,    0x15,
    2,    0x16, 2,    0x17, 2,    0x18, 2,    0x19, 0xFF, 0xFF,
};

u8* g_RStage16WightPartAnimations[8] = {
    g_RStage16WightPartAnimationData,
    &g_RStage16WightPartAnimationData[10],
    &g_RStage16WightPartAnimationData[20],
    &g_RStage16WightPartAnimationData[30],
    &g_RStage16WightPartAnimationData[36],
    &g_RStage16WightPartAnimationData[50],
    &g_RStage16WightPartAnimationData[56],
    &g_RStage16WightPartAnimationData[62],
};
