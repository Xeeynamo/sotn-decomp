// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_T_BAT_BSS_H
#define SATURN_T_BAT_BSS_H

#include "sattypes.h"

extern u32 g_CurrentServant;
extern s32 g_CurrentRoomX;
extern s32 g_CurrentRoomY;
extern s16 g_BatFollowDeltaX;
extern s16 g_BatFollowDeltaY;
extern FamiliarStats s_BatStats;
extern Point16 s_BatPathingPoints[4][16];

#endif
