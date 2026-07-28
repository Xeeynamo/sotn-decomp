// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    u16 padding;
    u8 ranges[10][2];
} AlucardEntityRanges;

AlucardEntityRanges g_AlucardEntityRanges = {
    0,
    {
        {0x20, 0x3F},
        {0x11, 0x2F},
        {0x20, 0x2F},
        {0x10, 0x10},
        {0x1C, 0x1F},
        {0x19, 0x1F},
        {0x11, 0x1F},
        {0x11, 0x3F},
        {0x11, 0x3F},
        {0x2F, 0x2F},
    },
};
