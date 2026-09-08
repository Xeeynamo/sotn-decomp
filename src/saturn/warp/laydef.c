// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "warp.h"

LayoutEntity* g_WarpLayoutHorizontal[53] = {
    g_WarpHLayoutEmpty, // 0
    g_WarpHLayout01,    g_WarpHLayout02,    g_WarpHLayout03,
    g_WarpHLayout04,    g_WarpHLayout05,    g_WarpHLayout06,
    g_WarpHLayoutEmpty, // 7
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, g_WarpHLayoutEmpty, g_WarpHLayoutEmpty,
    g_WarpHLayoutEmpty, // 47
    g_WarpHLayout48,    g_WarpHLayout49,    g_WarpHLayout50,
    g_WarpHLayout51,    g_WarpHLayout52,
};

LayoutEntity* g_WarpLayoutVertical[53] = {
    g_WarpVLayoutEmpty, // 0
    g_WarpVLayout01,    g_WarpVLayout02,    g_WarpVLayout03,
    g_WarpVLayout04,    g_WarpVLayout05,    g_WarpVLayout06,
    g_WarpVLayoutEmpty, // 7
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, g_WarpVLayoutEmpty, g_WarpVLayoutEmpty,
    g_WarpVLayoutEmpty, // 47
    g_WarpVLayout48,    g_WarpVLayout49,    g_WarpVLayout50,
    g_WarpVLayout51,    g_WarpVLayout52,
};
