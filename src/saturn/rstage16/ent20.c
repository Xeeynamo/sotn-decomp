// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

EntityEntry g_RStage16EntityEntry20 = {&g_RStage16SpriteBank18, func_060E2578};

EntityEntry g_RStage16EntityEntry21 = {NULL, func_060E3244};

EntityEntry g_RStage16EntityEntry22 = {NULL, func_060E3438};

u8 g_RStage16Entity20Data[4] = {
    0x10,
    0x12,
    0x20,
    0x30,
};

s8 g_RStage16Entity21Offsets[24][2] = {
    {15, -18},  {19, -16},  {21, -16},  {22, -8},   {27, 0},    {25, 1},
    {23, 1},    {21, 11},   {13, 20},   {2, 26},    {-7, 29},   {-20, 28},
    {-32, 20},  {-48, 14},  {-64, 0},   {-52, -8},  {-40, -20}, {-32, -22},
    {-28, -24}, {-26, -26}, {-24, -24}, {-22, -24}, {-16, -25}, {-16, -24},
};

u8 g_RStage16Entity21Sizes[24][2] = {
    {2, 0xA},    {2, 0xA},    {3, 0xA},     {4, 9},       {5, 8},
    {5, 7},      {6, 6},      {7, 6},       {8, 6},       {9, 8},
    {0xA, 0xB},  {0xA, 0xF},  {0x14, 0x12}, {0x18, 0x12}, {0x30, 0x10},
    {0x1C, 0xC}, {0x14, 0xA}, {0x10, 8},    {0xC, 6},     {0xA, 5},
    {8, 4},      {6, 6},      {4, 6},       {3, 7},
};
