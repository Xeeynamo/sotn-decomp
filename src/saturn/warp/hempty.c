// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

LayoutEntity g_WarpHLayoutEmpty[] = {
    {0xFFFE, 0xFFFE, 0, 0, 0},
    {0xFFFF, 0xFFFF, 0, 0, 0},
};

LayoutEntity g_WarpHLayoutUnused05[] = {
    {0xFFFE, 0xFFFE, 0, 0, 0},
    {0, 0x0038, 0x0008, 0x0080, 0},
    {0xFFFF, 0xFFFF, 0, 0, 0},
};

u16 g_WarpHLayoutPadding = 0;
